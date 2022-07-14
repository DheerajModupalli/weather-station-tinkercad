// Receiver

#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

#define rxPin 10
#define txPin A5
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);

#define rxPin1 9
#define txPin1 A4
SoftwareSerial mySerial1 =  SoftwareSerial(rxPin1, txPin1);

#define rxPin2 13
#define txPin2 A3
SoftwareSerial mySerial2 =  SoftwareSerial(rxPin2, txPin2);

#define LedGreen 7
#define LedBlue 6
#define LedRed 8
#define a 17.62
#define b 243.12


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int Temp = 0;
int val = 0;
int gas = 0;
int wind = 0;
int Td = 19;
long Hu = 0;

int pre_Temp = 0;
int pre_val = 0;
int pre_gas = -1;
int pre_wind = 0;

void setup() {

  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  mySerial.begin(9600);

  pinMode(rxPin1, INPUT);
  pinMode(txPin1, OUTPUT);
  mySerial1.begin(9600);

  pinMode(rxPin2, INPUT);
  pinMode(txPin2, OUTPUT);
  mySerial2.begin(9600);

  pinMode(LedGreen, OUTPUT);
  pinMode(LedBlue, OUTPUT);
  pinMode(LedRed, OUTPUT);

  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, OUTPUT);


  lcd.begin(16, 2);
}

void loop() {
  if ( digitalRead(A0) == HIGH && digitalRead(A1) == HIGH)
  {
    pre_val = -100;
    pre_gas = -100;
    pre_wind = -100;

    mySerial.listen();
    if (mySerial.available() > 0)
    {
      Temp = mySerial.read();
      Temp = map(Temp, 4, 89, -40, 125);

      if (Temp <= 125 && Temp >= -40)
      {
        if (pre_Temp != Temp)
        {
          lcd.setCursor(13, 0);
          lcd.print("   ");
          lcd.setCursor(10, 1);
          lcd.print("     ");
          //lcd.setCursor(14, 1);
          //lcd.print(" ");
          //lcd.setCursor(0, 0);
          //Serial.println(Temp);
          lcd.setCursor(0, 0);
          lcd.print("Temperature: ");
          lcd.setCursor(12, 0);
          lcd.print(Temp);
          lcd.setCursor(15, 0);
          lcd.print("C");

          Hu = 100 * pow(2.718, ((Td * a / (Td + b)) - (Temp * a / (b + Temp))));
          if (Hu > 0 && Hu <= 100)
          {
            lcd.setCursor(0, 1);
            lcd.print("Humiduty : ");
            lcd.setCursor(12, 1);
            lcd.print(Hu);
            lcd.setCursor(15, 1);
            lcd.print("%");
          }
          else if (Hu > 100) {
            lcd.setCursor(0, 1);
            lcd.print("Humiduty : ");
            lcd.setCursor(12, 1);
            lcd.print(100);
            lcd.setCursor(15, 1);
            lcd.print("%");
          }
          else {
            lcd.setCursor(0, 1);
            lcd.print("Humiduty : ");
            lcd.setCursor(12, 1);
            lcd.print(0);
            lcd.setCursor(15, 1);
            lcd.print("%");
          }
          if ( Temp >= -40 && Temp <= 0)
          {
            digitalWrite(LedBlue, HIGH);
            digitalWrite(LedGreen, LOW);
            digitalWrite(LedRed, LOW);
          }
          else if ( Temp > 0 && Temp <= 30)
          {
            digitalWrite(LedBlue, LOW);
            digitalWrite(LedGreen, HIGH);
            digitalWrite(LedRed, LOW);
          }
          else
          {
            digitalWrite(LedBlue, LOW);
            digitalWrite(LedGreen, LOW);
            digitalWrite(LedRed, HIGH);
          }
          if (Temp > 40) tone(A2, 10000, 100);
          delay(40);
          noTone(A2);
          pre_Temp = Temp ;
        }
      }
    }
  }
  else if ( digitalRead(A0) == HIGH && digitalRead(A1) == LOW)
  {
    digitalWrite(LedBlue, LOW);
    digitalWrite(LedGreen, LOW);
    digitalWrite(LedRed, LOW);

    pre_Temp = -100;
    pre_gas = -100;
    pre_wind = -100;

    mySerial1.listen();
    if (mySerial1.available() > 0)
    {
      val = mySerial1.read();

      //Serial.println(val);
      if (val != pre_val) {
        lcd.setCursor(14, 0);
        lcd.print("  ");
        lcd.setCursor(0, 1);
        lcd.print("                  ");
        lcd.setCursor(0, 0);
        if ( val >= 0 && val <= 149)
        {
          lcd.print("Weather Type : ");
          lcd.setCursor(0, 1);
          lcd.print("Overcast");
          delay(40);
        }
        else if ( val > 149 && val <= 218)
        {
          lcd.print("Weather Type : ");
          lcd.setCursor(0, 1);
          lcd.print("Partially Cloudy");
          delay(40);
        }
        else
        {
          lcd.print("Weather Type : ");
          lcd.setCursor(0, 1);
          lcd.print("Sunny/Clear");
          delay(40);
        }
        pre_val = val;
      }
    }
  }

  else if ( digitalRead(A0) == LOW && digitalRead(A1) == HIGH)
  {
    digitalWrite(LedBlue, LOW);
    digitalWrite(LedGreen, LOW);
    digitalWrite(LedRed, LOW);

    pre_Temp = -100;
    pre_val = -100;
    pre_wind = -100;

    mySerial2.listen();
    if (mySerial2.available() > 0)
    {
      gas = mySerial2.read();
      if ((gas <= 100) && (gas >= 0))
      {
        if (pre_gas != gas) {

          lcd.setCursor(13, 1);
          lcd.print("  ");
          lcd.setCursor(0, 0);
          //Serial.println(gas);
          //gas = map(gas, 0, 255, 0, 100);
          lcd.print("Toxic Gas !");
          lcd.setCursor(11, 0);
          lcd.print("      ");
          lcd.setCursor(0, 1);
          lcd.print("Percentage = ");
          lcd.setCursor(13, 1);
          lcd.print(gas);
          lcd.setCursor(15, 1);
          lcd.print("%");
          if (gas > 45) {
            digitalWrite(LedRed, HIGH);
            tone(A2, 1000, 100);
          }
          delay(40);
          pre_gas = gas;
        }
      }
    }
  }

  else if ( digitalRead(A0) == LOW && digitalRead(A1) == LOW)
  {
    pre_Temp = -100;
    pre_val = -100;
    pre_gas = -100;

    if (Serial.available() > 0)
    {
      wind = Serial.read();
      //wind = map(wind, 0, 255, 0, 74);
      Serial.println(wind);
      if ((wind <= 75) && (wind >= 0))
      {
        if (pre_wind != wind) {
          lcd.setCursor(0, 1);
          lcd.print("   ");
          lcd.setCursor(0, 0);
          //Serial.println(wind);
          lcd.print("Wind Speed :     ");
          lcd.setCursor(0, 1);
          lcd.print(wind);
          lcd.setCursor(3, 1);
          lcd.print("MPH");
          lcd.setCursor(6, 1);
          lcd.print("            ");
          delay(40);
          pre_wind = wind;
        }
      }
    }

  }

  //else
  //{
  // digitalWrite(LedBlue, LOW);
  // digitalWrite(LedGreen, LOW);
  // digitalWrite(LedRed, LOW);
  //noTone(A2);
  //lcd.clear();
  //}
}
