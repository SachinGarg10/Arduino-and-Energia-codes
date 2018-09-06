/*
  DigitalReadSerial with on-board Pushbutton
  Reads a digital input on pin 5, prints the result to the serial monitor 
 
  Harware Required:
  * MSP-EXP430G2 LaunchPad
  
  This example code is in the public domain.
 */

// digital pin 5 has a pushbutton attached to it. Give it a name:
int anaButton = P6_3;
int pwmButton = P2_4;

volatile boolean openDoor = false;
volatile boolean stateChange = false;
volatile int interrupTs = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600); // msp430g2231 must use 4800
  // make the on-board pushbutton's pin an input pullup:
//  pinMode(pushButton, INPUT_PULLUP);
pinMode(pwmButton, INPUT_PULLUP);

attachInterrupt(pwmButton, onDoorOpen, CHANGE);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
//  int buttonState = analogRead(anaButton);
//  int value = map(buttonState, 0, 4095, 0, 3300);
//  int rVolt = 3300 - value;
//  int r = 15;
//  int lR = (value * r)/(rVolt);

//  Serial.println(lR);

//int temp = map(value, 0, 3300, 0, 150);
//int temp = 3300*0.1*buttonState/4095;

//  Serial.println(map(buttonState, 0, 4095, 0, 3300));
//Serial.println(temp, 1);
  // print out the state of the button:
//  Serial.println(buttonState);

//  analogWrite(pwmButton, map(buttonState, 0, 4095, 0, 255));
//  delay(100);        // delay in between reads for stability

//  Serial.println();

  if (stateChange) {
    if (openDoor) {
      Serial.println("Dinakar open");
    } else {
      Serial.println("Dinaker CLose");
    }
  }
}

void onDoorOpen() {
  // software debouncing: 0ms to bypass
  if((long) (millis() - interrupTs) >= 90) {
    interrupTs = millis();    

    stateChange = true;
    openDoor = digitalRead(pwmButton);
  }
}



