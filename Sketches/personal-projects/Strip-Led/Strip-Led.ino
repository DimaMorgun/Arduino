#define R_PIN 3
#define G_PIN 5
#define B_PIN 6

void setup() {
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  analogWrite(R_PIN, 255);
  analogWrite(G_PIN, 10);
  analogWrite(B_PIN, 120);
}
