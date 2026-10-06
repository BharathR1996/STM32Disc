# GPIO Driver Toggle LED (Push-Pull) for STM32F407VG

This project demonstrates a lightweight, register-level GPIO driver for the STM32F407VG microcontroller and uses it to blink an LED on the STM32F407G-DISC1 board. The code is intentionally bare-metal and keeps the implementation close to the hardware, which makes it ideal for learning how GPIO peripherals are configured and toggled at the register level.

## Project objective

The firmware is built around three main ideas:

- define the MCU memory map and register structures
- create a reusable GPIO driver API with explicit hardware access
- use that driver in `main.c` to toggle an LED in a simple forever loop

This project is educational rather than a complete HAL. It focuses on direct register manipulation and the structure-based design commonly used in embedded C drivers.

## Hardware target

- Board: STM32F407G-DISC1 Discovery Board
- MCU: STM32F407VG
- Core: ARM Cortex-M4
- Toolchain: STM32CubeIDE / GCC ARM Embedded
- LED used: Orange LED on GPIOD pin 13 (`PD13`)

On the STM32F407G-DISC1 board, the orange LED is commonly connected to `GPIOD Pin 13`.

## Actual project structure

```text
0009_GPIO_Driver_Toggle_LED_PushPull/
├── .cproject
├── .project
├── Startup/
│   └── startup_stm32f407vgtx.s
├── Src/
│   ├── main.c
│   ├── syscalls.c
│   └── sysmem.c
├── drivers/
│   ├── Inc/
│   │   ├── gpiodriver.h
│   │   └── stm32f407xx.h
│   └── Src/
│       └── gpiodriver.c
├── STM32F407VGTX_FLASH.ld
├── STM32F407VGTX_RAM.ld
├── README.md
└── (empty/unused) Inc/
```

Important note: the working driver code is under `drivers/Inc` and `drivers/Src`. The generated startup files and linker scripts are present in their expected locations for STM32CubeIDE projects.

## Code analysis

### 1. MCU register map: `drivers/Inc/stm32f407xx.h`

This header contains the MCU-level definitions that make the code portable and readable.

It provides:

- base addresses for flash, SRAM, GPIO, RCC, SYSCFG, and EXTI
- register layout structs such as `GPIO_RegDef_t` and `RCC_RegDef_t`
- pointer aliases like `GPIOA`, `GPIOB`, `GPIOD`, and `RCC`
- clock-enable and clock-disable macros
- reset macros and generic constants such as `ENABLE`, `DISABLE`, and `SET`

Example register mapping:

```c
typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
}GPIO_RegDef_t;
```

This is the core of the bare-metal approach: each GPIO port is represented as a C struct overlaying the exact memory address of the hardware peripheral.

The clock macros are also defined at the register level, for example:

```c
#define GPIOD_CLK_EN()   (RCC->RCC_AHB1ENR |= (1 << 3))
#define GPIOD_CLK_DIS()  (RCC->RCC_AHB1ENR &= ~(1 << 3))
```

This matches the STM32F4 RCC register layout, where the AHB1 clock-enable bits control the GPIO ports.

### 2. GPIO configuration API: `drivers/Inc/gpiodriver.h`

The public driver API defines the data structures used by the application:

```c
typedef struct {
    uint8_t pinNumber;
    uint8_t pinMode;
    uint8_t pinSpeed;
    uint8_t pinOutputType;
    uint8_t pinPullUpPullDown;
    uint8_t pinAlternateFuncMode;
}GPIO_PinConfig_t;
```

```c
typedef struct {
    GPIO_RegDef_t *pGPIOBaseAddr;
    GPIO_PinConfig_t GPIOPinConfig;
}GPIO_Handler_t;
```

The driver exposes the following mode and configuration constants:

- `GPIO_MODE_IN = 0`
- `GPIO_MODE_OUT = 1`
- `GPIO_MODE_ALTFUN = 2`
- `GPIO_MODE_ANALOG = 3`
- `GPIO_OUTPUT_TYPE_PUSHPULL = 0`
- `GPIO_OUTPUT_TYPE_OPENDRAIN = 1`
- `GPIO_OUTPUT_SPEED_LOW = 0`
- `GPIO_OUTPUT_SPEED_MEDIUM = 1`
- `GPIO_OUTPUT_SPEED_HIGH = 2`
- `GPIO_OUTPUT_SPEED_VERYHIGH = 3`
- `GPIO_NO_PULL_UP_DOWN = 0`
- `GPIO_PULL_UP = 1`
- `GPIO_PULL_DOWN = 2`

The file also declares the reusable GPIO functions:

```c
void GPIO_CLKControl(GPIO_RegDef_t *pGPIOBaseAddr, bool EnDis);
void GPIO_Init(GPIO_Handler_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOBaseAddr);
uint8_t GPIO_ReadPortPin(GPIO_RegDef_t *pGPIOBaseAddr, uint8_t pinNumber);
uint16_t GPIO_ReadPort(GPIO_RegDef_t *pGPIOBaseAddr);
void GPIO_WritePortPin(GPIO_RegDef_t *pGPIOBaseAddr, uint8_t pinNumber, bool value);
void GPIO_WritePort(GPIO_RegDef_t *pGPIOBaseAddr, uint16_t value);
void GPIO_TogglePin(GPIO_RegDef_t *pGPIOBaseAddr, uint8_t pinNumber);
```

### 3. Driver implementation: `drivers/Src/gpiodriver.c`

This file is the real logic behind the peripheral control.

#### Clock control

```c
void GPIO_CLKControl(GPIO_RegDef_t *pGPIOBaseAddr, bool EnDis)
```

