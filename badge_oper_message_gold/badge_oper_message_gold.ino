/* Workshop 88 Thotcon Badge Project 
 * Badge sketch
 * 
 */

/*EEPROM MAP
  0000  ff ff ff ff ff ff ff ff  ff ff ff ff ff ff ff ff  |................|
        [ADDR]     [ED]         [EC]
  0010  01 03 06 03 02 02 05 01  05 00 ff ff ff ff ff ff  |................|
        [    Checkin Byte Counters   ]

  PACKET  Description:
   +----------------+----------------------+------+---------------------+-----------+
   | 0x01 0x80 0x00 |  0x54 0x48 0x4F 0x54 | 0xNN | 0xNN 0xMM 0XLL ...  | 0xXX 0xYY |
   +----------------+----------------------+------+---------------------+-----------+
       MAC                  frameId          ctrl        options             FCS
*/
#include <ZigduinoRadio.h>
#include <EEPROM.h>
#include <String.h>
#include <fontScroll.h>
#include <TcbTile.h>
#include <avr/sleep.h> //ds_wdt
#include <avr/power.h> //ds_wdt
#include <avr/wdt.h>   //ds_wdt


#define CTL_CHECKIN 0x1
#define CTL_MESSAGE 0x2
#define CTL_REPORT  0x3
#define CTL_SQUELCH 0x4

//Radio
uint16_t grab_address();
void errHandle(radio_error_t);
uint8_t* processFrame(uint8_t, uint8_t*, uint8_t, uint8_t);
void processPacket();

//Memory
void process_checkin(uint16_t);

//Pwr-mgmt
uint16_t readVcc();

//Literal Messages
const char* welcome = "*** Greetings THOTCON 0x4 Badge Node:";
const char* checkin = "*** Proximity Verification Complete: ***";
const char* complete = "*** Congratulations! Tetris Complete!!! ***";
const char* report = "*** Host Communication Established ***";
const char* error = "*** Please Don't Hack Me ***";
const char* messages[] = {"Good Morning!","I need a Beer","BURP BURP BURP","Lunch Time!!! Nom Nom Nom","Fork My Dongle","Please Don\'t Hack Me","STFU","Applause","Dinner Time!!! Nom Nom Nom","See you at THOTCON 0x5","GTFO","c7five was here."};
const char* oper_messages[] = {"Do not cut hair!",//0
			       "Buy c7five a Beer",
			       "Pwnd by VideoMan",//2
			       "PTJ is in your Wi-Fi's",
			       "Untz Untz Untz Chipotle",//4
			       "Rooted by effffn",
			       "Give Sake a High-Five"};//6
const char* threestars = "*** ";
const char* treasure = "YmUgdGhlIGZpcnN0IHRvIHNheSAnY2FiYmFnZScgdG8gdzg4IGluIHRoZSB2aWxsYWdlCg==";
const char* beer = "10 Drink YOURBEER$;20 IF GLASS$ = NULL, THEN GOTO 50;30 TIP$ = TAB$ * .20;40 GOTO 10;50 PRINT \“HELP! I NEED ANOTHER BEER\”;60 GOTO 30";
// thotconID utilities, variables

const int whoAmI = 0; // Who gets the oper badge.
char idString[9] = " 0xDEAD ";
void getIDString(char*);

// Check for "dev mode", read EEPROM 0x88, 0xff is unprogrammed, 0x0 is dev
// (0x88 for Workshop 88)

int standard_mode = 0xFF;

//ds_wdt declarations, definitions (until setup())
/* wdt code adapted from 
http://donalmorrissey.blogspot.com/2010/04/sleeping-arduino-part-5-wake-up-via.html
*/
volatile int f_wdt=1;

// timer duty cycle stuff
const int WDT_90 = 10; // 10
const int WDT_18 = 2;
int wdt_long_delay = WDT_90;
volatile int wdt_delay_counter = 0;

