/*
  LED Array POC Code
 
Driving an 8x5 LED array with 13 digital output pins
  
 
  The circuit:
   * LEDs from pins 0 through 12 to ground
 
 created 10 Jan 2013
 by Rudy

This is likely very wrong, fix as necessary. 
 */


// these constants won't change:

const int driveCount = 13;    // the number of LED control pins

int ledPins[] = { 
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };   // an array of pin numbers to which LEDs are attached


void setup() {
  // loop over the pin array and set them all to output:
  for (int thisLed = 0; thisLed < driveCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT); 
  }
}

void loop() {



  // loop over the LED array edges:
  for (int thisLed = 0; thisLed < driveCount; thisLed++) {
      delay(200);
      digitalWrite(ledPins[thisLed], HIGH);
 
    }
    
 //loop over LED col and row select:
 for (int colLed = 0; colLed < 4; colLed++) {
    for (int rowLed = 5; rowLed < 13; rowLed++) {
                  delay(200);
                   digitalWrite(ledPins[colLed], HIGH);    
                   digitalWrite(ledPins[rowLed], LOW);
               }
  }  
}



