#define RED_BUTTON_PIN 2
#define GREEN_BUTTON_PIN 3
#define BLUE_BUTTON_PIN 4

#define RED_LIGHT_PIN 10
#define GREEN_LIGHT_PIN 9
#define BLUE_LIGHT_PIN 11

double RedValue = 0;
double GreenValue = 0;
double BlueValue = 0;

int LightMaxValue = 255;
double LightStepValue = 25.5;

bool IsButtonPressed = false;

void setup() {
//  Serial.begin(9600);

  pinMode(RED_BUTTON_PIN, INPUT_PULLUP);
  pinMode(GREEN_BUTTON_PIN, INPUT_PULLUP);
  pinMode(BLUE_BUTTON_PIN, INPUT_PULLUP);

  pinMode(RED_LIGHT_PIN, OUTPUT);
  pinMode(GREEN_LIGHT_PIN, OUTPUT);
  pinMode(BLUE_LIGHT_PIN, OUTPUT);
}

void loop() {
  if (IsButtonPressed) {
    IsButtonPressed = isButtonPressed(RED_BUTTON_PIN)
                      || isButtonPressed(GREEN_BUTTON_PIN)
                      || isButtonPressed(BLUE_BUTTON_PIN);
  }
  else {
    bool isButtonPressHandled = handleButtonPress(RED_BUTTON_PIN, RED_LIGHT_PIN, RedValue)
                                || handleButtonPress(GREEN_BUTTON_PIN, GREEN_LIGHT_PIN, GreenValue)
                                || handleButtonPress(BLUE_BUTTON_PIN, BLUE_LIGHT_PIN, BlueValue);
  }
}

bool handleButtonPress(int buttonPin, int ledPin, double& lightValue) {
  bool isCurrentButtonPressed = isButtonPressed(buttonPin);

  if (isCurrentButtonPressed && !IsButtonPressed) {
    Serial.println(buttonPin + " PRESSED");

    // Removes bounce of button contacts.
    delay(50);
    isCurrentButtonPressed = isButtonPressed(buttonPin);
    IsButtonPressed = true && isCurrentButtonPressed;
    Serial.print(buttonPin);
    Serial.println(" PRESS REGISTERED.");

    if (isCurrentButtonPressed && IsButtonPressed) {
      setLightValue(ledPin, lightValue);

      return true;
    }
  }

  return false;
}

bool isButtonPressed(int buttonPin) {
  return digitalRead(buttonPin) == LOW;
}

void setLightValue(int ledPin, double& lightValue) {
  lightValue += LightStepValue;
  if (lightValue > LightMaxValue) {
    lightValue = 0;
  }

  analogWrite(ledPin, lightValue);

  Serial.print(ledPin);
  Serial.print(" VALUE IS ");
  Serial.print(lightValue);
  Serial.println(";");
}
