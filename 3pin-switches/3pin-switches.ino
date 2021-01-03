const int STATUS_LED = 18;
const int REFRESH_INTERVAL = 1000;
const bool ENABLE_SERIAL = false;

const int CPIN0 = 16;
const int CPIN1 = 14;
const int CPIN2 = 15;

const int NUM_PINS = 3;
const int PINS[NUM_PINS] = {
  CPIN0, CPIN1, CPIN2,
};

const int NUM_BUTTONS = 6;
const int BUTTON_MAP[NUM_BUTTONS][2] = {
  { CPIN0, CPIN1 },
  { CPIN1, CPIN0 },
  { CPIN1, CPIN2 },
  { CPIN2, CPIN1 },
  { CPIN0, CPIN2 },
  { CPIN2, CPIN0 },
};

bool IS_PRESSED[NUM_BUTTONS] = {
  false,
  false,
  false,
  false,
  false,
  false,
};

bool PREV_PRESSED[NUM_BUTTONS] = {
  false,
  false,
  false,
  false,
  false,
  false,
};

char msg[20];

void setup() {
  pinMode(STATUS_LED, OUTPUT);
  
  reset();

  if (ENABLE_SERIAL) {
    Serial.begin(9600);
    Serial.println("Hello World!");  
  }
}

void loop() {
  bool anything_pressed = false;
  
  for (int i = 0; i < NUM_BUTTONS; ++i) {
    check_button_state(i);

    anything_pressed |= IS_PRESSED[i];

    if (ENABLE_SERIAL) {
      if (!PREV_PRESSED[i] && IS_PRESSED[i]) {
        sprintf(msg, "Button %d pressed", i);
        Serial.println(msg);
      } else if (PREV_PRESSED[i] && !IS_PRESSED[i]) {
        sprintf(msg, "Button %d released", i);
        Serial.println(msg);
      }
    }
    PREV_PRESSED[i] = IS_PRESSED[i];
    
    delayMicroseconds(REFRESH_INTERVAL);
  }

  digitalWrite(STATUS_LED, anything_pressed);
}

void check_button_state(int idx) {
  reset();

  pinMode(BUTTON_MAP[idx][0], INPUT_PULLUP);
  pinMode(BUTTON_MAP[idx][1], OUTPUT);
  
  digitalWrite(BUTTON_MAP[idx][1], LOW);

  int val = digitalRead(BUTTON_MAP[idx][0]);
  IS_PRESSED[idx] = !val;
}

void reset() {
  pinMode(CPIN0, INPUT);
  pinMode(CPIN1, INPUT);
  pinMode(CPIN2, INPUT);

  digitalWrite(CPIN0, LOW);
  digitalWrite(CPIN1, LOW);
  digitalWrite(CPIN2, LOW);
}