const int RX_CYCLES = 72; // 72 = 8*9 (3x len(lcr_by_row)XS
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
 *  Name:        wdt_setup
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











//Runs on reset
void setup()
{
  TcbTileSetup();

   uint8_t frameHeader[] = {0x01,0x80,0x00,'T','H','O','T'};
   ZigduinoRadio.attachError(errHandle);
  // ZigduinoRadio.attachReceiveFrame(processFrame);
   ZigduinoRadio.begin(20,frameHeader);
 

  ZigduinoRadio.beginTransmission();
  ZigduinoRadio.write(CTL_MESSAGE);
  ZigduinoRadio.write((char *)oper_messages[whoAmI]);
  ZigduinoRadio.endTransmission();
  ZigduinoRadio.flush();
  
   //fancy TC animation
  standard_mode = EEPROM.read(0x88);

  if (standard_mode)
  {
     displayBootAnim();
     blank_led_array();
     scrollMessage(welcome);
     getIDString(idString);
     scrollMessage(idString);
     scrollMessage(threestars);
     wdt_long_delay = WDT_90;
  }
  else
  {
     show_screen(w88, 100);
     wdt_long_delay = WDT_18;
  }

//  scrollMessage(" Dev Mode ");
 //  radio_set_param(RP_CCAMODE(3));
 //  ZigduinoRadio.forceState(STATE_SLEEP);
  /* Serial.begin(9600);
  Serial.println("init complete");
  */

   wdt_setup();  

};

void loop()
{
   char msg[ZR_FIFO_SIZE+1];
   int i = 0;
   int rcv = 0;

   if (f_wdt == 1)
   {              
      f_wdt = 0;  
      show_screen(lcr_by_row[wdt_delay_counter], 100);
      //ZigduinoRadio.forceState(STATE_SLEEP); 
      enterSleep();                          
      wdt_disable(); 

      if (wdt_delay_counter >= wdt_long_delay)
      {   
      wdt_delay_counter = 0; 
	 
	 ZigduinoRadio.setState(STATE_RX);
	 delay(1000);
	 for (int j=0; j < RX_CYCLES; j++)
	 {
	    delay(RX_CYCLE_TIME);
	    show_screen(lcr_by_row[j%24], 10);
	    if (ZigduinoRadio.available())
	    {
	       ZigduinoRadio.forceState(STATE_SLEEP);
	       rcv = ZigduinoRadio.read();
	       switch(rcv){ // First Byte is our control code
		  case CTL_CHECKIN:
		     processCheckin((uint8_t)ZigduinoRadio.read());
		     ZigduinoRadio.flush();
		     break;
		  case CTL_MESSAGE:
		     for (i=0; i<ZR_FIFO_SIZE && ZigduinoRadio.available(); i++)
		     {
			msg[i] = (char)ZigduinoRadio.read();
		     }
		     msg[i] = '\0';
		     scrollMessage("*** ");
		     scrollMessage(msg);
		     scrollMessage(" ***");
		     ZigduinoRadio.flush();
		     break;
		  case CTL_REPORT:
		     delay(50+(int)EEPROM.read(0x1));
		     ZigduinoRadio.setState(STATE_TX);
		     ZigduinoRadio.setChannel(15);
		     ZigduinoRadio.beginTransmission();
		     for (i = 0; i < 0x1A; i++)
			ZigduinoRadio.write(EEPROM.read(i));
		     ZigduinoRadio.endTransmission();
		     ZigduinoRadio.setChannel(20);
		     ZigduinoRadio.setState(STATE_SLEEP);
		     scrollMessage(report);

		     break;
		  case CTL_SQUELCH:
		     scrollMessage("** Squelch ***");
		     EEPROM.write(0x4,(byte)ZigduinoRadio.read());
		     ZigduinoRadio.flush();
		     break;
		  default:
		     scrollMessage(error);
		     show_screen(font5x8['0'+rcv-0x20], 200);
		     ZigduinoRadio.flush();
		     break;
	       }
	       break;
	    }
	 }
      }
      // ZigduinoRadio.setState(STATE_RX);

      wdt_setup();     
               
   }                                       
   else				    	
   {    					
   }                               	

};				    	
   







