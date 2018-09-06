/*
  Blink
  The basic Energia example.
  Turns on an LED on for one second, then off for one second, repeatedly.
  Change the LED define to blink other LEDs.

  Hardware Required:
    LaunchPad with an LED

  This example code is in the public domain.
*/

// most launchpads have a red LED
#define TRIG P2_0

//see pins_energia.h for more LED definitions
#define ECHO P2_2

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(TRIG, OUTPUT);
  digitalWrite(TRIG, LOW);
  pinMode(ECHO, INPUT_PULLDOWN);
  Serial.begin(9600);
}

unsigned int i = 0;

// the loop routine runs over and over again forever:
void loop() {
//  Serial.write(i);
//  i++;
//  digitalWrite(LEDR, HIGH);   // turn the LED on (HIGH is the voltage level)
//  digitalWrite(LEDG, LOW);
//  delay(200);               // wait for a second
//  digitalWrite(LEDR, LOW);    // turn the LED off by making the voltage LOW
//  digitalWrite(LEDG, HIGH);
//  delay(200);               // wait for a second

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  unsigned int pulseDuration = pulseIn(ECHO, HIGH);
  if (pulseDuration) {
    float dist = float(pulseDuration) * 340/20000;
    Serial.println(dist);
  }

  delay(500);
}
