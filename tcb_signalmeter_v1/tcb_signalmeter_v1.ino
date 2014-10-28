/*

Run this sketch on two Zigduinos, open the serial monitor at 9600 baud, and type in stuff
Watch the Rx Zigduino output what you've input into the serial port of the Tx Zigduino

*/

#include <ZigduinoRadio.h>

int row_pin[] = {14, 15, 16, 17, 18, 19, 33, 35}; // port b 0, 4 , 5 , 6, 7 

int column_pin[] = {36, 37, 4, 5, 6};

byte data = 0xFF;
byte lqi_reading = 0;
int rssi_reading = -91;
int ed_reading = -90;

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
                     
      byte tocol[] = { 0b11111111, 
                     0b11111110, 
                     0b11111100, 
                     0b11111000,                     
                     0b11110000, 
                     0b11100000, 
                     0b11000000, 
                     0b10000000, 
                     0b00000000  };                          
                     
 void blank_column(int n)
{

  for (int i=0; i<8; i++)
  {
    digitalWrite(row_pin[i], HIGH);
  }


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

// translate 0-
byte twofiftysix2column(byte val)
{
  byte out = 0xFF;
  byte pos = 7;
  for (byte i=1; i<(val+1); i++)
  {
    if (i % 16)
    {
      out |= 0<<pos;
      --pos;
    }
  }
  return out;
}

void setup()
{
  ZigduinoRadio.begin(11); // use channel 11;
  
  
  ZigduinoRadio.attachError(errHandle);

   DDRE |= (  (1<<PE0) | (1<<PE1) | (1<<PE2) | (1<<PE3) | (1<<PE4) );

   DDRF = 0xFF;

   blank_led_array();
/*
  for (byte i=0; i<256; i++)
  {
    //blank_column(0);
    //blank_column(4);
    show_column(tocol[map(i,0,256,0,8)], 0);
    
        blank_column(0);

    show_column(0b00011111,4);
        blank_column(4);

  }
  */
  ripple_array();
  
}

void loop()
{
  
      while(ZigduinoRadio.available()) { 
        blank_led_array();
      show_column(tocol[map(ZigduinoRadio.getLqi(),0,256,0,8)], 0);
blank_column(0);
      show_column(tocol[map(ZigduinoRadio.getEdNow(), -90, -6, 0, 8)], 1);
blank_column(1);

      show_column(tocol[map(ZigduinoRadio.getRssiNow(), -91, -9, 0, 8)], 2);
blank_column(2);

      show_column(tocol[ZigduinoRadio.read()% 8], 4);
blank_column(3);

      }

  
}

void errHandle(radio_error_t err) //light an indicator on error
{
  digitalWrite(11,HIGH);
  delay(1000);
  digitalWrite(11,LOW);
  
}

