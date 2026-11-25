# Driver Sleep Car

A small robot car that stops itself when the driver falls asleep.

A laptop webcam watches your eyes. If your eyes stay closed for **2 seconds**, the car stops and its buzzer sounds until you open your eyes again. If they stay closed for **5 seconds**, an optional Telegram alert is sent to your phone.

## How it works

```
 Laptop (Chrome / Edge)                       Car
 ┌──────────────────────────┐   Bluetooth    ┌─────────────────────┐
 │ Web app                  │ ─────────────► │ ESP32 (car)         │
 │ • webcam + face tracking │  "F0" / "S1"   │  ├─ L298N → motors  │
 │ • eye closure timer      │                │  └─ GPIO 4 → buzzer │
 │ • auto / manual driving  │                └─────────────────────┘
 │                          │   USB serial   ┌─────────────────────┐
 │                          │ ─────────────► │ ESP32 (Telegram)    │ ──► Telegram
 └──────────────────────────┘   optional     └─────────────────────┘
```

- **Auto forward (default):** the car drives forward while your eyes are open.
- **Eyes closed 2 s:** motors stop, buzzer on. Opening your eyes resumes driving.
- **Eyes closed 5 s:** Telegram alert (optional).
- **Manual mode:** turn auto off and drive with the Forward, Back, Left, and Right buttons.
- **Safety:** if the Bluetooth link drops, the car stops on its own within 1 second.

## What's in this folder

| Path | What it is |
| --- | --- |
| `firmware/car-esp32/car-esp32.ino` | Code for the ESP32 on the car (Bluetooth, motors, buzzer) |
| `firmware/telegram-esp32/telegram-esp32.ino` | Optional code for a second ESP32 that sends Telegram alerts |
| `web/index.html` | The web app (camera, eye tracking, car control) |
| `face_landmarker.task` | MediaPipe face model used by the web app. Keep it here. |
| `start_web_app.bat` | Starts the web app on Windows |
| `start_web_app.sh` | Starts the web app on macOS and Linux |
| `USAGE.md` | Step-by-step setup and use |
| `video/explainer.mp4` | 5-minute explainer video with narration (stored with Git LFS) |
| `docs/Project-Report.docx` | Project report |
| `docs/Presentation.pptx` | Project presentation |
| `REFERENCES.md` | Research papers we used |

## Parts

- 1 × ESP32 DevKit (classic ESP32 with 30 or 38 pins)
- 1 × L298N motor driver
- 2 × DC gear motors with wheels
- 1 × active buzzer (3.3–5 V)
- Battery pack for the motors (the L298N needs more power than the ESP32 USB supply)
- Jumper wires
- A laptop with a webcam and Bluetooth, running Chrome or Edge
- Optional: a second ESP32 and a Telegram bot for phone alerts

## Software

- [Arduino IDE 2](https://www.arduino.cc/en/software) with the **esp32 by Espressif** board package (version 3.x)
- Chrome or Edge on the laptop
- Python 3 (only needed to run the web app's local server)
- Internet access on the laptop, because the face tracking library loads from a CDN

## Status

This is a prototype built to show the idea. Test the car with its wheels off the ground first. Do not use it on real roads or as a replacement for a driver's own alertness.
