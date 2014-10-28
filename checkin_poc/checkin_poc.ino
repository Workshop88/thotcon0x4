#include <ZigduinoRadio.h>
#include <EEPROM.h>

#define CTL_CHECKIN 0x1
#define CTL_MESSAGE 0x2
#define CTL_REPORT  0x3
#define CTL_SQUELCH 0x4

int row_pin[] = {14, 15, 16, 17, 18, 19, 33, 35}; // port b 0, 4 , 5 , 6, 7 

int column_pin[] = {36, 37, 4, 5, 6};

/* Area bytes arrays -- These are the final positions of pieces on the board */
byte a1[] =       {  0b11111111, 
                     0b11111111, 
                     0b11111111, 
                     0b11111110, 
                     0b11111000  };

byte a2[] =      {   0b11111111, 
                     0b11111110, 
                     0b11111100, 
                     0b11111100, 
                     0b11111000  };
                     
byte a3[] =      {   0b11110000, 
                     0b11111110, 
                     0b11111100, 
                     0b11111100, 
                     0b11111000   };
                     
byte a4[] =      {   0b11110000, 
                     0b11111000, 
                     0b11111000, 
                     0b11111000, 
                     0b11111000   };
                     
byte a5[] =      {   0b11110000, 
                     0b11110000, 
                     0b11100000, 
                     0b11110000, 
                     0b11111000   };
                     
byte a6[]  =     {   0b11000000, 
                     0b11000000, 
                     0b11100000, 
                     0b11110000, 
                     0b11111000   };
                     
byte a7[]  =      {  0b11000000, 
                     0b11000000, 
                     0b11100000, 
                     0b11000000, 
                     0b11100000   };
                     
byte a8[] =       {  0b11000000, 
                     0b11000000, 
                     0b11100000, 
                     0b10000000, 
                     0b00000000   };
                     
byte a9[] =       {  0b10000000, 
                     0b10000000, 
                     0b10000000, 
                     0b10000000, 
                     0b00000000   };
                     
byte aa[] = {0x0,0x0,0x0,0x0,0x0};
                     
byte *areas[] = {a1,a2,a3,a4,a5,a6,a7,a8,a9};
                     
                     
 /* Animation tiles and arrays */
 /* < A1: > */
byte t1[] =   { 0b11111111, 
                0b01111111, 
                0b01111111, 
                0b11111111, 
                0b11111111  };
                     
byte t2[] =   { 0b11111111, 
                0b10111111, 
                0b00111111, 
                0b11111111, 
                0b11111111  };
                     
byte t3[] =   { 0b11111111, 
                0b11011111, 
                0b00011111, 
                0b11111111, 
                0b11111111  };
                     
byte t4[] =   { 0b11111111, 
                0b11101111, 
                0b10001111, 
                0b11111111, 
                0b11111111  };     
                     
byte t5[] =   { 0b11111111, 
                0b11110111, 
                0b11000111, 
                0b11111111, 
                0b11111111  };               

byte t6[] =   { 0b11111111, 
                0b11111111, 
                0b11110111, 
                0b11000111, 
                0b11111111  };               

byte t7[] =   { 0b11111111, 
                0b11111111, 
                0b11111111, 
                0b11111011, 
                0b11100011  };     
                     
byte t8[] =  { 0b11111111, 
               0b11111111, 
               0b11111111, 
               0b11111101, 
               0b11110001  };   

byte *anim1[] = {t1,t2,t3,t4,t5,t6,t7,t8,a1};
                     
byte t9[] =  { 0b11111111, 
               0b11111111, 
               0b11111111, 
               0b11111110, 
               0b11111000  };     
                     
byte t10[] =  { 0b11111111, 
                0b11111111, 
                0b01111111, 
                0b11111110, 
                0b11111000  };     

byte t11[] =  { 0b11111111, 
                0b01111111, 
                0b00111111, 
                0b11111110, 
                0b11111000  };      

byte t12[] =  { 0b11111111, 
                0b00111111, 
                0b10011111, 
                0b11111110, 
                0b11111000  }; 

