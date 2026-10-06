# GPIO Driver Configuration for STM32F407VG

This project is a bare-metal embedded C exercise that demonstrates how to build a reusable GPIO device driver for the STM32F407VG microcontroller using direct register access. It is part of a larger learning repository focused on understanding the STM32F407G-DISC1 board at the hardware-register level.

## Project Objective

The goal of this project is to move from raw memory-mapped register manipulation to an abstraction layer that encapsulates GPIO configuration and control. Instead of directly writing to hardware addresses in every source file, the project defines:

- a MCU-specific register header,
- GPIO configuration structures,
- GPIO helper macros,
- a functional GPIO driver API.

This makes the code easier to reuse and clearer to understand while still staying close to the hardware.

## Hardware Target

- Board: STM32F407G-DISC1 Discovery Board
- MCU: STM32F407VG
- Core: ARM Cortex-M4
- Toolchain: STM32CubeIDE / GCC ARM Embedded

## Project Structure

```text
0008_GPIO_Driver_Configuration/
├── .cproject
├── .project
├── STM32F407VGTX_FLASH.ld
├── STM32F407VGTX_RAM.ld
├── Src/
│   ├── main.c
│   ├── syscalls.c
│   └── sysmem.c
├── Startup/
│   └── startup_stm32f407vgtx.s
├── drivers/
│   ├── Inc/
│   │   ├── gpiodriver.h
│   │   └── stm32f407xx.h
│   └── Src/
│       └── gpiodriver.c
└── README.md
```

## Core Files

### 1. `drivers/Inc/stm32f407xx.h`

This header is the MCU memory map and register definition file. It provides:

- base addresses for SRAM, flash, GPIO, RCC, and SYSCFG
- GPIO register structure definitions
- RCC register structure definition
- peripheral pointer aliases such as `GPIOA`, `GPIOB`, `GPIOD`, etc.
- clock-enable macros such as `GPIOA_CLK_EN()` and `GPIOD_CLK_EN()`
- reset and enable/disable utility macros

The file defines the memory-mapped register layout used by the GPIO driver. For example:

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

This structure maps directly to the STM32 GPIO peripheral registers, making direct hardware access straightforward and efficient.

### 2. `drivers/Inc/gpiodriver.h`

This is the public API for the GPIO driver. It defines:

- `GPIO_PinConfig_t` for a single pin configuration
- `GPIO_Handler_t` for a GPIO peripheral instance and its configuration
- GPIO mode values
- output type values
- speed values
- pull-up/pull-down values
- function prototypes for the driver API

Example types from the file:

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

and:

```c
typedef struct {
    GPIO_RegDef_t *pGPIOBaseAddr;
    GPIO_PinConfig_t GPIOPinConfig;
}GPIO_Handler_t;
```

The defined GPIO modes are:

- `GPIO_MODE_IN` = 0
- `GPIO_MODE_OUT` = 1
- `GPIO_MODE_ALTFUN` = 2
- `GPIO_MODE_ANALOG` = 3

The driver also supports:

- push-pull or open-drain output mode
- low / medium / high / very-high output speed
- no pull-up/down, pull-up, pull-down

### 3. `drivers/Src/gpiodriver.c`

This file implements the GPIO driver logic. It contains the actual register operations for controlling STM32 GPIO peripheral behavior.

#### a) Clock control

```c
void GPIO_CLKControl(GPIO_RegDef_t *pGPIOBaseAddr, bool EnDis)
```

This function enables or disables the clock for a given GPIO port. It checks the `pGPIOBaseAddr` against each known GPIO base pointer and calls the matching RCC clock-enable or clock-disable macro.

#### b) Initialization

```c
void GPIO_Init(GPIO_Handler_t *pGPIOHandle)
```

This function configures the selected GPIO pin using the hardware registers:

- `MODER` to select input/output/alternate function/analog mode
- `OTYPER` to select push-pull vs open-drain output type
- `OSPEEDR` to set pin speed
- `PUPDR` to configure pull-up or pull-down resistors
- `AFR[]` for alternate function configuration when needed

#### c) De-initialization

```c
void GPIO_DeInit(GPIO_RegDef_t *pGPIOBaseAddr)
```

