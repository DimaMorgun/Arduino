void setup() {
  pinMode(PB3, OUTPUT);
}
void loop() {
  digitalWrite(PB3, HIGH);
  delay(500);
  digitalWrite(PB3, LOW);
  delay(500);
}
