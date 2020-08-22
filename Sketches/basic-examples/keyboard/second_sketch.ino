#include "Keypad.h"

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

char keys[ROWS][COLS] = {
  {'F', 'L', 'E', 'S'},
  {'R', 'U', 'O', 'Y'},
  {' ', 'K', 'C', 'U'},
  {'F', ' ', 'O', 'G'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.print(key);
  }
}
