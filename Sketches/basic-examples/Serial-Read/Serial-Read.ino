#define dhtPin 2
#define ledRPin 13
#define ledGPin 12
#define ledBPin 11

void setup() {
  pinMode(ledRPin, OUTPUT);
  pinMode(ledGPin, OUTPUT);
  pinMode(ledBPin, OUTPUT);

  Serial.begin(9600);

  digitalWrite(ledRPin, 1);
  digitalWrite(ledGPin, 1);
}

void loop() {
  handleLed();
}

void handleLed() {
  if (Serial.available() > 0) {
    int value = Serial.parseInt();

    setLed(0, 0, value);
  }
}

void setLed(int red, int green, int blue) {
  if (red > 0 && red <= 255) {

  }
  if (green > 0 && green <= 255) {

  }
  if (blue > 0 && blue <= 255) {
    analogWrite(ledBPin, blue);
  }
  else {
    exceptionHandler("Blue led", "Value should be more than 0 or lass or equal to 255");
  }
}

void exceptionHandler(String device, String message) {
  String exceptionMessage = device + ": " + message + ".";
  Serial.println(exceptionMessage);
}
