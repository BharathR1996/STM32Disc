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

## Repository Structure

```text
STM32Disc/
├── 0004_Peripheral_Clock_Configuration/
│   ├── README.md
│   ├── Src/
│   ├── Startup/
│   ├── STM32F407VGTX_FLASH.ld
│   ├── STM32F407VGTX_RAM.ld
│   └── Images/
├── 0005_Peripheral_Clock_Configuration_GPIO/
│   ├── README.md
│   ├── Src/
│   ├── Startup/
│   ├── STM32F407VGTX_FLASH.ld
│   ├── STM32F407VGTX_RAM.ld
│   └── Images/
├── 0006_HSI_Clock_Measurement/
│   ├── README.md
│   ├── Src/
│   ├── Startup/
│   ├── STM32F407VGTX_FLASH.ld
│   ├── STM32F407VGTX_RAM.ld
│   └── Images/
├── 0007_HSE_Clock_Measurement/
│   ├── README.md
│   ├── Src/
│   ├── Startup/
│   ├── STM32F407VGTX_FLASH.ld
│   ├── STM32F407VGTX_RAM.ld
│   └── Images/
├── 0008_GPIO_Driver_Configuration/
│   ├── drivers/
│   ├── Src/
│   ├── Startup/
│   ├── STM32F407VGTX_FLASH.ld
│   ├── STM32F407VGTX_RAM.ld
│   └── .project / .cproject
├── README.md
└── .git/
```

## Key Concepts Covered

- Memory-mapped peripheral access
- RCC clock enable and disable logic
- GPIO register layout and configuration
- Alternate function pin mapping
- Bare-metal C driver design
- MCU clock source configuration
- Direct bit manipulation and register masks

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

