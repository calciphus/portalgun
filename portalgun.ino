/*
 * Arduino Nano Board Configuration:
 * Rotary Encoder: Pins D2 D3
 * Serial: 
 *    A4 Data
 *    A5 Clock
 * 
 */

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_AlphaNum4 displayScreen = Adafruit_AlphaNum4();

static int pinA = 2; // Our first hardware interrupt pin is digital pin 2
static int pinB = 3; // Our second hardware interrupt pin is digital pin 3
volatile byte aFlag = 0; // let's us know when we're expecting a rising edge on pinA to signal that the encoder has arrived at a detent
volatile byte bFlag = 0; // let's us know when we're expecting a rising edge on pinB to signal that the encoder has arrived at a detent (opposite direction to when aFlag is set)
volatile byte encoderPos = 0; //this variable stores our current value of encoder position. Change to int or uin16_t instead of byte if you want to record a larger range than 0-255
volatile byte oldEncPos = 0; //stores the last encoder position value so we can compare to the current reading and see if it has changed (so we know when to print to the serial monitor)
volatile byte reading = 0; //somewhere to store the direct values we read from our interrupt pins before checking to see if we have moved a whole detent


// Add dimensions here, update both the count and the array below
String current = "C137"; // Default dimension
int dimensionCount = 53;
char const* dimensions[]={"C137","J19Z","46'\\","35-C","C132","C500","304X","R2D2","D18B","0XFF","9DUT","QB3D","GWGZ","P51W","ALQQ","T5'V","YXVK","8-V8","PNY2","FART","PQCC","65-N","J3NI","J-37","08CB","QIMV","5-CL","C3P0","SJ-9","4-W6","ZBVF","J9KS","NBJP","WU7L","ICUP","5GYA","JMR3","G32T","4ZTV","3VXC","5C-V","5CXS","LEYN","NPMF","P15R","3JRS","A-8W","VV2P","I225","99D9","K7RH","53-X","RICK"};

void setup() {
  // Setup for Serial Display  
  displayScreen.begin(0x70);  // pass in the address
  
  // Display default dimension
  displayScreen.writeDigitAscii(0, current.charAt(0));
  displayScreen.writeDigitAscii(1, current.charAt(1));
  displayScreen.writeDigitAscii(2, current.charAt(2));
  displayScreen.writeDigitAscii(3, current.charAt(3));
  displayScreen.writeDisplay();

  // Setup for Roatery Encoder
  pinMode(pinA, INPUT_PULLUP); // set pinA as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  pinMode(pinB, INPUT_PULLUP); // set pinB as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  attachInterrupt(0,PinA,RISING); // set an interrupt on PinA, looking for a rising edge signal and executing the "PinA" Interrupt Service Routine (below)
  attachInterrupt(1,PinB,RISING); // set an interrupt on PinB, looking for a rising edge signal and executing the "PinB" Interrupt Service Routine (below)

  // Serial needed for Debugging
  //Serial.begin(9600);  
  
}

void PinA(){
  cli(); //stop interrupts happening before we read pin values
  reading = PIND & 0xC; // read all eight pin values then strip away all but pinA and pinB's values
  if(reading == B00001100 && aFlag) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    encoderPos --; //decrement the encoder's position count
    bFlag = 0; //reset flags for the next turn
    aFlag = 0; //reset flags for the next turn
  }
  else if (reading == B00000100) bFlag = 1; //signal that we're expecting pinB to signal the transition to detent from free rotation
  sei(); //restart interrupts
}

void PinB(){
  cli(); //stop interrupts happening before we read pin values
  reading = PIND & 0xC; //read all eight pin values then strip away all but pinA and pinB's values
  if (reading == B00001100 && bFlag) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    encoderPos ++; //increment the encoder's position count
    bFlag = 0; //reset flags for the next turn
    aFlag = 0; //reset flags for the next turn
  }
  else if (reading == B00001000) aFlag = 1; //signal that we're expecting pinA to signal the transition to detent from free rotation
  sei(); //restart interrupts
}


void loop() {
  
  if(oldEncPos != encoderPos) {
    oldEncPos = encoderPos;  
    int scopedPosition = encoderPos % dimensionCount;
    
    current = dimensions[scopedPosition];
    //Serial.println(encoderPos);
    //Serial.println(scopedPosition);
  
  
    // Write individual characters to screen from current string
    displayScreen.writeDigitAscii(0, current.charAt(0));
    displayScreen.writeDigitAscii(1, current.charAt(1));
    displayScreen.writeDigitAscii(2, current.charAt(2));
    displayScreen.writeDigitAscii(3, current.charAt(3));
    
    // Write to display
    displayScreen.writeDisplay();

  }

}
