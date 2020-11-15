#include <LiquidCrystal_I2C.h>
#include <dht.h>

#define dhtPin 2

dht DHT;
LiquidCrystal_I2C lcd(0x27, 16, 2);

int cycleDelayTime = 500;
int dhtDelayTime = 1500;

int temperature;
int humidity;

void setup() {
  lcd.init(); // initialize the lcd
  lcd.backlight();
}

void loop() {
  handlerTemperature();

  lcd.setCursor(0, 0);
  String tempResult = "Temperature " + String(temperature) + "C" + (char)223;
  lcd.print(tempResult);

  lcd.setCursor(3, 1);
  String humidityResult = "Humidity " + String(humidity) + "%";
  lcd.print(humidityResult);

  delay(cycleDelayTime);
}

void handlerTemperature() {
  DHT.read11(dhtPin);
  temperature = DHT.temperature;
  humidity = DHT.humidity;

  delay(dhtDelayTime);
}
