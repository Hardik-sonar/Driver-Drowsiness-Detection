// Car controller over Bluetooth Classic (SPP) with L298N motors and a buzzer.
//
// The web app sends one line per tick, for example "F0\n":
//   first character  = motion: F forward, B backward, L left, R right, S stop
//   second character = buzzer: 1 on, 0 off
// If no valid line arrives for 1 second, the motors stop and the buzzer turns off.

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled. Enable it in the board settings.
#endif

BluetoothSerial SerialBT;

// L298N inputs: motor 1 = IN1/IN2, motor 2 = IN3/IN4
const int PIN_A = 18;   // IN1
const int PIN_B = 19;   // IN2
const int PIN_C = 21;   // IN3
const int PIN_D = 22;   // IN4

const int BUZZER_PIN = 4;

const unsigned long TIMEOUT_MS = 1000;
unsigned long lastCmd = 0;
String lineBuf;

// dir: 1 forward, -1 backward, 0 stop
void setMotor(int pinIn1, int pinIn2, int dir) {
  digitalWrite(pinIn1, dir == 1);
  digitalWrite(pinIn2, dir == -1);
}

void drive(char motion) {
  switch (motion) {
    case 'F': setMotor(PIN_A, PIN_B,  1); setMotor(PIN_C, PIN_D,  1); break;
    case 'B': setMotor(PIN_A, PIN_B, -1); setMotor(PIN_C, PIN_D, -1); break;
    case 'L': setMotor(PIN_A, PIN_B, -1); setMotor(PIN_C, PIN_D,  1); break;
    case 'R': setMotor(PIN_A, PIN_B,  1); setMotor(PIN_C, PIN_D, -1); break;
    default:  setMotor(PIN_A, PIN_B,  0); setMotor(PIN_C, PIN_D,  0); break;
  }
}

void handleLine(const String& line) {
  if (line.length() < 2) return;
  drive(line[0]);
  digitalWrite(BUZZER_PIN, line[1] == '1' ? HIGH : LOW);
  lastCmd = millis();
}

void setup() {
  Serial.begin(115200);

  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);
  pinMode(PIN_D, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  drive('S');
  digitalWrite(BUZZER_PIN, LOW);

  SerialBT.begin("ESP32-Motor");
  Serial.println("Ready. Pair with 'ESP32-Motor' and connect from the web app.");
}

void loop() {
  while (SerialBT.available()) {
    char c = SerialBT.read();
    if (c == '\n') {
      handleLine(lineBuf);
      lineBuf = "";
    } else if (c != '\r' && lineBuf.length() < 16) {
      lineBuf += c;
    }
  }

  // Safety: stop everything if the web app stops sending
  if (millis() - lastCmd > TIMEOUT_MS) {
    drive('S');
    digitalWrite(BUZZER_PIN, LOW);
  }
}