byte t13[] =  { 0b11111111, 
                0b10011111, 
                0b11001111, 
                0b11111110, 
                0b11111000  };   

byte t14[] =  { 0b11111111, 
                0b11001111, 
                0b11100111, 
                0b11111110, 
                0b11111000  };  

byte t15[] =  { 0b11111111, 
                0b11110111, 
                0b11100111, 
                0b11101110, 
                0b11111000  };
  
byte t16[] =  { 0b11111111, 
                0b11111011, 
                0b11110011, 
                0b11110110, 
                0b11111000  };

byte t17[] =  { 0b11111111, 
                0b11111101, 
                0b11111001, 
                0b11111010, 
                0b11111000  };

byte *anim2[] = {t9,t10,t11,t12,t13,t14,t15,t16,t17,a2};

byte t18[] =     {   0b11111111, 
                     0b11111110, 
                     0b01111100, 
                     0b11111100, 
                     0b11111000  };
                     
byte t19[] =     {   0b11111111, 
                     0b11111110, 
                     0b00111100, 
                     0b11111100, 
                     0b11111000  };
                     
byte t20[] =     {   0b11111111, 
                     0b11111110, 
                     0b00011100, 
                     0b11111100, 
                     0b11111000  };
                     
byte t21[] =     {   0b11111111, 
                     0b00011110, 
                     0b11111100, 
                     0b11111100, 
                     0b11111000  };
                     
byte t22[] =     {   0b11111111, 
                     0b00001110, 
                     0b11111100, 
                     0b11111100, 
                     0b11111000  };
                     
byte t23[] =     {   0b11111111, 
                     0b10000110, 
                     0b11111100, 
                     0b11111100, 
                     0b11111000  };
                     
byte t24[] =     {   0b11111111, 
                     0b11000010, 
                     0b11111100, 
                     0b11111100, 
                     0b11111000  };
                     
byte t25[] =     {   0b11000011, 
                     0b11111110, 
                     0b11111100, 
                     0b11111100, 
                     0b11111000  };  

byte t26[] =     {   0b11100001, 
                     0b11111110, 
                     0b11111100, 
                     0b11111100, 
                     0b11111000  };      
                     
byte *anim3[] = {t18,t19,t20,t21,t22,t23,t24,t25,t26,a3}; 

byte t27[] =     {   0b11110000, 
                     0b01111110, 
                     0b01111100, 
                     0b11111100, 
                     0b11111000   };
                     
byte t28[] =     {   0b11110000, 
                     0b00111110, 
                     0b10111100, 
                     0b11111100, 
                     0b11111000   };
                     
byte t29[] =     {   0b11110000, 
                     0b00011110, 
                     0b11011100, 
                     0b11111100, 
                     0b11111000   };

byte t30[] =     {   0b11110000, 
                     0b10011110, 
                     0b10111100, 
                     0b10111100, 
                     0b11111000   };

byte t31[] =     {   0b11110000, 
                     0b11001110, 
                     0b11011100, 
                     0b11011100, 
                     0b11111000   };

byte t32[] =     {   0b11110000, 
                     0b11100110, 
                     0b11101100, 
                     0b11101100, 
                     0b11111000   };
 
byte t33[] =     {   0b11110000, 
                     0b11110010, 
                     0b11110100, 
                     0b11110100, 
                     0b11111000   };
                     
byte *anim4[] = {t27,t28,t29,t30,t31,t32,t33,a4};

byte t34[] =     {   0b11110000, 
                     0b01111000, 
                     0b01111000, 
                     0b01111000, 
                     0b11111000   };
                     
byte t35[] =     {   0b11110000, 
                     0b10111000, 
                     0b00111000, 
                     0b10111000, 
                     0b11111000   };
                     
byte t36[] =     {   0b11110000, 
                     0b11011000, 
                     0b10011000, 
                     0b11011000, 
                     0b11111000   };
                     
byte t37[] =     {   0b11110000, 
                     0b11101000, 
                     0b11001000, 
                     0b11101000, 
                     0b11111000   };
                     
