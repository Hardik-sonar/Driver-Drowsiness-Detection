# How to use Driver Sleep Car

Follow the steps in order the first time. After that, you only need steps 5 to 7.

## 1. Wire the car

| L298N pin | Connects to | Purpose |
| --- | --- | --- |
| IN1 | ESP32 GPIO **18** | Motor 1 direction |
| IN2 | ESP32 GPIO **19** | Motor 1 direction |
| IN3 | ESP32 GPIO **21** | Motor 2 direction |
| IN4 | ESP32 GPIO **22** | Motor 2 direction |
| ENA, ENB | Leave the jumpers **on** | Full speed |
| OUT1, OUT2 | Motor 1 | |
| OUT3, OUT4 | Motor 2 | |
| +12V (or your motor voltage) | Battery + | Motor power |
| GND | ESP32 GND **and** battery − | Shared ground (required) |

| Buzzer | Connects to |
| --- | --- |
| Positive (+) | ESP32 GPIO **4** |
| Negative (−) | ESP32 GND |

Notes:
- The ESP32 is powered over USB while you set up. Run the motors from the battery.
- Connect the ESP32 GND to the L298N GND, or the motors won't respond.
- If one wheel spins the wrong way, swap that motor's two wires.

## 2. Flash the car firmware

1. Open **Arduino IDE 2**.
2. Install the board package: **Tools → Board → Boards Manager**, search for **esp32**, install **esp32 by Espressif**.
3. Plug the car's ESP32 into the laptop with USB.
4. **Tools → Board** → **ESP32 Dev Module**. Choose the port that appears when you plug the board in.
5. Open `firmware/car-esp32/car-esp32.ino` and click **Upload**.
6. When it finishes, the car is ready. It won't move until the web app connects.

## 3. (Optional) Set up Telegram alerts

1. Create a bot with [@BotFather](https://t.me/BotFather) on Telegram and copy the token.
2. Find your chat ID (send a message to your bot, then open `https://api.telegram.org/bot<TOKEN>/getUpdates`).
3. Open `firmware/telegram-esp32/telegram-esp32.ino` and fill in:
   - `ssid` and `password` for your Wi-Fi
   - `botToken` and `chatID`
4. Flash it to a **second** ESP32 the same way as step 2.
5. Connect that board to the laptop with USB when you use the web app. Click **Connect Telegram ESP32** in the web app.

Skip this section if you don't need phone alerts. The car works without it.

## 4. Pair the car with your laptop (Windows)

1. Turn the car on. Its ESP32 must be powered and running the firmware.
2. Open **Settings → Bluetooth & devices → Add device → Bluetooth**.
3. Select **ESP32-Motor** and finish pairing. You don't need a PIN.

After pairing, Windows creates a Bluetooth serial port for the car. You'll pick it in the web app. You can check its number in **Device Manager → Ports (COM & LPT)**. Look for **Standard Serial over Bluetooth link** next to ESP32-Motor.

On macOS, pair the car in **System Settings → Bluetooth**. Its port appears in Chrome's picker as a Bluetooth serial device.

## 5. Start the web app

**Windows:** double-click `start_web_app.bat`. Python 3 must be installed (from [python.org](https://www.python.org/downloads/), tick **Add python to PATH**).

**macOS / Linux:** open a terminal in this folder and run:

```bash
sh start_web_app.sh
```

The script opens the web app at **http://localhost:8000/web/**. Use Chrome or Edge.

Keep the window with the server open while you use the app.

## 6. Use the web app

1. **Camera:** allow camera access when Chrome asks. If you miss it, click **Start camera**.
2. **Face tracking:** green boxes should appear on your eyes. The EAR number is about 0.25–0.35 when your eyes are open.
3. **Connect the car:** click **Connect car**, choose **ESP32-Motor** (the Bluetooth serial port) in the list, and click Connect.
4. **Driving:** with **Auto forward** on, the car drives forward.
5. **Manual driving:** untick **Auto forward**. Hold Forward, Back, Left, or Right to move. Release to stop.
6. **Stop:** click **Stop**. This turns off auto forward and halts the car. Tick **Auto forward** again to drive automatically.
7. **Sleep test:** close your eyes for more than 2 seconds. The car stops, the buzzer sounds, and the status shows **Stopped, buzzer on**. Open your eyes to resume.
8. **Telegram:** closing your eyes for 5 seconds sends an alert, if the Telegram ESP32 is connected.

You can change the 2-second and 5-second times, and the EAR threshold, in the **Settings** card.

**Demo mode:** if you have no camera, click **Switch to demo mode** and hold the **Space** bar to close your eyes.

## Troubleshooting

| Problem | What to try |
| --- | --- |
| The page shows "Camera or model unavailable" | Allow camera access in Chrome. Make sure the server is running from this folder, so `face_landmarker.task` is found. |
| ESP32-Motor doesn't appear in Chrome's list | Pair it in Windows Bluetooth settings first. Close other apps that use the car's COM port (including Arduino IDE's serial monitor). Then click Connect car again. |
| "Access to the port is denied" | Another program has the port open. Close the web app's other tab or any serial monitor, then reconnect. |
| Car won't move when connected | Check the battery and the GND connection. Make sure the jumpers on ENA and ENB are on. |
| One wheel doesn't move | Check that wire's connection to the L298N and the matching GPIO pin. |
| No buzzer sound | Check the buzzer's polarity and that it's on GPIO 4. Test it with a short wire from GPIO 4 to 3.3 V. |
| Telegram alert doesn't arrive | Check the Wi-Fi name and password, the bot token, and the chat ID in the Telegram sketch. |
| Web app doesn't load at all | Open the app with the start script, not by double-clicking `index.html`. The model file needs the local server. |
| Face tracking is slow | Use a well-lit room, and close other apps that use the camera. |
