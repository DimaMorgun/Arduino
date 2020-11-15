void setup() {
  Serial.begin(9600);
  Serial.println("Started.");
  
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  
  Serial.println("Cycle done.");
}