byte *anim5[] = {t34,t35,t36,t37,a5};

byte t38[] =     {   0b11110000, 
                     0b01110000, 
                     0b01100000, 
                     0b11110000, 
                     0b11111000   };
                     
byte t39[] =     {   0b11110000, 
                     0b00110000, 
                     0b00100000, 
                     0b11110000, 
                     0b11111000   };                     

byte t40[] =     {   0b11110000, 
                     0b10010000, 
                     0b10000000, 
                     0b11110000, 
                     0b11111000   };

byte t41[] =     {   0b10010000, 
                     0b10010000, 
                     0b11100000, 
                     0b11110000, 
                     0b11111000   };

byte *anim6[] = {t38,t39,t40,t41,a6};

byte t42[]  =    {   0b11000000, 
                     0b01000000, 
                     0b01100000, 
                     0b11110000, 
                     0b11111000   };

byte t43[]  =    {   0b11000000, 
                     0b10000000, 
                     0b00100000, 
                     0b01110000, 
                     0b11111000   };

byte t44[]  =    {   0b11000000, 
                     0b00000000, 
                     0b1000000, 
                     0b11110000, 
                     0b11111000   };
 
byte t45[]  =    {   0b11000000, 
                     0b11000000, 
                     0b00100000, 
                     0b10010000, 
                     0b11111000   };
 
byte t46[]  =    {   0b11000000, 
                     0b11000000, 
                     0b11100000, 
                     0b10010000, 
                     0b11001000   };
                 
byte *anim7[] = {t42,t43,t44,t45,t46,a7};

byte t47[]  =     {  0b11000000, 
                     0b11000000, 
                     0b01100000, 
                     0b11000000, 
                     0b11100000   };
                     
byte t48[]  =     {  0b11000000, 
                     0b01000000, 
                     0b00100000, 
                     0b11000000, 
                     0b11100000   };
                     
byte t49[]  =     {  0b11000000, 
                     0b11000000, 
                     0b01100000, 
                     0b00000000, 
                     0b11100000   };
                     
byte t50[]  =     {  0b11000000, 
                     0b11000000, 
                     0b11100000, 
                     0b01000000, 
                     0b00100000   };
                     
byte *anim8[] = {t47,t48,t49,t50,a8};

byte t51[] =      {  0b11000000, 
                     0b01000000, 
                     0b01100000, 
                     0b10000000, 
                     0b00000000   };
                     
byte t52[] =      {  0b11000000, 
                     0b10000000, 
                     0b00100000, 
                     0b10000000, 
                     0b00000000   };
                     
byte *anim9[] = {t51,t52,a9};

byte w88[] =      {  0b00000000,
                     0b11101010,
                     0b00010000,
                     0b11101010,
                     0b00000000   };

                     
void show_screen(byte shape[], int iterations)
{
  while (--iterations)
  {
    for (int i=0; i<5; i++)
    {
      blank_led_array();
      show_column(shape[4-i], i);
    }
  }
}

void blank_led_array()
{
  for (int i=0; i<5; i++)
  {
     digitalWrite(column_pin[i], LOW);
  }
}

void show_column(byte whole_col, int n)
{
  for (byte i=0; i<8; i++)
  {
    digitalWrite(row_pin[i], bitRead(whole_col, 7-i));
   
  }
  
  digitalWrite(column_pin[n], HIGH);
}

byte **anims[] = {anim1,anim2,anim3,anim4,anim5,anim6,anim7,anim8,anim9};
uint16_t anim_lens[9] = {9,10,10,8,5,5,6,5,3};


void setup()
{
   DDRE |= (  (1<<PE0) | (1<<PE1) | (1<<PE2) | (1<<PE3) | (1<<PE4) );
   DDRF = 0xFF;
   
   delay(300);
 // Serial.begin(9600);
 //  Serial.println("init complete");
   //show_screen(w88,300);
  // blank_led_array();
 //  radio_set_param(RP_CCAMODE(3));
  // ZigduinoRadio.attachReceiveFrame(processFrame);
   ZigduinoRadio.begin(20);
   displayAnim(6);
   blank_led_array();
     
};



