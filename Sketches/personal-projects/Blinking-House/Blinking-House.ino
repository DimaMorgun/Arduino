// CONNECTIONS:
// DS1302 CLK/SCLK --> A0
// DS1302 DAT/IO   --> A1
// DS1302 RST/CE   --> A2
// DS1302 VCC      --> 5v
// DS1302 GND      --> GND

#include <ThreeWire.h>
#include <RtcDS1302.h>

ThreeWire myWire(A1, A0, A2); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

int RANDOM_MIN_VALUE = 0;
int RANDOM_MAX_VALUE = 100;
int PERCENTAGE_MIN_VALUE = 0;
int PERCENTAGE_MAX_VALUE = 100;
int TIME_START_LIGHT_ON = 17;
int TIME_END_LIGH_ON = 21;
int TIME_START_STAND_ON = 21;
int TIME_END_STAND_ON = 22;
int TIME_START_LIGHT_OFF = 22;
int TIME_END_LIGHT_OFF = 24;
int HOUR_MULTIPLIER = 100;
int CHANCE_DECREASE = 50;
int LIGHTS_COUNT = 14;
//int DELAY_TIME = 1000 * 60;
int DELAY_TIME = 1000 * 30;

int lightPins[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}; // WARNING HERE SHOULD BE "LIGHTS_COUNT" VALUE;
int turnedOnLightPins[14] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; // WARNING HERE SHOULD BE "LIGHTS_COUNT" VALUE;
int usedLights = 0;

void setup ()
{
  for (int i = 0; i < LIGHTS_COUNT; i++) {
    pinMode(lightPins[i], OUTPUT);
  }

  Serial.begin(9600);
}

void loop ()
{
  RtcDateTime dateTime = Rtc.GetDateTime();

  if (isInLightOnStage()) {
    handleLightOnStage();
  }
  if (isInLightStandStage()) {
    // Do nothing for now.
  }
  if (isInLightOffStage()) {
    // Do nothing for now.
  }

  Serial.println("Delay...");
  delay(DELAY_TIME);
}

bool isInLightOnStage() {
  int currentTimeValue = getTimeValue();
  int stageStartTimeValue = getLightOnStageStartTime();
  int stageEndTimeValue = getLightOnStageEndTime();

  return stageStartTimeValue <= currentTimeValue && currentTimeValue < stageEndTimeValue;
}

void handleLightOnStage() {
  int timeValue = getTimeValue();
  int startTime = getLightOnStageStartTime();
  int endTime = getLightOnStageEndTime();
  int randomValue = getRandomValue();

  int value = getMappedPercentageValue(timeValue, startTime, endTime);

  if (isInSuccessRange(value, randomValue)) {
    turnOnLight();
  }
}

int getLightOnStageStartTime() {
  return TIME_START_LIGHT_ON * HOUR_MULTIPLIER;
}

int getLightOnStageEndTime() {
  return TIME_END_LIGH_ON * HOUR_MULTIPLIER;
}

void turnOnLight() {
  if (usedLights < LIGHTS_COUNT) {
    int lightPin = -1;
    bool isPinUsed = false;

    do {
      isPinUsed = false;
      int randomPin = random(0, LIGHTS_COUNT);
      lightPin = lightPins[randomPin];

      for (int i = 0; i < LIGHTS_COUNT; i++) {
        if (turnedOnLightPins[i] == lightPin) {
          isPinUsed = true;
          break;
        }
      }
    } while (isPinUsed);

    for (int i = 0; i <= LIGHTS_COUNT; i++) {
      if (turnedOnLightPins[i] == -1) {
        turnedOnLightPins[i] = lightPin;
        usedLights++;
        digitalWrite(lightPin, HIGH);
        break;
      }
    }
  }
}

bool isInLightStandStage() {
  int currentTimeValue = getTimeValue();
  int stageStartTimeValue = TIME_START_STAND_ON * HOUR_MULTIPLIER;
  int stageEndTimeValue = TIME_END_STAND_ON * HOUR_MULTIPLIER;

  return stageStartTimeValue <= currentTimeValue && currentTimeValue < stageEndTimeValue;
}

bool isInLightOffStage() {
  int currentTimeValue = getTimeValue();
  int stageStartTimeValue = TIME_START_LIGHT_OFF * HOUR_MULTIPLIER;
  int stageEndTimeValue = TIME_END_LIGHT_OFF * HOUR_MULTIPLIER;

  return stageStartTimeValue <= currentTimeValue && currentTimeValue < stageEndTimeValue;
}

int getTimeValue() {
  RtcDateTime dateTime = Rtc.GetDateTime();

  return HOUR_MULTIPLIER * dateTime.Hour() + dateTime.Minute();
}

int getRandomValue() {
  return random(RANDOM_MIN_VALUE, RANDOM_MAX_VALUE);
}

int getMappedPercentageValue(int timeValue, int startTime, int endTime) {
  return map(timeValue, startTime, endTime, PERCENTAGE_MIN_VALUE, PERCENTAGE_MAX_VALUE);
}

int isInSuccessRange(int value, int randomValue) {
  return value + randomValue >= PERCENTAGE_MAX_VALUE + CHANCE_DECREASE;
}
