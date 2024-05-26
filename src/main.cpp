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

// LED pins for each sensor
#define LED_RED_1 A0
#define LED_GREEN_1 A1
#define LED_RED_2 A2
#define LED_GREEN_2 A3
#define LED_RED_3 A4
#define LED_GREEN_3 A5
#define LED_RED_4 A6
#define LED_GREEN_4 A7

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(115200);

  // Initialize sensor pins
  pinMode(TRIG_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1, INPUT);
  pinMode(TRIG_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);
  pinMode(TRIG_PIN_3, OUTPUT);
  pinMode(ECHO_PIN_3, INPUT);
  pinMode(TRIG_PIN_4, OUTPUT);
  pinMode(ECHO_PIN_4, INPUT);

  // Initialize LED pins
  pinMode(LED_RED_1, OUTPUT);
  pinMode(LED_GREEN_1, OUTPUT);
  pinMode(LED_RED_2, OUTPUT);
  pinMode(LED_GREEN_2, OUTPUT);
  pinMode(LED_RED_3, OUTPUT);
  pinMode(LED_GREEN_3, OUTPUT);
  pinMode(LED_RED_4, OUTPUT);
  pinMode(LED_GREEN_4, OUTPUT);

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

  int ledCount = 0;
  int ledStatus[4];

  // Sensor 1 logic
  if (distance1 < 30.0)
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
  if (distance2 < 30.0)
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
  if (distance3 < 30.0)
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
  if (distance4 < 30.0)
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

  // Update LCD display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SMART PARKING");
  lcd.setCursor(0, 1);
  lcd.print("Empty slots: ");
  lcd.print(ledCount);

  String data = String(ledStatus[0]) + "," + String(ledStatus[1]) + "," + String(ledStatus[2]) + "," + String(ledStatus[3]);
  Serial.println(data);

  delay(2000);
}
