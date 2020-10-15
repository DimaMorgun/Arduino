#include <IRremote.h>

int IR_PIN = 2;
int SOUND_PIN = 3;
int ECHO_PIN = 4;
int TRIGGER_PIN = 5;
int LIGHT_PIN = 13;

unsigned long int PLAY_CODE = 16761405;
int MAX_DISTANCE = 100;

bool currentState = false;
unsigned int distance = 0;

//NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
IRrecv receiver(IR_PIN);
decode_results result;

void setup() {
  setupPins();

  receiver.enableIRIn();

  Serial.begin(9600);
}

void setupPins() {
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(SOUND_PIN, OUTPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
}

void loop() {
  unsigned long int currentValue = getIRValue();

  if (currentValue != 0) {
    handleState(currentValue);
  }

  handleDistance();

  handleLight();
  handleSound();
}

unsigned long int getIRValue() {
  unsigned long int value = 0;

  if (receiver.decode(&result)) {
    value = result.value;

    delay(50);
    receiver.resume();
  }

  return value;
}

void handleDistance() {
  //https://create.arduino.cc/projecthub/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-036380?ref=similar&ref_id=172503&offset=0
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  int duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration * .0343) / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void handleState(unsigned long int value) {
  if (value != 0 && value == PLAY_CODE) {
    currentState = !currentState;
  }
}

void handleLight() {
  if (currentState) {
    digitalWrite(LIGHT_PIN, HIGH);
  }
  else {
    digitalWrite(LIGHT_PIN, LOW);
  }
}

void handleSound() {
  if (currentState && distance < 80) {
    digitalWrite(SOUND_PIN, HIGH);
    delay(25);
    digitalWrite(SOUND_PIN, LOW);
    int maxDelayTime = 2000;
    int minDelayTime = 50;
    Serial.print("Delay Time = ");
    Serial.println(map(distance, 0, MAX_DISTANCE, minDelayTime, maxDelayTime));
    delay(map(distance, 0, MAX_DISTANCE, minDelayTime, maxDelayTime));
  }
  else {
    digitalWrite(SOUND_PIN, LOW);
  }
}