This function checks which GPIO port pointer was passed and then enables or disables the corresponding clock bit in `RCC_AHB1ENR`.

This is essential because GPIO peripherals are dormant by default; they must have their buses clocked before any register is configured.

#### Initialization

```c
void GPIO_Init(GPIO_Handler_t *pGPIOHandle)
```

The implementation writes configuration fields to the GPIO registers:

- `MODER` selects the pin mode (input, output, alternate, analog)
- `OTYPER` selects output type (push-pull or open-drain)
- `OSPEEDR` selects the drive speed
- `PUPDR` selects pull-up or pull-down behavior
- `AFR[]` is prepared when alternate-function mode is used

The pin-number mapping is straightforward: each GPIO register field uses 2 bits per pin in `MODER`, `OSPEEDR`, and `PUPDR`, and 1 bit per pin in `OTYPER`.

#### De-initialization

```c
void GPIO_DeInit(GPIO_RegDef_t *pGPIOBaseAddr)
```

This function resets the selected GPIO port by using the reset macros. The code uses a helper named `resetGPIOPeripheral()`, which calls `GPIO_PERIPHERAL_SET` and `GPIO_PERIPHERAL_RESET` for a position index.

#### Read / write / toggle operations

The driver implements these common operations:

```c
uint8_t GPIO_ReadPortPin(GPIO_RegDef_t *pGPIOBaseAddr, uint8_t pinNumber)
uint16_t GPIO_ReadPort(GPIO_RegDef_t *pGPIOBaseAddr)
void GPIO_WritePortPin(GPIO_RegDef_t *pGPIOBaseAddr, uint8_t pinNumber, bool value)
void GPIO_WritePort(GPIO_RegDef_t *pGPIOBaseAddr, uint16_t value)
void GPIO_TogglePin(GPIO_RegDef_t *pGPIOBaseAddr, uint8_t pinNumber)
```

The toggle operation is a simple XOR on the LED bit:

```c
pGPIOBaseAddr->ODR ^= (0x01 << pinNumber);
```

This is the key mechanism used in the firmware to flip the LED state.

#### Interrupt-related functions

The driver declares the following stubs:

```c
void GPIO_INTRConfig(uint8_t pinNumber, uint8_t IRQPriority, bool EnDis);
void GPIO_INTRHandler(uint8_t pinNumber);
```

These functions are empty. This project does not implement EXTI or NVIC interrupt handling, which is expected in a learning-focused GPIO driver.

## Application logic: `Src/main.c`

The actual example program configures `GPIOD Pin 13` as a push-pull output, enables the GPIO clock, initializes the pin, and then toggles it forever.

```c
GPIO_Handler_t orangeLED;

int main(void)
{
    memset(&orangeLED, 0, sizeof(GPIO_Handler_t));

    // Enable Clock for Port D
    GPIO_CLKControl(GPIOD, ENABLE);

    orangeLED.pGPIOBaseAddr = GPIOD;
    orangeLED.GPIOPinConfig.pinNumber = GPIO_PIN_13;
    orangeLED.GPIOPinConfig.pinMode = GPIO_MODE_OUT;
    orangeLED.GPIOPinConfig.pinOutputType = GPIO_OUTPUT_TYPE_PUSHPULL;
    orangeLED.GPIOPinConfig.pinSpeed = GPIO_OUTPUT_SPEED_MEDIUM;
    orangeLED.GPIOPinConfig.pinPullUpPullDown = GPIO_NO_PULL_UP_DOWN;

    GPIO_Init(&orangeLED);

    int i;
    for (;;)
    {
        GPIO_TogglePin(GPIOD, orangeLED.GPIOPinConfig.pinNumber);
        for (i = 0; i < 100000; i++);
    }
}
```

This is a classic embedded LED-blink pattern: configure the pin as output, toggle the output data register, and insert a software delay loop.

## Why this project matters

This code teaches the following embedded-programming concepts:

- memory-mapped peripheral access
- direct register programming on STM32 devices
- hardware abstraction through structs and helper APIs
- GPIO clock gating via RCC
- bit manipulation for mode, speed, type, and pull configuration
- driver-style API design for embedded firmware

## Important implementation notes and caveats

This project is intentionally simple and educational, but there are some practical observations:

1. The driver is not a full production GPIO HAL.
   - interrupt support is not implemented
   - alternate-function handling is only partially wired
   - many peripheral families and features are intentionally left out

2. `GPIO_Init()` uses bitwise OR operations without clearing the field first.
   - For a fresh peripheral state this is usually acceptable.
   - However, if a pin is initialized more than once or a register already contains other bits, this can leave stale configuration bits set.
   - A safer implementation would clear the relevant field before writing the new value.

3. Reset logic is simplified.
   - The project defines GPIO reset using the RCC reset registers, but the actual GPIO reset bits on STM32F4 are in the AHB1 reset registers rather than the APB1 reset block used in the helper.
   - This is acceptable for a learning example, but it is not a complete, device-accurate implementation for all use cases.

4. The LED toggle is a software delay loop.
   - It works for demonstration purposes.
   - In real firmware, a timer-based delay or a scheduler is usually preferred for timing and lower power usage.

## Build and usage steps

1. Open the project in STM32CubeIDE.
2. Make sure the include path includes `drivers/Inc`.
3. Build the firmware.
4. Flash the binary to the STM32F407G-DISC1 board.
5. The orange LED on `GPIOD Pin 13` should blink continuously.

## Summary

This project is a hands-on example of a custom STM32 GPIO driver built from direct register access. It shows how a tiny driver can abstract GPIO behavior while still staying close to the hardware. The code is concise, readable, and useful as a learning base for more advanced peripheral drivers such as UART, SPI, I2C, and EXTI.
