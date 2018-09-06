#define encoderA 2
#define encoderB 3

int encoderPos = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial) {
    // wait until Serial communication started
    Serial.println("Serial Connecting...");
  }

  pinMode(encoderA, INPUT_PULLUP);
  pinMode(encoderB, INPUT_PULLUP);
  attachInterrupt(0, encoderSt, CHANGE);
}

void loop() {
  Serial.println(encoderPos);
}

void encoderSt() {
  if (digitalRead(encoderA) == digitalRead(encoderB)) {
    encoderPos++;
  } else {
    encoderPos--;
  }
  Serial.println(encoderPos);
}
