# STM32Disc

STM32Disc is a collection of bare-metal STM32F407G-DISC1 practice projects focused on learning direct register programming, peripheral clock configuration, clock measurement, and custom driver development. The repository follows a hands-on learning path from low-level bit manipulation to reusable GPIO driver abstractions.

## Hardware Platform

- STM32F407G-DISC1 Discovery board
- MCU: STM32F407VG
- Toolchain: STM32CubeIDE / GCC ARM Embedded
- Target style: bare-metal C, no HAL abstraction

## Repository Overview

The repository is organized as a series of standalone learning exercises, each in its own numbered folder:

- 0004_Peripheral_Clock_Configuration
- 0005_Peripheral_Clock_Configuration_GPIO
- 0006_HSI_Clock_Measurement
- 0007_HSE_Clock_Measurement
- 0008_GPIO_Driver_Configuration
- 0009_GPIO_Driver_Toggle_LED_PushPull
- 0010_GPIO_Driver_Toggle_LED_OpenDrain
- 0011_GPIO_Driver_Button_LED
- 0012_GPIO_Driver_External_BTN_LED

## Learning Progression

### 0004_Peripheral_Clock_Configuration

This project introduces the fundamental idea of enabling a peripheral clock and setting a specific register bit. It uses ADC1 as the example peripheral and demonstrates how to:

- identify the peripheral bus
- calculate the base and offset addresses
- enable the corresponding RCC clock bit
- set a control register bit in memory-mapped hardware

### 0005_Peripheral_Clock_Configuration_GPIO

This exercise extends the same idea to GPIO. It configures the AHB1 clock for GPIOD and sets PD2 high to demonstrate GPIO output control. It is a practical example of direct register access when driving a pin.

### 0006_HSI_Clock_Measurement

This project focuses on using the internal HSI oscillator and exposing it on PA8 via MCO1. It teaches:

- selecting the clock source for MCO1
- configuring GPIOA pin 8 as alternate function
- measuring or verifying the HSI output using an oscilloscope or logic analyzer

### 0007_HSE_Clock_Measurement

This exercise mirrors the HSI work but switches to the external high-speed clock (HSE). It shows how to enable HSE, wait for readiness, route the signal to MCO1, and verify the external clock on PA8.

### 0008_GPIO_Driver_Configuration

This is the transition from register-level exercises to reusable firmware design. The project defines:

- a custom MCU header: `stm32f407xx.h`
- a GPIO driver API in `gpiodriver.h`
- the implementation in `gpiodriver.c`

It includes abstractions for:

- GPIO clock control
- GPIO initialization and de-initialization
- pin-level read/write/toggle operations
- GPIO mode, speed, output type, and pull configuration

This folder represents the foundation for building a proper device driver layer in embedded C.

### 0009_GPIO_Driver_Toggle_LED_PushPull

This project applies the GPIO driver API to a real output task: toggling the orange user LED on the STM32F407G-DISC1 board. It demonstrates how to:

- configure the MCU memory map and GPIO register layout
- build a reusable GPIO driver with explicit hardware access
- initialize `GPIOD Pin 13` as a push-pull output
- use the driver API to toggle the LED in a simple forever loop

The focus is on keeping the implementation close to the hardware while still organizing the code into reusable driver abstractions.

### 0010_GPIO_Driver_Toggle_LED_OpenDrain

This project builds on the push-pull LED example by configuring `PD13` as an
open-drain output. It demonstrates how output type and pull-up configuration
affect the available LED current and brightness.

### 0011_GPIO_Driver_Button_LED

This example reads the STM32F407G-DISC1 user button on `PA0` and controls the
orange LED on `PD13`. It uses the board's external pull-down and introduces
input-state interpretation and switch debouncing.

### 0012_GPIO_Driver_External_BTN_LED

This project uses an external active-low button on `PD14` with a pull-up and
controls an LED on `PD13`. Its README includes circuit illustrations and
documents troubleshooting LED polarity, breadboard continuity, and series
resistor selection.

## Repository Structure

Each numbered directory is a standalone STM32CubeIDE project. The projects
progress from register-level fundamentals to GPIO drivers and hardware
applications.

| Project folder | Focus |
| --- | --- |
| `0004_Peripheral_Clock_Configuration` | Enable and configure a peripheral clock using ADC1. |
| `0005_Peripheral_Clock_Configuration_GPIO` | Enable the GPIO clock and drive a GPIO pin. |
| `0006_HSI_Clock_Measurement` | Route and measure the internal HSI clock on PA8. |
| `0007_HSE_Clock_Measurement` | Route and measure the external HSE clock on PA8. |
| `0008_GPIO_Driver_Configuration` | Configure the reusable, register-level GPIO driver. |
| `0009_GPIO_Driver_Toggle_LED_PushPull` | Drive the on-board LED using push-pull output. |
| `0010_GPIO_Driver_Toggle_LED_OpenDrain` | Explore open-drain output and pull-up behavior. |
| `0011_GPIO_Driver_Button_LED` | Read the on-board button and control the on-board LED. |
| `0012_GPIO_Driver_External_BTN_LED` | Use an external pull-up button and LED; includes circuit diagrams and troubleshooting. |

Projects generally include `Src/`, `Startup/`, linker scripts, and (where
applicable) `drivers/`, `Images/`, and STM32CubeIDE project configuration
files. Open a project's README for its exact hardware setup and instructions.

## Key Concepts Covered

- Memory-mapped peripheral access
- RCC clock enable and disable logic
- GPIO register layout and configuration
- Alternate function pin mapping
- Bare-metal C driver design
- MCU clock source configuration
- Direct bit manipulation and register masks
- Push-pull and open-drain GPIO outputs
- Active-high and active-low button inputs with pull resistors
- External LED current limiting and circuit troubleshooting

## Recommended Workflow

1. Open the project in STM32CubeIDE.
2. Build the selected project in its own folder.
3. Flash it to the STM32F407G-DISC1 board.
4. Use a logic analyzer or oscilloscope to validate signal behavior when needed.
5. Move from direct register access to reusable abstracted driver code as seen in the GPIO driver project.

## Typical Project Setup

Each exercise is designed as a self-contained STM32 project and includes:

- generated startup assembly files
- linker scripts
- source files under `Src/`
- board-specific configuration files
- optional images for expected outputs

## Notes

This repository is intended primarily for learning and experimentation. It is not a production framework and does not rely on vendor HAL libraries for the core examples. Instead, it focuses on understanding the hardware at the register level and building simple abstractions on top of that foundation.

## Future Improvements

Potential next steps for this learning repository include:

- adding UART driver examples
- implementing SPI/I2C drivers
- adding EXTI interrupt examples
- building a full custom peripheral driver library
- documenting oscilloscope screenshots and results for each exercise
