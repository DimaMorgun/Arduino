#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

int potentiometerPin = 3;

int MAX_VALUE = 1024;
int POT_RESISTANCE = 5000;
int DELAY_TIME = 100;

void setup() {
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
  lcd.print("Resistance is - "); // Print the string "Hello World!"
  
}

void loop() {
  String outputPostfix = " Ohm";
  String outputValue = getResistanceValue() + outputPostfix;

  lcd.setCursor(2, 1);
  lcd.print(outputValue);

  delay(DELAY_TIME);
}

int getResistanceValue(){
  int potValue = analogRead(potentiometerPin);

  int resistancePercentage = (MAX_VALUE - potValue) / (MAX_VALUE / 100);
  if(resistancePercentage > 100){
    resistancePercentage = 100;
  }

  return (5000 / 100) * resistancePercentage;
}
