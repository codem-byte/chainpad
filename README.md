# 16x2 I2C LCD Cat Runner & Meteor Animation

A quick Arduino sketch that animates a two-tile cat running/flipping across a 16x2 character LCD, followed by a diagonal meteor streak and scattered stars.

## What's in the Code

- **Two-tile cat sprite:** Each animation frame is split into a left and right `5x8` custom character (`cat1`, `cat2`, `cat3`) so the cat spans two columns along the bottom row (`col` and `col + 1`).
- **Frame cycling:** As `col` moves from `0` to `13`, `col % 3` swaps custom character slots `0` and `1` between standing, a tucked flip, and stretching/landing.
- **Meteor & star pass:** After the run, slots `4` and `5` are loaded with a diagonal trail and a sparkle character, stepping across rows 0 and 1 for 10 frames before `loop()` repeats.

## Hardware & Wiring

- Microcontroller (tested/written for standard Arduino/Wire `LiquidCrystal_I2C` setups; if you're using an ESP8266, don't forget `Wire.begin(SDA, SCL)` in `setup()` since this snippet only calls `lcd.init()`)
- 16x2 character LCD with an I2C backpack (address set to `0x27` in the sketch; try `0x3F` if yours uses that)
- Jumper wires

| LCD Pin | Controller Pin |
| :--- | :--- |
| `VCC` | `5V` (or `3.3V` depending on backpack/logic) |
| `GND` | `GND` |
| `SDA` | `SDA` (`A4` on Uno, `GPIO 4` / `D2` on ESP8266) |
| `SCL` | `SCL` (`A5` on Uno, `GPIO 5` / `D1` on ESP8266) |

## Setup & Libraries

1. Install **LiquidCrystal I2C** in the Arduino IDE Library Manager (`Wire.h` is built in).
2. Check your backpack's I2C address if nothing shows up—change `0x27` to `0x3F` on line 4 if needed.
3. Adjust contrast with the little potentiometer on the back of the I2C module if the backlight is on but blocks/text are faint.

## Tweaking Timing & Speed

- **Cat speed:** Change `delay(120)` in the first `for` loop (lower is faster).
- **Meteor speed:** Change `delay(90)` in the second `for` loop.
- **Custom shapes:** Edit the `B00000`–`B11111` rows in any of the `byte ...[8]` arrays to change how the cat or particles look.

## Note on `lcd.clear()` & `createChar()`

Calling `lcd.clear()` and `lcd.createChar()` inside every loop step is fine for a small demo like this, though on some I2C LCD backpacks frequent clears can cause a slight flicker and rewriting CGRAM every frame takes a few extra milliseconds over I2C. If you want smoother motion later, you can load the custom characters once and overwrite only the changed cells instead of clearing the whole screen.

## Wiring
<img width="1919" height="1038" alt="image" src="https://github.com/user-attachments/assets/edb2bca2-1497-4e09-8ef7-af52a774b0b4" />
