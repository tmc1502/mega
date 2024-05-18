#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


#define TRIG_PIN_1 8
#define ECHO_PIN_1 9

#define TRIG_PIN_2 10
#define ECHO_PIN_2 11

#define TRIG_PIN_3 12
#define ECHO_PIN_3 13

#define TRIG_PIN_4 14
#define ECHO_PIN_4 15

#define LED_PIN_1 2
#define LED_PIN_2 3
#define LED_PIN_3 4
#define LED_PIN_4 5

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  

  pinMode(TRIG_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1, INPUT);
  pinMode(TRIG_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);
  pinMode(TRIG_PIN_3, OUTPUT);
  pinMode(ECHO_PIN_3, INPUT);
  pinMode(TRIG_PIN_4, OUTPUT);
  pinMode(ECHO_PIN_4, INPUT);
  
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);
  pinMode(LED_PIN_4, OUTPUT);

  lcd.init();
  lcd.backlight();
}

float getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;
  
  return distance;
}

void loop() {
  float distance1 = getDistance(TRIG_PIN_1, ECHO_PIN_1);
  float distance2 = getDistance(TRIG_PIN_2, ECHO_PIN_2);
  float distance3 = getDistance(TRIG_PIN_3, ECHO_PIN_3);
  float distance4 = getDistance(TRIG_PIN_4, ECHO_PIN_4);

  int ledCount = 0;

  if (distance1 < 30.0) {
    digitalWrite(LED_PIN_1, LOW);  
  } else {
    digitalWrite(LED_PIN_1, HIGH); 
    ledCount++;
  }

  if (distance2 < 30.0) {
    digitalWrite(LED_PIN_2, LOW);  
  } else {
    digitalWrite(LED_PIN_2, HIGH); 
    ledCount++;
  }

  if (distance3 < 30.0) {
    digitalWrite(LED_PIN_3, LOW); 
  } else {
    digitalWrite(LED_PIN_3, HIGH);
    ledCount++;
  }

  if (distance4 < 30.0) {
    digitalWrite(LED_PIN_4, LOW);  
  } else {
    digitalWrite(LED_PIN_4, HIGH); 
    ledCount++;
  }



  //LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SMART PARKING");
  lcd.setCursor(0, 1);
  lcd.print("Empty slots: ");
  lcd.print(ledCount);


  delay(500);
}