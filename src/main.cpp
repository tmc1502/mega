#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Sensor pins
#define TRIG_PIN_1 2
#define ECHO_PIN_1 3

#define TRIG_PIN_2 4
#define ECHO_PIN_2 5

#define TRIG_PIN_3 6
#define ECHO_PIN_3 7

#define TRIG_PIN_4 8
#define ECHO_PIN_4 9

#define TRIG_PIN_5 10
#define ECHO_PIN_5 11

#define TRIG_PIN_6 12
#define ECHO_PIN_6 13

#define TRIG_PIN_7 22
#define ECHO_PIN_7 23

#define TRIG_PIN_8 24
#define ECHO_PIN_8 25

#define TRIG_PIN_9 26
#define ECHO_PIN_9 27

#define TRIG_PIN_10 28
#define ECHO_PIN_10 29

// LED pins for each sensor
#define LED_RED_1 A0
#define LED_GREEN_1 A1 

#define LED_RED_2 A2
#define LED_GREEN_2 A3

#define LED_RED_3 A4
#define LED_GREEN_3 A5

#define LED_RED_4 A6
#define LED_GREEN_4 A7

#define LED_RED_5 A8
#define LED_GREEN_5 A9

#define LED_RED_6 A10
#define LED_GREEN_6 A11

#define LED_RED_7 A12
#define LED_GREEN_7 A13

#define LED_RED_8 A14
#define LED_GREEN_8 A15

#define LED_RED_9 30
#define LED_GREEN_9 31

#define LED_RED_10 32
#define LED_GREEN_10 33

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(115200);

  // Initialize sensor pins
//A
  pinMode(TRIG_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1, INPUT);
  pinMode(TRIG_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);
  pinMode(TRIG_PIN_3, OUTPUT);
  pinMode(ECHO_PIN_3, INPUT);
  pinMode(TRIG_PIN_4, OUTPUT);
  pinMode(ECHO_PIN_4, INPUT);
  pinMode(TRIG_PIN_5, OUTPUT);
  pinMode(ECHO_PIN_5, INPUT);
//B
  pinMode(TRIG_PIN_6, OUTPUT);
  pinMode(ECHO_PIN_6, INPUT);
  pinMode(TRIG_PIN_7, OUTPUT);
  pinMode(ECHO_PIN_7, INPUT);
  pinMode(TRIG_PIN_8, OUTPUT);
  pinMode(ECHO_PIN_8, INPUT);
  pinMode(TRIG_PIN_9, OUTPUT);
  pinMode(ECHO_PIN_9, INPUT);
  pinMode(TRIG_PIN_10, OUTPUT);
  pinMode(ECHO_PIN_10, INPUT);

  // Initialize LED pins
  //A
  pinMode(LED_RED_1, OUTPUT);
  pinMode(LED_GREEN_1, OUTPUT);
  pinMode(LED_RED_2, OUTPUT);
  pinMode(LED_GREEN_2, OUTPUT);
  pinMode(LED_RED_3, OUTPUT);
  pinMode(LED_GREEN_3, OUTPUT);
  pinMode(LED_RED_4, OUTPUT);
  pinMode(LED_GREEN_4, OUTPUT);
  pinMode(LED_RED_5, OUTPUT);
  pinMode(LED_GREEN_5, OUTPUT);
  //B
  pinMode(LED_RED_6, OUTPUT);
  pinMode(LED_GREEN_6, OUTPUT);
  pinMode(LED_RED_7, OUTPUT);
  pinMode(LED_GREEN_7, OUTPUT);
  pinMode(LED_RED_8, OUTPUT);
  pinMode(LED_GREEN_8, OUTPUT);
  pinMode(LED_RED_9, OUTPUT);
  pinMode(LED_GREEN_9, OUTPUT);
  pinMode(LED_RED_10, OUTPUT);
  pinMode(LED_GREEN_10, OUTPUT);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
}

float getDistance(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;

  return distance;
}

