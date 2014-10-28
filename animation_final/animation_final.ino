#include <ZigduinoRadio.h>

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

void setup()
{
   DDRE |= (  (1<<PE0) | (1<<PE1) | (1<<PE2) | (1<<PE3) | (1<<PE4) );

   DDRF = 0xFF;
};

byte **anims[] = {anim1,anim2,anim3,anim4,anim5,anim6,anim7,anim8,anim9};
uint16_t anim_lens[9] = {9,10,10,8,5,5,6,5,3};

void displayAnim(int n)
{
      int i = 0;
      for (i = 0; i < anim_lens[n]; i++)
          show_screen(anims[n][i],100);
}

void loop()
{
uint16_t i = 0;

for( i =0; i < 9; i++)
   displayAnim(i);
 

};

/*
void loop()
{

  show_screen(w88, 1000);
  show_screen(t1, 100);
  show_screen(t2, 100);
  show_screen(t3, 100);
  show_screen(t4, 100);
  show_screen(t5, 100);
  show_screen(t6, 100);
  show_screen(t7, 100);
//  show_screen((t7>>1)&0xFF, 100);
  show_screen(t8, 100);
  show_screen(a1, 100);
  show_screen(a1, 100);
  show_screen(a1, 100);
  show_screen(a1, 100);
  show_screen(t9, 100);
  show_screen(t10, 100);
  show_screen(t11, 100);
  show_screen(t12, 100);
  show_screen(t13, 100);
  show_screen(t14, 100);
  show_screen(t15, 100);
  show_screen(t16, 100);
  show_screen(t17, 100);
  show_screen(a2, 100);
  show_screen(a2, 100);
  show_screen(a2, 100);
  show_screen(a2, 100);
  show_screen(t18, 100);
  show_screen(t19, 100);
  show_screen(t20, 100);
  show_screen(t21, 100);
  show_screen(t22, 100);
  show_screen(t23, 100);
  show_screen(t24, 100);
  show_screen(t25, 100);
  show_screen(t26, 100);
  show_screen(a3, 100);
  show_screen(a3, 100);
  show_screen(a3, 100);
  show_screen(a3, 100);
  show_screen(t27, 100);
  show_screen(t28, 100);
  show_screen(t29, 100);
  show_screen(t30, 100);
  show_screen(t31, 100);
  show_screen(t32, 100);
  show_screen(t33, 100);
  show_screen(a4, 100);
  show_screen(a4, 100);
  show_screen(a4, 100);
  show_screen(a4, 100);
  show_screen(t34, 100);
  show_screen(t35, 100);
  show_screen(t36, 100);
  show_screen(t37, 100);
  show_screen(a5, 100);
  show_screen(a5, 100);
  show_screen(a5, 100);
  show_screen(a5, 100);
  show_screen(t38, 100);
  show_screen(t39, 100);  
  show_screen(t40, 100);
  show_screen(t41, 100);
  show_screen(a6, 100);
  show_screen(a6, 100);
  show_screen(a6, 100);
  show_screen(a6, 100);
  show_screen(t42, 100);
  show_screen(t43, 100);  
  show_screen(t44, 100);
  show_screen(t45, 100);
  show_screen(t46, 100);
  show_screen(a7, 100);
  show_screen(a7, 100);
  show_screen(a7, 100);
  show_screen(a7, 100);
  show_screen(t47, 100);
  show_screen(t48, 100);
  show_screen(t49, 100);  
  show_screen(t50, 100);
  show_screen(a8, 100);
  show_screen(a8, 100);
  show_screen(a8, 100);
  show_screen(a8, 100);
  show_screen(t51, 100);
  show_screen(t52, 100);
  show_screen(a9, 100);
  show_screen(a9, 100);
  show_screen(a9, 100);
  show_screen(a9, 100);
  show_screen(aa, 100);
 show_screen(aa, 100); 
 show_screen(aa, 100);
  show_screen(aa, 100);
   show_screen(aa, 100);
};*/
