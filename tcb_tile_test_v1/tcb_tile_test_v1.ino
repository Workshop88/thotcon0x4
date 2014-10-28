#include <TcbTile.h>

#include <fontScroll.h>


//#include "LowPower.h"

#define F_CPU 1000000L

byte vns[] = {  DPDS0,
                DPDS0,
                DPDS1,
                DPDS1,
                VERSION_NUM };
 byte ptoggle=0;               
             
const char* welcome = "Greetings THOTCON 0x4 Badge Node ";
const char* checkin = "Proximity Verification Complete: ";
const char* complete = "Congratulations! Tetris Complete!!!";
const char* messages[] = {"Good Morning!","I need a Beer","BURP BURP BURP","Lunch Time!!! Nom Nom Nom","Fork My Dongle","Please Don\"t Hack Me","STFU","Applause","Dinner Time!!! Nom Nom Nom","See you at THOTCON 0x5","GTFO","c7five was here."};
   
void setup()
{
   TcbTileSetup();
   
   vns[0] = DPDS1;
   vns[1] = DPDS1;
   vns[4] = DPDS1;
   
  // displayBootAnim();
               
};

void loop()
{
 // FontScroll fs;
/*
 if (!ptoggle)
 {
      DPDS0 |= _BV(PFDRV1) | _BV(PFDRV0) | _BV(PEDRV1) | _BV(PEDRV0);
      ptoggle=1;
 } else
 {
   DPDS0 = 0x0;
   ptoggle=0;
 }
 */
 //show_screen(font5x8['W'-0x20], 1000);
 scrollMessage(" Hey! ");
 scrollMessage(welcome);
 scrollMessage(checkin);
 scrollMessage(complete);
 for (int i=0; i<13; i++)
 {
   scrollMessage(messages[i]);
 }

 
 show_screen(vns, 100);
 show_screen(vns, 100);
 show_screen(vns, 100);
 show_screen(vns, 100); 
 show_screen(vns, 100);
 show_screen(vns, 100);
 show_screen(vns, 100);
 blank_led_array();

 //LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
 /*
 for (byte i=0; i<9; i++)
 {
   displayAnim(8-i);
 }
 */
 
}; 