void loop()
{
  float distance1 = getDistance(TRIG_PIN_1, ECHO_PIN_1);
  float distance2 = getDistance(TRIG_PIN_2, ECHO_PIN_2);
  float distance3 = getDistance(TRIG_PIN_3, ECHO_PIN_3);
  float distance4 = getDistance(TRIG_PIN_4, ECHO_PIN_4);
  float distance5 = getDistance(TRIG_PIN_5, ECHO_PIN_5); // New distance
  float distance6 = getDistance(TRIG_PIN_6, ECHO_PIN_6); // New distance
  float distance7 = getDistance(TRIG_PIN_7, ECHO_PIN_7); // New distance
  float distance8 = getDistance(TRIG_PIN_8, ECHO_PIN_8); // New distance
  float distance9 = getDistance(TRIG_PIN_9, ECHO_PIN_9); // New distance
  float distance10 = getDistance(TRIG_PIN_10, ECHO_PIN_10); // New distance

  int ledCount = 0;
  int ledStatus[10];

  // Sensor 1 logic
  if (distance1 < 10.0)
  {
    digitalWrite(LED_RED_1, HIGH);
    digitalWrite(LED_GREEN_1, LOW);
    ledStatus[0] = 1;
  }
  else
  {
    digitalWrite(LED_RED_1, LOW);
    digitalWrite(LED_GREEN_1, HIGH);
    ledStatus[0] = 0;
    ledCount++;
  }

  // Sensor 2 logic
  if (distance2 < 10.0)
  {
    digitalWrite(LED_RED_2, HIGH);
    digitalWrite(LED_GREEN_2, LOW);
    ledStatus[1] = 1;
  }
  else
  {
    digitalWrite(LED_RED_2, LOW);
    digitalWrite(LED_GREEN_2, HIGH);
    ledStatus[1] = 0;
    ledCount++;
  }

  // Sensor 3 logic
  if (distance3 < 10.0)
  {
    digitalWrite(LED_RED_3, HIGH);
    digitalWrite(LED_GREEN_3, LOW);
    ledStatus[2] = 1;
  }
  else
  {
    digitalWrite(LED_RED_3, LOW);
    digitalWrite(LED_GREEN_3, HIGH);
    ledStatus[2] = 0;
    ledCount++;
  }

  // Sensor 4 logic
  if (distance4 < 10.0)
  {
    digitalWrite(LED_RED_4, HIGH);
    digitalWrite(LED_GREEN_4, LOW);
    ledStatus[3] = 1;
  }
  else
  {
    digitalWrite(LED_RED_4, LOW);
    digitalWrite(LED_GREEN_4, HIGH);
    ledStatus[3] = 0;
    ledCount++;
  }

  // Sensor 5 logic
  if (distance5 < 10.0)
  {
    digitalWrite(LED_RED_5, HIGH);
    digitalWrite(LED_GREEN_5, LOW);
    ledStatus[4] = 1;
  }
  else
  {
    digitalWrite(LED_RED_5, LOW);
    digitalWrite(LED_GREEN_5, HIGH);
    ledStatus[4] = 0;
    ledCount++;
  }

  // Sensor 6 logic
  if (distance6 < 10.0)
  {
    digitalWrite(LED_RED_6, HIGH);
    digitalWrite(LED_GREEN_6, LOW);
    ledStatus[5] = 1;
  }
  else
  {
    digitalWrite(LED_RED_6, LOW);
    digitalWrite(LED_GREEN_6, HIGH);
    ledStatus[5] = 0;
    ledCount++;
  }

  // Sensor 7 logic
  if (distance7 < 10.0)
  {
    digitalWrite(LED_RED_7, HIGH);
    digitalWrite(LED_GREEN_7, LOW);
    ledStatus[6] = 1;
  }
  else
  {
    digitalWrite(LED_RED_7, LOW);
    digitalWrite(LED_GREEN_7, HIGH);
    ledStatus[6] = 0;
    ledCount++;
  }

  // Sensor 8 logic
  if (distance8 < 10.0)
  {
    digitalWrite(LED_RED_8, HIGH);
    digitalWrite(LED_GREEN_8, LOW);
    ledStatus[7] = 1;
  }
  else
  {
    digitalWrite(LED_RED_8, LOW);
    digitalWrite(LED_GREEN_8, HIGH);
    ledStatus[7] = 0;
    ledCount++;
  }

  // Sensor 9 logic
  if (distance9 < 10.0)
  {
    digitalWrite(LED_RED_9, HIGH);
    digitalWrite(LED_GREEN_9, LOW);
    ledStatus[8] = 1;
  }
  else
  {
    digitalWrite(LED_RED_9, LOW);
    digitalWrite(LED_GREEN_9, HIGH);
    ledStatus[8] = 0;
    ledCount++;
  }

  // Sensor 10 logic
  if (distance10 < 10.0)
  {
    digitalWrite(LED_RED_10, HIGH);
    digitalWrite(LED_GREEN_10, LOW);
    ledStatus[9] = 1;
  }
  else
  {
    digitalWrite(LED_RED_10, LOW);
    digitalWrite(LED_GREEN_10, HIGH);
    ledStatus[9] = 0;
    ledCount++;
  }

  // Update LCD display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SMART PARKING");
  lcd.setCursor(0, 1);
  lcd.print("Empty slots: ");
  lcd.print(ledCount);
String data = "A:" + String(ledStatus[0]) + "," + String(ledStatus[1]) + "," + String(ledStatus[2]) + "," + String(ledStatus[3]) + "," + String(ledStatus[4]) + " B:" + String(ledStatus[5]) + "," + String(ledStatus[6]) + "," + String(ledStatus[7]) + "," + String(ledStatus[8]) + "," + String(ledStatus[9]);
Serial.println(data);


  delay(5000);
}

