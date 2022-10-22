// COMP-10184 – Mohawk College

/**
 * StAuth10187: I Yongxing zhang, 000766325 certify that this material is my original work.
 * No other person's work has been used without due acknowledgement.
 * I have not made my work available to anyone else.
 */
#include <Arduino.h>
// digital input pin definitions
#define PIN_PIR D5
#define PIN_BUTTON D6
// difine all stage
#define ALARM_DISABLE 0
#define ALARM_ENABLE 1
#define ALARM_COUNTDOWN 2
#define ALARM_ACTIVE 3

// buttion delay
#define BUTTON_DELAY 200

int iAlarmStage;
bool bPIR;
bool bBtn;

// *************************************************************
void setup()
{
  // configure the USB serial monitor
  Serial.begin(115200);
  // configure the LED output
  pinMode(LED_BUILTIN, OUTPUT);
  // PIR sensor is an INPUT
  pinMode(PIN_PIR, INPUT);
  // Button is an INPUT
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  delay(10);
  digitalWrite(LED_BUILTIN, true);
  iAlarmStage = ALARM_ENABLE;
  Serial.println("COMP-10184 - Alarm System");
  Serial.println("Student Name: Yongxing Zhang");
  Serial.println("Student ID: 000766325");
  Serial.println();
  Serial.println("alarm now is activitied");
}

// collect button and sensor stage
void collectInputs()
{
  bPIR = digitalRead(PIN_PIR);
  bBtn = digitalRead(PIN_BUTTON);
  delay(BUTTON_DELAY);
}

// base on each stage, button and light react different
void checkAlarmStage()
{
  int lightOn = LOW;
  // collectInputs();
  switch (iAlarmStage)
  {
  case ALARM_DISABLE:
    digitalWrite(LED_BUILTIN, HIGH);

    if (!bBtn)
    {
      iAlarmStage = ALARM_ENABLE;
      Serial.println("Alarm is enable");
    }
    break;
  case ALARM_ENABLE:
    digitalWrite(LED_BUILTIN, HIGH);
    if (bPIR)
    {
      iAlarmStage = ALARM_COUNTDOWN;
      Serial.println("Alarm will activite in 10s ");
    }
    break;

  case ALARM_COUNTDOWN:
    for (int i = 0; i < 80; i++)
    {
      lightOn = !lightOn;
      digitalWrite(LED_BUILTIN, lightOn);
      delay(125);
      collectInputs();
      if (!bBtn)
      {
        iAlarmStage = ALARM_DISABLE;
        Serial.println("Alarm is disabled ");
        break;
      }
      if (i % 8 == 0)
      {
        Serial.println("Alarm will activite in " + String(9 - (i / 8)) + "s ");
      }
    }
    if (iAlarmStage == ALARM_COUNTDOWN)
    {
      iAlarmStage = ALARM_ACTIVE;
      Serial.println("Alarm is activity ");
    }
    break;

  case ALARM_ACTIVE:
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("alarm is active");
    break;
  }
}
// *************************************************************
void loop()
{

  collectInputs();
  checkAlarmStage();
}