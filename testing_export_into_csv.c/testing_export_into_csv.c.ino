#include <SPI.h>
#include <SD.h>

int encoderPin1 = 2;  // for position encoder
int encoderPin2 = 3;

//#define PUL 10  // for servo drives
//#define DIR 11

File myFile;

void setup() {
  pinMode(encoderPin1, INPUT_PULLUP);
  pinMode(encoderPin2, INPUT_PULLUP);

  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);

//  pinMode(PUL, OUTPUT);
//  pinMode(DIR, OUTPUT);
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  String fileName = "encoder.csv";

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  if (SD.exists(fileName)) {
    SD.remove(fileName);
  }
  
  myFile = SD.open("encoder.csv", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to encoder.csv...");
//    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
//  myFile = SD.open("test.txt");
//  if (myFile) {
//    Serial.println("test.txt:");
//
//    // read from the file until there's nothing else in it:
//    while (myFile.available()) {
//      Serial.write(myFile.read());
//    }
//    // close the file:
//    myFile.close();
//  } else {
//    // if the file didn't open, print an error:
//    Serial.println("error opening test.txt");
//  }
}

volatile int lastEncoded = 0;
volatile long encoderValue = 0;
 
long lastencoderValue = 0;
 
int lastMSB = 0;
int lastLSB = 0;

int flag = 1;

void loop() {
  // nothing happens after setup
  Serial.println(encoderValue);

  if (flag == 1) {
    String encoderValueString = String(encoderValue);
    encoderValueString += ",";
  
    myFile = SD.open("encoder.csv", FILE_WRITE);
  
    if (myFile) {
//      Serial.print("Writing to encoder.csv...");
      myFile.print(encoderValueString);
      // close the file:
      myFile.close();
//      Serial.println("done.");
    } else {
      // if the file didn't open, print an error:
      Serial.println("error opening test.txt");
    }
    flag = 0;
  }
}

void updateEncoder(){
  flag = 1;
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit
 
  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value
 
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;
 
  lastEncoded = encoded; //store this value for next time
  
//  encoderValue++;
}


