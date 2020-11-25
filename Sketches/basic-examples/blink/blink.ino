#define FIRST_LIGHT 0
#define SECOND_LIGHT 1

#define PWM_VALUE 250

#define DELAY_TIME_IN_MS 5

void setup() {
  pinMode(FIRST_LIGHT, OUTPUT);
  pinMode(SECOND_LIGHT, OUTPUT);
}

void loop() {
  for (int i = 0; i < PWM_VALUE; i++) {
    setLightsValues(i);
    delay(DELAY_TIME_IN_MS);
  }
  for (int i = PWM_VALUE; i > 0; i--) {
    setLightsValues(i);
    delay(DELAY_TIME_IN_MS);
  }
}

void setLightsValues(int currentPwnValue) {
  analogWrite(FIRST_LIGHT, currentPwnValue);
  analogWrite(SECOND_LIGHT, PWM_VALUE - currentPwnValue);
}
