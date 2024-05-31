#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>

// Sensor pins
// A
#define TRIG_PIN_1 12
#define ECHO_PIN_1 13

#define TRIG_PIN_2 14
#define ECHO_PIN_2 15

#define TRIG_PIN_3 16
#define ECHO_PIN_3 17

#define TRIG_PIN_4 18
#define ECHO_PIN_4 19

#define TRIG_PIN_5 22
#define ECHO_PIN_5 23

////B
#define TRIG_PIN_6 2
#define ECHO_PIN_6 3

#define TRIG_PIN_7 4
#define ECHO_PIN_7 5

#define TRIG_PIN_8 6
#define ECHO_PIN_8 7

#define TRIG_PIN_9 8
#define ECHO_PIN_9 9

#define TRIG_PIN_10 10
#define ECHO_PIN_10 11

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

#define LED_RED_9 24
#define LED_GREEN_9 25

#define LED_RED_10 26
#define LED_GREEN_10 27

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  lcd.begin(16, 2);
  Serial.begin(115200);

  // Initialize sensor pins
  for (int i = 2; i <= 29; i += 2)
  {
    pinMode(i, OUTPUT);
    pinMode(i + 1, INPUT);
  }

  // Initialize LED pins
  for (int i = A0; i <= A15; i += 2)
  {
    pinMode(i, OUTPUT);
    pinMode(i + 1, OUTPUT);
  }
  for (int i = 30; i <= 33; i += 2)
  {
    pinMode(i, OUTPUT);
    pinMode(i + 1, OUTPUT);
  }

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
  float distances[10];
  distances[0] = getDistance(TRIG_PIN_1, ECHO_PIN_1);
  distances[1] = getDistance(TRIG_PIN_2, ECHO_PIN_2);
  distances[2] = getDistance(TRIG_PIN_3, ECHO_PIN_3);
  distances[3] = getDistance(TRIG_PIN_4, ECHO_PIN_4);
  distances[4] = getDistance(TRIG_PIN_5, ECHO_PIN_5);
  distances[5] = getDistance(TRIG_PIN_6, ECHO_PIN_6);
  distances[6] = getDistance(TRIG_PIN_7, ECHO_PIN_7);
  distances[7] = getDistance(TRIG_PIN_8, ECHO_PIN_8);
  distances[8] = getDistance(TRIG_PIN_9, ECHO_PIN_9);
  distances[9] = getDistance(TRIG_PIN_10, ECHO_PIN_10);

  int ledStatus[10];
  int ledCount = 0;

  for (int i = 0; i < 10; i++)
  {
    if (distances[i] < 10.0)
    {
      digitalWrite(A0 + i * 2, HIGH); // Red LED
      digitalWrite(A1 + i * 2, LOW);  // Green LED
      ledStatus[i] = 1;
    }
    else
    {
      digitalWrite(A0 + i * 2, LOW);  // Red LED
      digitalWrite(A1 + i * 2, HIGH); // Green LED
      ledStatus[i] = 0;
      ledCount++;
    }
  }

  // Update LCD display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BAI GUI XE");
  lcd.setCursor(0, 1);
  lcd.print("SO CHO CON: ");
  lcd.print(ledCount);

  // Prepare JSON data
  StaticJsonDocument<256> jsonDoc;
  JsonArray ledArray = jsonDoc.createNestedArray("ledStatus");
  for (int i = 0; i < 10; i++)
  {
    ledArray.add(ledStatus[i]);
  }
  String jsonData;
  serializeJson(jsonDoc, jsonData);
  Serial.println(jsonData);

  delay(1000);
}
