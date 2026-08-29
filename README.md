# STM32_Device_Exam

Runnable example projects for the drivers in
[**STM32_Device_Lib**](https://github.com/nguyenkhue2608/STM32_Device_Lib),
one Keil MDK-ARM project per device. The driver sources are **not** copied in —
they are pulled from the library repo as a git submodule at `lib/drivers/` and
compiled straight from there.

- MCU: **STM32F103xB** (Blue Pill / F103C8T6 class) on every example.
- Toolchain: **Keil MDK-ARM (µVision 5)**, ARM Compiler 5 or 6.
- Flash/debug: ST-Link.
- The `.ioc` file in each project is kept for pin reference only; the build is
  driven by Keil, not STM32CubeIDE.

## Getting the code

```bash
git clone --recurse-submodules https://github.com/nguyenkhue2608/STM32_Device_Exam.git
# already cloned without --recurse-submodules:
git submodule update --init --recursive
```

## Repo layout

```
STM32_Device_Exam/
├── lib/drivers/        git submodule -> STM32_Device_Lib
├── <EXAMPLE>/
│   ├── MDK-ARM/<name>.uvprojx   Keil project (open this)
│   ├── Src/  or  Core/Src/      main.c + HAL glue
│   ├── Inc/  or  Core/Inc/      main.h (pin defines)
│   └── Drivers/                 vendored CMSIS + STM32F1 HAL
└── ...
```

Two folder layouts exist: most projects use `Src/` + `Inc/`; `LED7SEG` and
`RFID_RC522` use `Core/Src/` + `Core/Inc/`. That only changes the relative
include depth (`../../lib/...` vs `../../../lib/...`).

## Examples

| Project | Peripheral | Driver (`lib/drivers/…`) | Notes |
|---|---|---|---|
| `BUTTON` | GPIO in | `Button/BUTTON.h` | debounced button read |
| `CLCD_4BIT` | GPIO | `CLCD/CLCD.h` | HD44780 character LCD, 4-bit bus |
| `CLCD_8BIT` | GPIO | `CLCD/CLCD.h` | HD44780, 8-bit bus |
| `CLCD_I2C` | I2C | `CLCD_I2C/CLCD_I2C.h` | HD44780 via PCF8574 backpack |
| `DFPLAYER` | UART | `DFPLAYER/DFPLAYER.h` | DFPlayer Mini MP3 module |
| `DHT11` | GPIO + TIM4_CH1 (input capture) | `DHT/DHT.h` | **DATA wired to PB6** (see below) |
| `DS18B20` | GPIO (DWT µs delay) | `DS18B20/DS18B20.h` | 1-Wire temperature sensor |
| `DS3231` | I2C | `DS3231/DS3231.h` | RTC |
| `JOYSTICK` | ADC | `JOYSTICK/JOYSTICK.h` | 2-axis analog joystick + button |
| `KEYPAD` | GPIO | `KEYPAD/KEYPAD.h` | 3×4 matrix keypad |
| `LCD_OLED_SSD1306` | I2C | `LCD_OLED_SSD1306/OLED_LCD_SSD1306.h` | 128×64 OLED |
| `LCD_TFT_ST7735` | SPI | `LCD_TFT_ST7735/ST7735_SPI.h` | 160×128 TFT |
| `LED7SEG` | GPIO | `LED7SEG/LED7SEG.h` | multiplexed 7-segment (`Core/Src` layout) |
| `RFID_RC522` | SPI | `RC522/RC522.h` (API `MFRC522_*`) | MIFARE reader (`Core/Src` layout) |
| `SRF05` | GPIO + TIM1_CH2 (input capture) | `SRF05/SRF05.h` | ultrasonic range finder |
| `SERVO` | TIM PWM | *local (in `main.c`)* | no shared driver yet |
| `TFT_LCD_ILI9341` | SPI | *local (`lcd.h`)* | no shared driver yet |

## Build & flash one example

1. Open `<EXAMPLE>/MDK-ARM/<name>.uvprojx` in Keil µVision.
2. Project → Build (F7). Driver `.c` files are listed under the
   **Application/User** group and compiled from `..\..\lib\drivers\…`.
3. Flash → Download (F8) with an ST-Link connected.

If a driver header is not found, check the project's
*Options → C/C++ → Include Paths* contains `..\..\lib\drivers\<Device>`.

## Updating the drivers

```bash
cd lib/drivers
git pull origin master
cd ../..
git add lib/drivers
git commit -m "chore: bump drivers"
```

## Notes

- **DHT11 wiring** — the DHT driver needs its DATA pin on a timer channel for
  input capture. PB14 (the original pin) has none on F103, so this example uses
  **PB6 = TIM4_CH1**; move the sensor's DATA wire to PB6.
- **DHT / SRF05** need a timer configured in Input Capture mode, 1 µs/tick
  (Prescaler = `TIMxCLK/1_000_000 − 1`, Period `0xFFFF`); `MX_TIMx_Init()` in
  those `main.c` files already does this.
- **DS18B20** uses the Cortex-M `DWT` cycle counter for its µs delays — no timer,
  but needs a correct `SystemCoreClock`.
- `SERVO` and `TFT_LCD_ILI9341` still carry their driver logic locally; they are
  not yet part of `STM32_Device_Lib`.
- Build output (`*.o`, `*.axf`, `*.hex`, `*.map`, …) is git-ignored — a fresh
  clone has only sources until you build.
