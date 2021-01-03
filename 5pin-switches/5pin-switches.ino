#include <HID-Project.h>
#include <HID-Settings.h>

const int REFRESH_INTERVAL = 1000;
const bool ENABLE_SERIAL = false;

const int NUM_PINS = 5;
const int PINS[NUM_PINS] = { 16, 2, 4, 7, 8 };

const int NUM_BUTTONS = 10; // NUM_PINS * NUM_PINS - NUM_PINS;
const int BUTTON_MAP[NUM_BUTTONS][2] = {
  { PINS[0], PINS[1] },
  { PINS[1], PINS[0] },
  { PINS[1], PINS[2] },
  { PINS[2], PINS[1] },
  { PINS[2], PINS[3] },
  { PINS[3], PINS[2] },
  { PINS[3], PINS[4] },
  { PINS[4], PINS[3] },
  { PINS[0], PINS[2] },
  { PINS[2], PINS[0] },
};

const int pinLXAxis = A1;
const int pinLYAxis = A0;

void setup() {
  pinMode(14, OUTPUT);

  digitalWrite(pinLXAxis, LOW);
  digitalWrite(pinLYAxis, LOW);
  
  reset();

  Gamepad.begin();
}

void loop() {
  for (int i = 0; i < NUM_BUTTONS; ++i) {
    bool button_state = check_button(i);
    digitalWrite(14, button_state);

    if (button_state) {
      Gamepad.press(i + 1);
    } else {
      Gamepad.release(i + 1);
    }

    delayMicroseconds(REFRESH_INTERVAL);
  }

  // analog axes
  int readX = analogRead(pinLXAxis); // store in temporary variables to use in constrain()
  int readY = analogRead(pinLYAxis);

  const int XMIN = 200, XMAX = 880;
  const int YMIN = 125, YMAX = 835;

  // clamp values to observed joystick values
  readX = constrain(readX, XMIN, XMAX);
  readY = constrain(readY, YMIN, YMAX);
    
  Gamepad.xAxis(map(readX, XMIN, XMAX, -32767, 32767)); 
  Gamepad.yAxis(map(readY, YMIN, YMAX, 32767, -32767)); // flip Y axis because I have it oriented upside-down

  Gamepad.write();
}

bool check_button(int idx) {
  reset();

  pinMode(BUTTON_MAP[idx][0], INPUT_PULLUP);
  pinMode(BUTTON_MAP[idx][1], OUTPUT);
  
  digitalWrite(BUTTON_MAP[idx][1], LOW);

  return !digitalRead(BUTTON_MAP[idx][0]);
}

void reset() {
  for (int i = 0; i < NUM_PINS; ++i) {
    pinMode(PINS[i], INPUT);
    digitalWrite(PINS[i], LOW);
  }
}