This function resets a GPIO peripheral using the reset mechanism defined in the MCU header. A helper function calls the relevant reset macro after selecting the port.

#### d) Read and write operations

```c
uint8_t GPIO_ReadPortPin(GPIO_RegDef_t *pGPIOBaseAddr, uint8_t pinNumber)
uint16_t GPIO_ReadPort(GPIO_RegDef_t *pGPIOBaseAddr)
void GPIO_WritePortPin(GPIO_RegDef_t *pGPIOBaseAddr, uint8_t pinNumber, bool value)
void GPIO_WritePort(GPIO_RegDef_t *pGPIOBaseAddr, uint16_t value)
void GPIO_TogglePin(GPIO_RegDef_t *pGPIOBaseAddr, uint8_t pinNumber)
```

These functions provide the basic GPIO operations used in firmware development:

- read a single pin
- read the entire port register
- set or clear one pin
- write the full port value
- toggle a chosen pin

#### e) Interrupt stubs

The file contains placeholder functions for interrupt-related functionality:

```c
void GPIO_INTRConfig(uint8_t pinNumber, uint8_t IRQPriority, bool EnDis)
void GPIO_INTRHandler(uint8_t pinNumber)
```

These are intentionally left unimplemented in this learning project, indicating that external interrupt handling is a continuation of the driver design rather than a complete production implementation.

## Usage Pattern

The project is structured so a user can configure a GPIO pin using a handler and then call the public driver API. For example, a typical LED configuration on GPIOD pin 12 would look like this:

```c
#include "gpiodriver.h"

int main(void)
{
    GPIO_Handler_t led = {0};

    led.pGPIOBaseAddr = GPIOD;
    led.GPIOPinConfig.pinNumber = 12;
    led.GPIOPinConfig.pinMode = GPIO_MODE_OUT;
    led.GPIOPinConfig.pinOutputType = GPIO_OUTPUT_TYPE_PUSHPULL;
    led.GPIOPinConfig.pinSpeed = GPIO_OUTPUT_SPEED_HIGH;
    led.GPIOPinConfig.pinPullUpPullDown = GPIO_NO_PULL_UP_DOWN;

    GPIO_CLKControl(GPIOD, ENABLE);
    GPIO_Init(&led);

    while (1)
    {
        GPIO_TogglePin(GPIOD, 12);
        for (volatile uint32_t i = 0; i < 1000000; i++);
    }
}
```

This demonstrates the intended design style of the driver: configure the port, initialize the pin, and then interact through driver functions rather than direct hardware access.

## Main Program

The current `Src/main.c` file in this project is a minimal generated STM32CubeIDE entry point:

```c
int main(void)
{
    /* Loop forever */
    for(;;);
}
```

This means the project is structured as a driver library skeleton and can be used as a base for custom application logic. The real implementation work lives in the driver files under `drivers/`.

## Key Learning Outcomes

This project teaches the following embedded systems concepts:

- memory-mapped peripheral access
- GPIO register layout and bitfield programming
- MCU-specific peripheral abstractions
- clock gating for GPIO ports
- structure-based configuration design
- writing reusable C driver functions for embedded targets

## Design Notes and Observations

This project is an educational driver implementation rather than a full, production-grade HAL. Several parts are intentionally simplified, and a few details reflect early-stage driver development:

- the project defines a functional GPIO driver API but leaves interrupt handling incomplete
- the driver is built around manually defined MCU register structs and macros
- register access is explicit and close to the hardware, making it ideal for learning

This makes it especially useful for those learning how STM32 peripherals are controlled at the register level.

## Build and Setup Guidance

1. Import the folder into STM32CubeIDE.
2. Ensure the include path includes `drivers/Inc`.
3. Build the project.
4. Flash it to the STM32F407G-DISC1 board.
5. Add application logic in `Src/main.c` or expand the driver as needed.

## Summary

`0008_GPIO_Driver_Configuration` is a foundational STM32 firmware project that turns raw GPIO register operations into a clean, reusable driver API. It shows how to represent peripheral register maps, configure GPIO pins, and encapsulate hardware behavior into manageable C functions. The project is best understood as a stepping stone from direct register programming toward a more systematic embedded driver architecture.
