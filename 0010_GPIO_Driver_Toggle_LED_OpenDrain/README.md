# GPIO Driver Toggle LED (Open-Drain) for STM32F407VG

This project builds on the GPIO driver example in `0009_GPIO_Driver_Toggle_LED_PushPull`. It configures the orange user LED on the STM32F407G-DISC1 board as an open-drain output and toggles it using the custom, register-level GPIO driver.

## Project objective

The firmware demonstrates how to:

- configure a GPIO output as open-drain rather than push-pull
- select an internal GPIO pull-up
- reuse the GPIO driver to toggle an LED in a forever loop

## Hardware target

- Board: STM32F407G-DISC1 Discovery Board
- MCU: STM32F407VG
- Toolchain: STM32CubeIDE / GCC ARM Embedded
- LED used: Orange LED on GPIOD pin 13 (`PD13`)

## Project structure

```text
0010_GPIO_Driver_Toggle_LED_OpenDrain/
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
└── README.md
```

## GPIO configuration

`Src/main.c` enables the GPIOD clock and configures `PD13` with:

- Mode: output
- Output type: open-drain
- Speed: medium
- Pull: pull-up

The main loop toggles the pin and uses a software delay loop between transitions.

## Why the LED appears dimmer

The LED can appear comparatively dim in this example because `PD13` is configured as open-drain with the internal GPIO pull-up enabled. An open-drain output actively pulls the pin low, but when set high it becomes high-impedance; the internal pull-up then provides only a weak path to `VDD`. This is not equivalent to the stronger high-side drive of a push-pull output, so the available LED current can be lower.

The STM32F407 electrical characteristics specify the following weak pull-up and pull-down equivalent resistance values:

| Pins | Pull-up condition | Pull-up resistance (min / typ / max) | Pull-down condition | Pull-down resistance (min / typ / max) |
|---|---|---:|---|---:|
| All pins except PA10 and PB12 | `V_IN = V_SS` | 30 / 40 / 50 kΩ | `V_IN = V_DD` | 30 / 40 / 50 kΩ |
| PA10 and PB12 | — | 7 / 10 / 14 kΩ | — | 7 / 10 / 14 kΩ |

For `PD13`, the applicable weak pull-up resistance is 30 kΩ minimum, 40 kΩ typical, and 50 kΩ maximum. The internal pull-up is intended for weak biasing, not as a substitute for a low-resistance LED current path. Actual brightness also depends on the board's LED circuit and component tolerances.

### External pull-up resistor calculation

To disable the internal pull-up and provide a stronger high level, an external pull-up resistor can be connected from `3.3 V (VDD)` to `PD13`. For the board's active-high LED path, the pull-up resistor is in series with the LED and its existing board current-limiting resistor:

```text
3.3 V (VDD)
    |
  R_PULLUP       <-- external resistor
    |
  PD13 ---------- GPIO output (open-drain, internal pull-up disabled)
    |
  R_LED          <-- existing on-board current-limiting resistor
    |
  LED (anode toward PD13)
    |
   GND
```

With this active-high LED path, the LED current flows when the open-drain pin is released (high-impedance). Estimate the current and choose the external resistor using Ohm's law:

```text
I_LED = (VDD - V_F) / (R_PULLUP + R_LED)
R_PULLUP = (VDD - V_F) / I_LED - R_LED
```

Here, `V_F` is the LED's forward voltage and `R_LED` is the series resistor on the board. Both the actual `R_LED` value and `V_F` must be known to calculate current accurately; do not assume a generic board resistor value. In this setup, an external pull-up of approximately `450 Ω` was observed to produce normal-looking LED brightness. Its expected on-state current is:

```text
I_LED = (3.3 V - V_F) / (450 Ω + R_LED)
```

The actual current depends on the board's LED and resistor, but `450 Ω` is a practical observed value for this setup, rather than the earlier illustrative calculation based on an unverified `330 Ω` on-board resistor. Disable the internal pull-up when using the external resistor (`GPIO_NO_PULL_UP_DOWN`) so the internal and external pull-ups are not combined.

When the output is driven low, the GPIO sinks current through the external resistor. With `450 Ω` connected to `3.3 V`, that pull-up current is approximately `(3.3 V - V_OL) / 450 Ω`, or about `7 mA` if `V_OL` is small. Ensure the GPIO sink current is within the STM32F407 and board limits. Do not use a near-zero resistor or connect `VDD` directly to `PD13`; that would increase sink current substantially.

### Source and sink current

- **Source current:** current supplied by a GPIO output from the pin to an external load when the output is high. A push-pull output can source current.
- **Sink current:** current flowing from an external supply or load into the GPIO pin and then to ground when the output is low. An open-drain output can sink current, but cannot actively source current; the external pull-up supplies current when the pin is released.

## Build and usage

1. Open the project in STM32CubeIDE.
2. Ensure `drivers/Inc` is included in the compiler include paths.
3. Build and flash the firmware to the STM32F407G-DISC1 board.
4. Observe the orange LED on `PD13`; compare its brightness with the push-pull example in `0009_GPIO_Driver_Toggle_LED_PushPull`.

## Summary

This exercise highlights how GPIO output type and pull configuration affect real hardware behavior. Open-drain outputs are useful when a signal needs to be pulled low or shared with other devices, but the weak internal pull-up used here can provide less LED current than a push-pull output.
