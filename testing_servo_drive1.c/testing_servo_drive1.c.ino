void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT); // for direction
  pinMode(7, OUTPUT); // for pulses

  Serial.begin(9600);
  while(!Serial) {
//    wait for serial to connect.
  }

  digitalWrite(8, HIGH);
}

unsigned int count = 0;
//unsigned int timeSec = 1;
//float degreeRot = 90;
unsigned int delayPul = 0;
float pul = 0;
float deg = 0;

float inDirDeg = 0;
float inTime = 0;
String direct;
String serialData;

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available()) { 

    count = 0;

    serialData = Serial.readString();

    if (serialData[0] == 'c') {

      direct = "Clockwise";

      inDirDeg = 0;
      
      digitalWrite(8, HIGH);

      int i = 1;
      int chartoint = 0;
      
      while(serialData[i] != '\0') {
        chartoint = serialData[i] - '0';
        inDirDeg = inDirDeg * 10 + chartoint;
        i++;
      }
    } else if (serialData[0] == 'a') {

      direct = "Anticlockwise";

      inDirDeg = 0;
      
      digitalWrite(8, LOW);

      int i = 1;
      int chartoint = 0;
      
      while(serialData[i] != '\0') {
        chartoint = serialData[i] - '0';
        inDirDeg = inDirDeg * 10 + chartoint;
        i++;
      }
    } else if (serialData[0] == 't') {
      
      inTime = 0;

      int i = 1;
      int chartoint = 0;
      
      while(serialData[i] != '\0') {
        chartoint = serialData[i] - '0';
        inTime = inTime * 10 + chartoint;
        i++;
      }

      inDirDeg = 0;
      
    } else {
      inDirDeg = 0;
    }

    Serial.print("Direction: ");
    Serial.println(direct);
    Serial.print("Time: ");
    Serial.println(inTime);
    Serial.print("Degrees: ");
    Serial.println(inDirDeg);
    
//    digitalWrite(8, HIGH);
  
    deg = inDirDeg/360;
    pul = 1600*deg;
    delayPul = inTime*1000000/pul;
  
    Serial.println(pul);
    Serial.println(delayPul);
    
    while (count < pul) {
      digitalWrite(7, LOW);
      delayMicroseconds(delayPul);
      digitalWrite(7, HIGH);
      count++;
    }
  }
}
