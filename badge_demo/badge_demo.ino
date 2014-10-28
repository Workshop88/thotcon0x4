/* Initial Badge demo sketch.  Show some animations.  Process some checkins, store in EEPROM */

#include <ZigduinoRadio.h>
#include <EEPROM.h>

#define AREA1 (1<<0)
#define AREA2 (1<<1)
#define AREA3 (1<<2)
#define AREA4 (1<<3)
#define AREA5 (1<<4)
#define AREA6 (1<<5)
#define AREA7 (1<<6)
#define AREA8 (1<<7)

#define rowM ((1<<PD0)|(1<<PD1)|(1<<PD2)|(1<<PD3)|(1<<PD4))

int check_addr = 0x2;

void setup()
{
  ZigduinoRadio.begin(11);
  Serial.begin(9600); // for debugging
  ZigduinoRadio.attachError(errHandle);
  EEPROM.write(check_addr,AREA3);
  //Set ports F and E 0-4 as Output
  DDRF |= 0xFF;
  DDRE |= rowM;
  PORTF &= ~0xFF; //rows
  PORTE &= rowM; //cols
  Serial.println();
  Serial.print("Init Complete:");
  
}

void loop()
{
  int checkins = EEPROM.read(check_addr);
  Serial.print("checkins: ");
  Serial.print(checkins);
  Serial.println();
  Serial.print(DPDS1);
  Serial.println();
  Serial.print(DPDS0);
  
}

void errHandle(radio_error_t err){}
