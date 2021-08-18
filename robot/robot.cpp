#if (1) 
#define ROBOX_LOG(...)   Serial.printf(__VA_ARGS__)
#else
#define ROBOX_LOG(...)
#endif

#define MOTOR_TYPE_3
#define VBOT_CHAIN

#include "VbotBoard.h"
#include "robot.h"
#include "FastLED.h"

#define GET 1
#define RUN 2
#define RESET 4
#define START 5

#define ULTRASONIC_SENSOR       1
#define LIGHT_SENSOR_VALUE      3
#define JOYSTICK                5
#define RGBLED                  8
#define TONE                    34
#define LINEFOLLOWER            17

#define LINE_DETECT_MODE      100
#define LINE_CIRCLE_MODE      101
#define SOUND_FOLLOW_MODE     102
#define NORMAL_MODE           103


#define NUM_LEDS 2
#define LED_DATA_PIN 23

enum {
  SET_MOTOR1 = 0,
  SET_MOTOR2,
  SET_MOTOR3,
};

enum {
    LED_ALL = 0,
    LED_LEFT,
    LED_RIGHT
};

enum LineFollow {
    LINE_PICKED = 0,
    LINE_LEFT,
    LINE_RIGHT,
    LINE_CENTER,
    INVALID
};

/* Hardware API */
/*---------------------------------------------------------------------------*/
VnDCMotor           DcMotor1(M1);
VnDCMotor           DcMotorL(M2);
VnDCMotor           DcMotorR(M3);
CRGB                leds[NUM_LEDS];
VnUltrasonicSensor  Ultra(ULTRA);
VnBuzzer            Buzzer;
VnLineFollower      LINE(FLOWLINE);
VnLightSensor       LightSensor(LIGHT_SENSOR);
VnSoundSensor       SoundSensor(SOUND_SENSOR);

void robotInit(void)
{
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++)
    leds[i] = CRGB::Black;
  FastLED.show();  
}

void robotStartup(void) 
{
  int i = 0;
  for (i = 0; i < 5; i++) {
    robotSetLed(0, 255, 0, 0);
    delay(500);
    robotSetLed(0, 0, 0, 0);
    delay(500);
  }
}

void robotSetJoyStick(int leftSpeed, int rightSpeed)
{
  DcMotorL.run(leftSpeed, MOTOR2);
  DcMotorR.run(rightSpeed, MOTOR3);
  ROBOX_LOG("JOYSTICK leftSpeed=%d, rightSpeed=%d\n", leftSpeed, rightSpeed);
}

void robotSetMotor(int motor, int speed)
{
  switch(motor) {
    case SET_MOTOR1:
      DcMotor1.run(speed, MOTOR1);
      break;
    case SET_MOTOR2:
      DcMotorL.run(speed, MOTOR2);
      break;
    case SET_MOTOR3:
      DcMotorR.run(speed, MOTOR3);
      break;
  }
  ROBOX_LOG("MOTOR motor=%d, speed=%d\n", motor, speed);
}

static int rgb2HexColor(int r, int g, int b)
{
    return (r<<16) | (g<<8) | b;
}

void robotSetLed(int idx, int r, int g, int b)
{
  if (idx < 0 || idx > NUM_LEDS)
    return;

  int color = rgb2HexColor(r, g, b);
  if (idx == 0) {
    for (int i = 0; i < NUM_LEDS; i++)
    leds[i] = color;
  } else {
      leds[idx - 1] = color;
  }
  FastLED.show();
  
  ROBOX_LOG("LEd idx=%d, r=%d, g=%d, b=%d\n", idx, r, g, b);
}

void robotSetLed(int idx, int color)
{
  if (idx < 0 || idx > NUM_LEDS)
    return;

  if (idx == 0) {
    for (int i = 0; i < NUM_LEDS; i++)
    leds[i] = color;
  } else {
      leds[idx - 1] = color;
  }
  FastLED.show();
  
  ROBOX_LOG("LEd idx=%d, color=%d\n", idx, color);
}

void robotSetTone(int freq, int duration)
{
  Buzzer.tone(freq, duration);
  ROBOX_LOG("TONE freq=%d, duration=%d\n", freq, duration);
}

