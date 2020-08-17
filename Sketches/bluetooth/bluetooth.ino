#include <SoftwareSerial.h>

SoftwareSerial ArduinoMaster(2, 3);
String msg;

int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(13, LOW);

  Serial.begin(9600);
  ArduinoMaster.begin(9600);
}

void loop() {
  readSerialPort();

  // Send answer to master
  if (msg != "") {
    Serial.print("Master sent : " );
    Serial.println(msg);
    ArduinoMaster.print(msg);
    msg = "";
  }
}

void readSerialPort() {
  while (ArduinoMaster.available()) {
    delay(10);
    if (ArduinoMaster.available() > 0) {
      char c = ArduinoMaster.read();  //gets one byte from serial buffer
      msg += c; //makes the string readString
    }

    if (msg == "1") {
      digitalWrite(13, HIGH);
    } else if (msg == "0") {
      digitalWrite(13, LOW);
    }
  }
  ArduinoMaster.flush();
}
