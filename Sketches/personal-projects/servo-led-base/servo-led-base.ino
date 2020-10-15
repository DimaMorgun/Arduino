int ledPin = 13;
int servoPin = 5;
int potPin = 0;
bool isOddStep = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(servoPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  manageLight();
  manageServo();

  isOddStep = !isOddStep;
  delay(500);
}

void manageServo(){
  int stepValue = 60;
  
  if(isOddStep)
  {
    analogWrite(servoPin, stepValue);
  }
  else{
    analogWrite(servoPin, -stepValue);
  }
}

void manageLight(){
  if(isOddStep){
    digitalWrite(ledPin, LOW);
  }
  else
  {
    digitalWrite(ledPin, HIGH);
  }
}
