/*

Run this sketch on two Zigduinos, open the serial monitor at 9600 baud, and type in stuff
Watch the Rx Zigduino output what you've input into the serial port of the Tx Zigduino

*/

#include <ZigduinoRadio.h>

int row_pin[] = {14, 15, 16, 17, 18, 19, 33, 35}; // port b 0, 4 , 5 , 6, 7 

int column_pin[] = {36, 37, 4, 5, 6};

byte triangle[] = {  0b00000000, 
                     0b01101110, 
                     0b01101110, 
                     0b01101110, 
                     0b10010001  };
                     
 byte line[] =     { 0b11111101, 
                     0b11111101, 
                     0b11111101, 
                     0b11111101, 
                     0b11111101  };
                     
 byte jag[] =      { 0b11000000, 
                     0b00000011, 
                     0b11000000, 
                     0b00000011, 
                     0b11000000  };

 byte t1[] =       { 0b11111111, 
                     0b11111111, 
                     0b01111111, 
                     0b11111111, 
                     0b11111111  };
                     
  byte t2[] =      { 0b11111111, 
                     0b11111111, 
                     0b00111111, 
                     0b01111111, 
                     0b11111111  };
                     
   byte t3[] =     { 0b11111111, 
                     0b11111111, 
                     0b00011111, 
                     0b10111111, 
                     0b11111111  };
                     
   byte t4[] =     { 0b11111111, 
                     0b11111111, 
                     0b10001111, 
                     0b11011111, 
                     0b11111111  };     
                     
    byte t5[] =    { 0b11111111, 
                     0b11011111, 
                     0b10011111, 
                     0b11011111, 
                     0b11111111  };               

     byte t6[] =   { 0b11111111, 
                     0b11101111, 
                     0b11001111, 
                     0b11101111, 
                     0b11111111  };               

     byte t7[] =   { 0b11111111, 
                     0b11110111, 
                     0b11100111, 
                     0b11110111, 
                     0b11111111  };     
                     
      byte t8[] =  { 0b11111111, 
                     0b11111011, 
                     0b11110011, 
                     0b11111011, 
                     0b11111111  };   
                     
      byte t9[] =  { 0b11111111, 
                     0b11111101, 
                     0b11111001, 
                     0b11111101, 
                     0b11111111  };     
                     
      byte t10[] =  { 0b11111111, 
                     0b11111110, 
                     0b11111100, 
                     0b11111110, 
                     0b11111111  };     
                     
 void blank_column(int n)
{
/*
  for (int i=0; i<8; i++)
  {
    digitalWrite(portepin[i], HIGH);
  }
*/

    digitalWrite(column_pin[n], LOW);
  
}

 void blank_led_array()
{
  for (int i=0; i<5; i++)
  {
    blank_column(i);
  }
}

void show_column(byte whole_col, int n)
{
  for (byte i=0; i<8; i++)
  {
    digitalWrite(row_pin[i], bitRead(whole_col, 7-i));
    //digitalWrite(portepin[i], LOW);
  }
  
  digitalWrite(column_pin[n], HIGH);
}

void light_whole_array(int n)
{
 show_column(0, n);
}

void show_screen(byte shape[], int iterations)
{
  while (--iterations)
  {
    for (byte i=0; i<5; i++)
    {
      blank_led_array();
      show_column(shape[i], i);
    }
  }
}

void ripple_array()
{
  for (byte i=0; i<5; i++)
  {
    show_column(0, i);
    delay(10);
    blank_column(i);
  }
}

void setup()
{
  ZigduinoRadio.begin(11); // use channel 11;
  
  
  ZigduinoRadio.attachError(errHandle);
  ZigduinoRadio.attachTxDone(onXmitDone);

   DDRE |= (  (1<<PE0) | (1<<PE1) | (1<<PE2) | (1<<PE3) | (1<<PE4) );

   DDRF = 0xFF;

   blank_led_array();

   ripple_array();
}

void loop()
{
  
  // tx block
    //a few sequence with delays so we can do some basic read/write verification
     for (int i=1; i<16; i++)
     {

      ZigduinoRadio.write(i); delay(500);

     }



  delay(1000); //we'll need some wtf?!?! time
}

void errHandle(radio_error_t err) //light an indicator on error
{
  digitalWrite(11,HIGH);
  delay(1000);
  digitalWrite(11,LOW);
  
}
void onXmitDone(radio_tx_done_t x) //each transmition blinks this LED
{

  show_column(0,0);
  delay(100);
  blank_column(0);
}

