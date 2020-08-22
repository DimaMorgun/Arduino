// DHT -> https://github.com/adafruit/DHT-sensor-library
// Tutorials (4 digit 7 segment display) -> https://osoyoo.com/2017/08/08/arduino-lesson-4-digit-7-segment-led-display/#:~:text=A%204%2Ddigit%207%2Dsegment,4%20digits%20from%20D1%2DD4.
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 14
#define DHTTYPE DHT11

int a = 2;
int b = 3;
int c = 4;
int d = 5;
int e = 6;
int f = 7;
int g = 8;
int d1 = 9;
int d2 = 10;
int d3 = 11;
int d4 = 12;

DHT_Unified dht(DHTPIN, DHTTYPE);

long n = 0;// n represents the value displayed on the LED display. For example, when n=0, 0000 is displayed. The maximum value is 9999.
int x = 100;
int count = 0;//Set count=0. Here count is a count value that increases by 1 every 0.1 second, which means 1 second is counted when the value is 10
int del = 3;//Set del as 5; the value is the degree of fine tuning for the clock

void setup() {
  Serial.begin(9600);

  setupDHT();
  setup4SegmentDisplay();
}

void setupDHT() {
  dht.begin();
}

void setup4SegmentDisplay() {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
}

void loop() {
  int temperature = getTemperature();
  int humidity = getHumidity();

  // Represents a value for temp + humidity in format "TTHH" in 4 digit 7 segment screen.
  n = temperature * 100 + humidity;

  clearLEDs();//clear the 7-segment display screen
  pickDigit(0);//Light up 7-segment display d1
  pickNumber((n / 1000)); // get the value of thousand
  delay(del);//delay

  clearLEDs();
  pickDigit(1);
  pickNumber((n % 1000) / 100); // get the value of hundred
  delay(del);

  clearLEDs();//clear the 7-segment display screen
  pickDigit(2);//Light up 7-segment display d3
  pickNumber(n % 100 / 10); //get the value of ten
  delay(del);//delay 5ms

  clearLEDs();
  pickDigit(3);
  pickNumber(n % 10); //Get the value of single digit
  delay(del);
}

void writeResult() {
  Serial.print("-- -- -- -- --\n");

  writeTemperature();
  writeHumidity();
}

void writeTemperature() {
  Serial.print(F("Temperature: "));
  Serial.print(getTemperature());
  Serial.println(F("°C"));
}

float getTemperature() {
  sensors_event_t event;

  dht.temperature().getEvent(&event);

  return event.temperature;
}

void writeHumidity() {
  Serial.print(F("Humidity: "));
  Serial.print(getHumidity());
  Serial.println(F("%"));
}

float getHumidity() {
  sensors_event_t event;

  dht.humidity().getEvent(&event);

  return event.relative_humidity;
}

/**************************************/

void pickDigit(int x) //light up a 7-segment display
{
  //The 7-segment LED display is a common-cathode one. So also use digitalWrite to  set d1 as high and the LED will go out
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);

  switch (x)
  {
    case 0:
      digitalWrite(d1, LOW);//Light d1 up
      break;
    case 1:
      digitalWrite(d2, LOW); //Light d2 up
      break;
    case 2:
      digitalWrite(d3, LOW); //Light d3 up
      break;
    default:
      digitalWrite(d4, LOW); //Light d4 up
      break;
  }
}
//The function is to control the 7-segment LED display to display numbers. Here x is the number to be displayed. It is an integer from 0 to 9
void pickNumber(int x)
{
  switch (x)
  {
    default:
      zero();
      break;
    case 1:
      one();
      break;
    case 2:
      two();
      break;
    case 3:
      three();
      break;
    case 4:
      four();
      break;
    case 5:
      five();
      break;
    case 6:
      six();
      break;
    case 7:
      seven();
      break;
    case 8:
      eight();
      break;
    case 9:
      nine();
      break;
  }
}
void clearLEDs() //clear the 7-segment display screen
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void zero() //the 7-segment led display 0
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
}

void one() //the 7-segment led display 1
{
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void two() //the 7-segment led display 2
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}
void three() //the 7-segment led display 3
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}

void four() //the 7-segment led display 4
{
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void five() //the 7-segment led display 5
{
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void six() //the 7-segment led display 6
{
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void seven() //the 7-segment led display 7
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void eight() //the 7-segment led display 8
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void nine() //the 7-segment led display 9
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
/*******************************************/
void add()
{
  // Toggle LED
  count ++;
  if (count == 10)
  {
    count = 0;
    n++;
    if (n == 10000)
    {
      n = 0;
    }
  }
}