float robotGetDistance(void)
{
  float distance = (float)Ultra.distanceCm(200);
  ROBOX_LOG("DISTANCE distance=%.2f\n", distance);
  return distance;
}
/*

*/
float robotGetLineSensor(void)
{
  float line = (float)(LINE.readSensor1() * 2 + LINE.readSensor2());
  ROBOX_LOG("LINE LEFT=%d RIGHT=%d\n", LINE.readSensor1(), LINE.readSensor2());
  return line;
}

float robotGetLightSensor(void)
{
  float value = (float)(LightSensor.read() * 1000 / 4095);
  ROBOX_LOG("LIGHTSENSOR VAL=%.1f   %d\n", value, LightSensor.read());
  return value;
}

float robotGetSoundSensor(void)
{
  float value = SoundSensor.readSoundSignal();
  ROBOX_LOG("SOUNDSENSOR VAL=%.1f \n", value);
  return value;
}

/* Robot block */
/*---------------------------------------------------------------------------*/
void robotKeepMoving(const char *dir, int speed) 
{
    int leftSpeed = 0;
    int rightSpeed = 0;

    ROBOX_LOG("robotKeepMoving: %s %d\n", dir, speed);
    if (!strcmp(dir, "FORWARD")) {
        leftSpeed = (int)(0 - speed);
        rightSpeed = (int)(speed);
    }
    else if (!strcmp(dir, "BACKWARD")) {
        leftSpeed = (int)(speed);
        rightSpeed = (int)(0 - speed);
    }
    else if (!strcmp(dir, "LEFT")) {
        rightSpeed = (int)(speed);
    }
    else if (!strcmp(dir, "RIGHT")) {
        leftSpeed = (int)(0 - speed);
    }
    robotSetJoyStick(leftSpeed, rightSpeed);
}

void robotTurnOffAllLights(void)
{
    ROBOX_LOG("robotTurnOffAllLights\n");
    robotSetLed(0, 0, 0, 0);
}

void robotWaitSecs(float time) 
{
    ROBOX_LOG("robotWaitSecs: %f\n", time);
    delay(time * 1000);
}

void robotStopMoving(void)
{
    ROBOX_LOG("robotTurnOffAllLights\n");
    robotSetJoyStick(0, 0);
}

void robotLightsUp(int leftColor, int rightColor)
{
    ROBOX_LOG("robotLightsUp %d %d\n", leftColor, rightColor);
    robotSetLed(LED_LEFT, leftColor);
    robotSetLed(LED_RIGHT, rightColor);
}

void robotTurnOnLight(const char *led, int color)
{
    ROBOX_LOG("robotTurnOnLight %s %d\n", led, color);

    if (!strcmp(led, "ALL")) {
        robotSetLed(LED_ALL, color);
    }
    else if (!strcmp(led, "LEFT")) {
        robotSetLed(LED_LEFT, color);
    }
    else if (!strcmp(led, "RIGHT")) {
        robotSetLed(LED_RIGHT, color);
    }    
}

void robotTurnOffLight(const char *led)
{
    ROBOX_LOG("robotTurnOffLight %s\n", led);

    if (!strcmp(led, "ALL")) {
        robotSetLed(LED_ALL, 0);
    }
    else if (!strcmp(led, "LEFT")) {
        robotSetLed(LED_LEFT, 0);
    }
    else if (!strcmp(led, "RIGHT")) {
        robotSetLed(LED_RIGHT, 0);
    }    
}

void robotPlayNote(int freq, int duration)
{
    ROBOX_LOG("robotPlayNote %d %d\n", freq, duration);
    robotSetTone(freq, duration);
}

void robotShowLedMatrix(const char *value)
{
    ROBOX_LOG("robotShowLedMatrix %s\n", value);
}

float robotDistanceToObstacle(void)
{
  float distance = (float)Ultra.distanceCm(200);
  ROBOX_LOG("robotDistanceToObstacle distance=%.2f\n", distance);
  return distance;
}

bool robotObstacleAhead(void)
{
  float distance = (float)Ultra.distanceCm(200);
  ROBOX_LOG("robotObstacleAhead distance=%.2f\n", distance);
  return (distance < 10);
}

float robotPickedUp(void)
{
  float line = (float)(LINE.readSensor1() * 2 + LINE.readSensor2());
  ROBOX_LOG("robotPickedUp line=%d\n", line);
  return (line == LINE_PICKED);
}

float robotStrengthOfLight(void)
{
  float value = (float)(LightSensor.read() * 1000 / 4095);
  ROBOX_LOG("robotStrengthOfLight LEFT=%.1f   %d\n", value, LightSensor.read());
  return value;
}
