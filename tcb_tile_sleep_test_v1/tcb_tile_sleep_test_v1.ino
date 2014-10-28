
#include <ZigduinoRadio.h>


#include <TcbTile.h>

#include <fontScroll.h>

#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

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



volatile int f_wdt=1;
const int WDT_176 = 22;
const int WDT_88 = 9; // 11
volatile int wdt_delay_counter = 0;

const int RX_CYCLES = 8; // 80
const int RX_CYCLE_TIME = 100; // milliseconds



/***************************************************
 *  Name:        ISR(WDT_vect)
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Watchdog Interrupt Service. This
 *               is executed when watchdog timed out.
 *
 ***************************************************/
ISR(WDT_vect)
{
  if(f_wdt == 0)
  {
    f_wdt=1;
    wdt_delay_counter++;
  }
  else
  {
    scrollMessage("WDT");
  }
}


/***************************************************
 *  Name:        enterSleep
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Enters the arduino into sleep mode.
 *
 ***************************************************/
void enterSleep(void)
{
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);   /* EDIT: could also use SLEEP_MODE_PWR_DOWN for lowest power consumption. */
  //sleep_enable();
  
  /* Now enter sleep mode. */
  sleep_mode();
  
  /* The program will continue from here after the WDT timeout*/
  //sleep_disable(); /* First thing to do is disable sleep. */
  
  /* Re-enable the peripherals. */
  power_all_enable();
}



/***************************************************
 *  Name:        setup
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Setup for the serial comms and the
 *                Watch dog timeout. 
 *
 ***************************************************/
void wdt_setup()
{
  /*** Setup the WDT ***/
  
  /* Clear the reset flag. */
  MCUSR &= ~(1<<WDRF);
  
  /* In order to change WDE or the prescaler, we need to
   * set WDCE (This will allow updates for 4 clock cycles).
   */
  WDTCSR |= (1<<WDCE) | (1<<WDE);

  /* set new watchdog timeout prescaler value */
  WDTCSR = 1<<WDP0 | 1<<WDP3; /* 8.0 seconds */
  
  /* Enable the WD interrupt (note no reset). */
  WDTCSR |= _BV(WDIE);
  
}

void setup()
{
   TcbTileSetup();
   
   vns[0] = DPDS1;
   vns[1] = DPDS1;
   vns[4] = DPDS1;
   
   show_screen(vns, 500);
   scrollMessage(" B");
   wdt_setup();

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
  if (f_wdt == 1)
  {
     f_wdt = 0;
     ZigduinoRadio.forceState(STATE_SLEEP);
     scrollMessage("(");
     enterSleep();
     scrollMessage(")");
     wdt_disable();
     show_screen(font5x8['1'+wdt_delay_counter-0x20],200);
     if (wdt_delay_counter > WDT_88)
     {   
	wdt_delay_counter = 0;
	scrollMessage(" W88 ");
	ZigduinoRadio.setState(STATE_RX);
	
	/*
	  
	//scrollMessage(welcome);
	
	//scrollMessage(checkin);
	scrollMessage(complete);
	
	for (int i=0; i<13; i++)
	{
	scrollMessage(messages[i]);
	}
	
	*/
	
	for (int j=0; j < RX_CYCLES; j++)
	{
	   delay(RX_CYCLE_TIME);
	   show_screen(vns, 100);
	   show_screen(font5x8['1'+j-0x20],200);
	   blank_led_array();
	}
     }
     wdt_setup();
  }
  else
  {
  }
     
 /*
 for (byte i=0; i<9; i++)
 {
   displayAnim(8-i);
 }
 */
 
}; 
