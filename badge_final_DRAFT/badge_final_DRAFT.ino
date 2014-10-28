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
#include <fontScroll.h>
#include <TcbTile.h>


//Function Macros
#define SET_LOW(x,y) (x &= (~(1<<y)))
#define SET_HIGH(x,y) (x |= (1<<y))

//Variables


#define AREA_1  0x1
#define AREA_2  0x2
#define AREA_3  0x3
#define AREA_4  0x4
#define AREA_5  0x5
#define AREA_6  0x6
#define AREA_7  0x7
#define AREA_8  0x8
#define AREA_9  0x9
#define AREA_A  0xA

#define CTL_CHECKIN 0x1
#define CTL_MESSAGE 0x2
#define CTL_REPORT  0x3
#define CTL_SQUELCH 0x4

//Radio
uint16_t grab_address();
void errHandle(radio_error_t);
uint8_t* processFrame(uint8_t, uint8_t*, uint8_t, uint8_t);
void processPacket();

// Graphix/
void boot_graphic();

void show_column(byte,int);
void blank_led_array();
void show_screen(byte*,int);
void display_anim(uint16_t);
void scrollMessage(const char*);

//Memory
void process_checkin(uint16_t);

//Pwr-mgmt
uint16_t readVcc();

//Literal Messages
const char* welcome = "*** Greetings THOTCON 0x4 Badge Node ***";
const char* checkin = "*** Proximity Verification Complete: ***";
const char* complete = "*** Congratulations! Tetris Complete!!! ***";
const char* report = "*** Host Communication Established ***";
const char* error = "*** Please Don't Hack Me ***";
const char* messages[] = {"Good Morning!","I need a Beer","BURP BURP BURP","Lunch Time!!! Nom Nom Nom","Fork My Dongle","Please Don\'t Hack Me","STFU","Applause","Dinner Time!!! Nom Nom Nom","See you at THOTCON 0x5","GTFO","c7five was here."};






//Runs on reset
void setup()
{
   // Activate LED Ports for Output
   DDRE |= (  (1<<PE0) | (1<<PE1) | (1<<PE2) | (1<<PE3) | (1<<PE4) );
   DDRF = 0xFF;
   // Set drive currect for LED Ports
   DPDS0 |= _BV(PFDRV1) | _BV(PFDRV0) | _BV(PEDRV1) | _BV(PEDRV0);

   /*Timer Setups
   TCCR1B |= 1<<WGM12 | 1<<CS10;
   TIMSK1 |= 1 << OCIE1A;
   OCR1A = 0x0BB0;
   sei();
   */


   //fancy TC animation
   boot_graphic();
   blank_led_array();
   scrollMessage(welcome);
 //  radio_set_param(RP_CCAMODE(3));
   uint8_t frameHeader[] = {0x01,0x80,0x00,'T','H','O','T'};
   ZigduinoRadio.attachError(errHandle);
  // ZigduinoRadio.attachReceiveFrame(processFrame);
   ZigduinoRadio.begin(20,frameHeader);
 //  ZigduinoRadio.forceState(STATE_SLEEP);
  /* Serial.begin(9600);
  Serial.println("init complete");
  */

};

void loop()
{
   //Hope to be able to replace this with a watchdog timer or something from the Low Power Lib
   char msg[ZR_FIFO_SIZE+1];
   int i = 0;
   if (ZigduinoRadio.available())
   {
      ZigduinoRadio.forceState(STATE_SLEEP);
      switch(ZigduinoRadio.read()){ // First Byte is our control code
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
          delay(50);
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
           ZigduinoRadio.flush();
           break;
      }
  }
  ZigduinoRadio.setState(STATE_RX);
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
   PORTF = 0xFF;
   SET_LOW(PORTE,4);
   SET_HIGH(PORTF,7);
   delayMicroseconds(1);
   PORTF = 0xFF;
   byte i = EEPROM.read(0x08);
   EEPROM.write(0x08,++i);
   sei();
}



void processCheckin(uint8_t n)
{
     uint8_t c = 0;
     ZigduinoRadio.forceState(STATE_SLEEP);
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




void boot_graphic()
{
  int i = 0;


  byte b1[] =       {  0b01110110,
                     0b01110110,
                     0b00000110,
                     0b01110110,
                     0b01110000  };

  byte b2[] =       {  0b10101101,
                     0b10101101,
                     0b10000101,
                     0b10101101,
                     0b10100001  };

  byte b3[] =       {  0b11011011,
                     0b11011011,
                     0b11000011,
                     0b11011011,
                     0b11000011  };

  byte b4[] =       {  0b11011011,
                     0b11000011,
                     0b11011011,
                     0b11011011,
                     0b11000011  };

  byte b5[] =       {  0b11000011,
                     0b11011011,
                     0b11011011,
                     0b11011011,
                     0b11000011  };

  byte b6[] =       {  0b10000011,
                     0b10111011,
                     0b10111011,
                     0b10111011,
                     0b10000011  };

  byte b7[] =       {  0b10000011,
                     0b11010111,
                     0b10111011,
                     0b11010111,
                     0b10000011  };

  byte b8[] =       {  0b10010011,
                     0b11000111,
                     0b11010111,
                     0b11000111,
                     0b10010011  };

  byte b9[] =       {  0b10111011,
                     0b11010111,
                     0b11101111,
                     0b11010111,
                     0b10111011  };

  byte b10[] =      {  0b11111111,
                     0b10010011,
                     0b11101111,
                     0b11110111,
                     0b10010111  };


  byte b11[] =      {  0b11111111,
                     0b10000011,
                     0b11101111,
                     0b11101111,
                     0b10001111  };

  byte b12[] =      {  0b11101111,
                     0b10000011,
                     0b11101111,
                     0b11101111,
                     0b10001111  };

  byte* boot_anim[] = {b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12};
  int timing[]= {300,100,100,100,100,300,100,100,300,100,100,300};



  for ( i = 0; i < 12; i++)
     show_screen(boot_anim[i],timing[i]);
  i--;
  for ( i; i >= 0; i--)
     show_screen(boot_anim[i],timing[i]);

}



