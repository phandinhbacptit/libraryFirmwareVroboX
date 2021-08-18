#ifndef ROBOT
#define ROBOT

void robotKeepMoving(const char *dir, int speed);
void robotTurnOffAllLights(void);
void robotWaitSecs(float time);
void robotStopMoving(void);
void robotLightsUp(int leftColor, int rightColor);
void robotTurnOnLight(const char *led, int color);
void robotTurnOffLight(const char *led);
void robotPlayNote(int freq, int duration);
void robotShowLedMatrix(const char *value);
float robotDistanceToObstacle(void);
bool robotObstacleAhead(void);
float robotPickedUp(void);
float robotStrengthOfLight(void);
void robotInit(void);
void robotStartup(void);
void robotSetJoyStick(int leftSpeed, int rightSpeed);
void robotSetMotor(int motor, int speed);
void robotSetLed(int idx, int r, int g, int b);
void robotSetTone(int freq, int duration);
float robotGetDistance(void);
float robotGetLineSensor(void);
float robotGetLightSensor(void);
float robotGetSoundSensor(void);

#endif