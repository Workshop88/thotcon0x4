/*

Run this sketch on two Zigduinos, open the serial monitor at 9600 baud, and type in stuff
Watch the Rx Zigduino output what you've input into the serial port of the Tx Zigduino

*/

#include <ZigduinoRadio.h>

int row_pin[] = {14, 15, 16, 17, 18, 19, 33, 35}; // port b 0, 4 , 5 , 6, 7 

int column_pin[] = {36, 37, 4, 5, 6};

int screen_off_time = 5000;


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
                     
 byte jag38[] =    { 0b11111000, 
                     0b11100011, 
                     0b00011111, 
                     0b11000111, 
                     0b11111000  };                     

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
  byte row_state = HIGH;
  
  for (byte i=0; i<8; i++)
  {
    row_state = bitRead(whole_col, 7-i);
    if (row_state == LOW)
    {
      digitalWrite(row_pin[i], LOW);
      digitalWrite(column_pin[n], HIGH);
      digitalWrite(row_pin[i], HIGH);
    }
    digitalWrite(column_pin[n], LOW);
  }
  
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
      //blank_led_array();
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

void brief_listen(int n)
{
    int something_in_rx_buffer;
    ZigduinoRadio.setState(STATE_RX); 
    delay(n);
    something_in_rx_buffer = ZigduinoRadio.available();
    ZigduinoRadio.setState(STATE_SLEEP); 
}

void setup()
{
  ZigduinoRadio.begin(11); // use channel 11;

  
  ZigduinoRadio.attachError(errHandle);
    ZigduinoRadio.setState(STATE_SLEEP); 

   DDRE |= (  (1<<PE0) | (1<<PE1) | (1<<PE2) | (1<<PE3) | (1<<PE4) );

   DDRF = 0xFF;

   blank_led_array();

   ripple_array();
   screen_off_time = 350;
}

void loop()
{
  show_screen(triangle, 100);
  brief_listen(50);
  show_screen(jag, 100);
  brief_listen(50);
  show_screen(jag38, 100);
  brief_listen(50);
  ripple_array();
  delay(screen_off_time);  
}

void errHandle(radio_error_t err) //light an indicator on error
{
  digitalWrite(11,HIGH);
  delay(1000);
  digitalWrite(11,LOW);
  
}