void displayAnim(uint16_t n)
{
      uint16_t i = 0;
      if (n > 8) return;
      for (i = 0; i < anim_lens[n]; i++)
          show_screen(anims[n][i],100);
      blank_led_array(); delay(50);
      show_screen(anims[n][i-1],300);
}


uint8_t* processFrame(uint8_t len, uint8_t* frm, uint8_t lqi, uint8_t crc_fail)
{
  //int i,n = 0;
  char* frameId;
  Serial.print ("Recieved frame: "); 
  Serial.println (len); 
  
  
  for (uint8_t x = 0; x < len; x++)
  {
    Serial.print("[");
    Serial.print(frm[x],HEX);
    Serial.print("]");
  }
  /*
   
   for (i = 7; i < ((int) len - 2); i++)
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
   } */               
  Serial.println();
  return ZigduinoRadio.rxRingBuffer;
  
}


void loop()
{
    int len,pos,disp = 0;
    uint16_t area = 0;
  
   
//   Serial.println("Wake");
    ZigduinoRadio.setState(STATE_RX); 
  //  while(!ZigduinoRadio.available());
    //   delay(100);
     delay(6000);
    /*if (len = ZigduinoRadio.available())
    {
       disp = 1;
       while (pos = ZigduinoRadio.available())
            area = (uint16_t) ZigduinoRadio.read();
            
  
   
    }*/
    processPacket();
    if (disp){
      ZigduinoRadio.forceState(STATE_SLEEP);
   //   processCheckin(area);
      disp = 0;
    //  blank_led_array();   
      ZigduinoRadio.setState(STATE_RX);
    }
 //  Serial.println("Sleep");
//   ZigduinoRadio.setState(STATE_SLEEP);
//   delay(6000);
   
}
void processCheckin(uint16_t n)
{
     uint8_t c = 0;
     byte i = EEPROM.read(0x10+n);
   //  if (i == 0x00) 
   //     scrollMessage((char *)checkin);
   // Serial.print("Recieved area: ");
   // Serial.println(n);
   // Serial.print("Total Checkins: ");
   // Serial.println(i);  
     EEPROM.write(0x10 + n, ++i);
     for (uint8_t j = 0; j < 10; j++)
     {
         if (EEPROM.read(0x10+j) > 00) 
              c++;
         if ( c > 9 ) c = 9;
     }
   //  Serial.print("Animation: ");
   //  Serial.println(c);
     displayAnim(c-1);
}

void processPacket()
{
    uint16_t len = 0;
    uint8_t ctl = 0;
    char * msg = 0;
    if (len = ZigduinoRadio.available())
    {
       
       while (ZigduinoRadio.available())
       {
            len = (uint16_t) ZigduinoRadio.read();
            ctl = (uint8_t) ZigduinoRadio.read();
            if (!ctl) break;
            switch (ctl){
              case CTL_CHECKIN:
            //     Serial.print("Type: Checkin, Len: ");
             //    Serial.println(len);
                 processCheckin((uint16_t) ZigduinoRadio.read());
                 ZigduinoRadio.flush();
                 break;
              case CTL_MESSAGE:
            //     Serial.print("Type: Message, Len: ");
            //     Serial.print(len);
                 while (ZigduinoRadio.available())
                     *msg++ = (char) ZigduinoRadio.read();
                 *msg++ = '\0';
                 //Serial.print(msg);
                 scrollMessage(msg);
                 ZigduinoRadio.flush();
                 break;
             case CTL_REPORT:
             // report back code here;
                 break;
             case CTL_SQUELCH: 
                 // ED metric update here;
                 break;
             default: 
              //   Serial.print("Type: Unknown, Len:");
              //   Serial.println(len);
                 ZigduinoRadio.flush();
                 break;
            }
            
       }
  
    }  
  
}
void scrollMessage(char*) { return; }
