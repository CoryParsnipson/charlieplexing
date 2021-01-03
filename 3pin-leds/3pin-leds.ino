const int CPIN0 = 16;
const int CPIN1 = 14;
const int CPIN2 = 15;

const int NUM_LEDS = 6;
const int REFRESH_INTERVAL = 1000;

const int MODE_MAP[NUM_LEDS][2] = {
  { CPIN0, CPIN1 },
  { CPIN1, CPIN0 },
  { CPIN1, CPIN2 },
  { CPIN2, CPIN1 },
  { CPIN0, CPIN2 },
  { CPIN2, CPIN0 },
};

void setup() {
  reset();
}

void loop() {
  for (int i = 0; i < NUM_LEDS; ++i) {
    drive_pin(i);
    delayMicroseconds(REFRESH_INTERVAL);
  }
}

void drive_pin(int idx) {
  reset();
  
  pinMode(MODE_MAP[idx][0], OUTPUT);
  pinMode(MODE_MAP[idx][1], OUTPUT);

  digitalWrite(MODE_MAP[idx][0], HIGH);
  digitalWrite(MODE_MAP[idx][1], LOW);
}

void reset() {
  pinMode(CPIN0, INPUT);
  pinMode(CPIN1, INPUT);
  pinMode(CPIN2, INPUT);

  digitalWrite(CPIN0, LOW);
  digitalWrite(CPIN1, LOW);
  digitalWrite(CPIN2, LOW);
}