uint16_t readVcc() {
  uint16_t result;
  ADMUX = _BV(REFS0)|  _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  ADCSRB = _BV(MUX5);
  delay(3);
  ADCSRA |= _BV(ADSC);
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  //result = 1126400L / result;
  return result;
}





// Radio Code

uint8_t* processFrame(uint8_t len, uint8_t* frm, uint8_t lqi, uint8_t crc_fail)
{
  int i = 0;
  char frameId[4];
  //pull the frameId
  scrollMessage("Haz Frm");
  for (i = 0; i < (int) len; i++)
  {
    /*Serial.print("[");
    Serial.print(frm[i],HEX);
    Serial.print("]");*/
    if (i >= 3 && i < 7) frameId[i-3] = (char)frm[i];
  }
  frameId[4] = '\0';

  //Short out if this isn't our packet
  if (strcmp(frameId,"THXT"))
         return ZigduinoRadio.rxRingBuffer;

  //Fill the Ring buffer sans header
  for (int i = 0; i < (int) len; i++)
   {
       uint16_t j = ((uint16_t)((uint16_t)ZigduinoRadio.rxRingBufferHead + 1)) % ZR_FIFO_SIZE;
       if (j != ZigduinoRadio.rxRingBufferTail)
       {
                                        // push into FIFO
          ZigduinoRadio.rxRingBuffer[ZigduinoRadio.rxRingBufferHead] = frm[i];
          ZigduinoRadio.rxRingBufferHead = j;
       }
      else
      {
                                        // FIFO full
           break;
      }
   }
  //Serial.println();
  return ZigduinoRadio.rxRingBuffer;
}



void errHandle(radio_error_t err)
{
   //Radio error blinks corner LED, incriments EEPROM error count byte

   cli();
/*
   PORTF = 0xFF;
   SET_LOW(PORTE,4);
   SET_HIGH(PORTF,7);
   delayMicroseconds(1);
   PORTF = 0xFF;
*/
/*
   scrollMessage(" radio error ");
   byte i = EEPROM.read(0x08);
   EEPROM.write(0x08,++i);
*/
   sei();
}



void processCheckin(uint8_t n)
{
     uint8_t c = 0;
//     ZigduinoRadio.forceState(STATE_SLEEP);
     byte i = EEPROM.read(0x10+n); // grab current count

     EEPROM.write(0x10 + n, ++i);  //incriment count
     for (uint8_t j = 0; j < 10; j++)  //tally all checkins
     {
         if (EEPROM.read(0x10+j) > 00)
              c++;
         if ( c > 10 ) c = 10;  //edge-case, shouldn't occur but did
     }

    scrollMessage(checkin);  //written message
    if (c == 10) 
    { 
      scrollMessage(complete);
      return;
    }
    if (i-1){ // i will be 1 or more
       show_screen(areas[c-1],100);
       blank_led_array();delay(50);
       show_screen(areas[c-1],300);
    } 
    else
    {
      displayAnim(c-1);  //tetris drop
    }
}

void getIDString(char * idstr)
{
   byte byteone = EEPROM.read(0x0);
   byte bytetwo = EEPROM.read(0x1);

   String prefix = String("0x");

   String first_byte = String("");
   String second_byte = String("");
   String first_byte_num = String(byteone, HEX);
   String second_byte_num = String(bytetwo, HEX);

   if (byteone < 16)
   {
      first_byte += "0";
   }

   if (bytetwo < 16)
   {
      second_byte += "0";
   }

   first_byte += first_byte_num;
   second_byte += second_byte_num;
   

   String output = String(" " + prefix + first_byte + second_byte + " ");
   
   if (output.length() != 8)
      scrollMessage("getID len bad!");

   output.toCharArray(idstr, output.length() + 1);
}



	



