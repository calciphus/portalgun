/*
 * Arduino Nano Board Configuration:
 * Rotary Encoder: Pins D3 D4
 * Serial: 
 *    A4 Data
 *    A5 Clock
 * 
 */

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_AlphaNum4 displayScreen = Adafruit_AlphaNum4();

void setup() {
  Serial.begin(9600);
  
  displayScreen.begin(0x70);  // pass in the address
  displayScreen.writeDisplay();

}


void loop() {
  int dimensionCount = 4;
  char const* dimensions[]={"C137", "J19A", "D18B","0xFF"};

  // Position read from knob. For now, it's 0
  int knobPos = 0;

  
  String current;
  current = dimensions[knobPos];

  // Write individual characters to screen from current string
  displayScreen.writeDigitAscii(0, current.charAt(0));
  displayScreen.writeDigitAscii(1, current.charAt(1));
  displayScreen.writeDigitAscii(2, current.charAt(2));
  displayScreen.writeDigitAscii(3, current.charAt(3));
  delay(200);
  
  // Write to display
  displayScreen.writeDisplay();
}
