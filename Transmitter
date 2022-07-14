// Transmitter

#include <SoftwareSerial.h>

#define rxPin 2
#define txPin 3
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);

#define rxPin1 4
#define txPin1 5
SoftwareSerial mySerial1 =  SoftwareSerial(rxPin1, txPin1);

#define rxPin2 6
#define txPin2 7
SoftwareSerial mySerial2 =  SoftwareSerial(rxPin2, txPin2);

#define rxPin3 8
#define txPin3 9
SoftwareSerial mySerial3 =  SoftwareSerial(rxPin3, txPin3);

int Temp;
int val;
int gas;
int wind;

void setup()
{

  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  mySerial.begin(9600);

  pinMode(rxPin1, INPUT);
  pinMode(txPin1, OUTPUT);
  mySerial1.begin(9600);

  pinMode(rxPin2, INPUT);
  pinMode(txPin2, OUTPUT);
  mySerial2.begin(9600);

  pinMode(rxPin3, INPUT);
  pinMode(txPin3, OUTPUT);
  mySerial3.begin(9600);

  Serial.begin(9600);

}

void loop()
{
  Temp = analogRead(A0);
  Temp = map(Temp, 0, 1024, 0, 255);
  //Serial.println(Temp);
  mySerial.write(Temp);
  delay(10);

  val = analogRead(A1);
  val = map(val, 1, 700, 0, 255);
  mySerial1.write(val);
  //Serial.println(val);
  delay(10);

  gas = analogRead(A2);
  //Serial.println(gas);
  gas = map(gas, 20, 120, 0, 100);
  mySerial2.write(gas);
  //Serial.println(gas);
  delay(10);

  wind = analogRead(A3);
  //Serial.println(wind);
  wind = map(wind, 0, 1023, 0, 74);
  if (wind > 63) {
    mySerial3.write(74);
    Serial.println(74);
  }
  else
  {
    mySerial3.write(wind);
    Serial.println(wind);
  }
  delay(10);
}
