/*

Run this sketch on two Zigduinos, open the serial monitor at 9600 baud, and type in stuff
Watch the Rx Zigduino output what you've input into the serial port of the Tx Zigduino

*/

void initT(void)
{

  TCCR1B |= 1<<WGM12 | 1<<CS10;	// timer initialization	


  TIMSK1 |= 1<<OCIE1A;			


  OCR1A = 0x002C;	// 70 Hz		


  sei();



}




ISR(TIMER1_COMPA_vect) // This is the interrupt handler just squentially turn portE high.
{
   PORTB |= (  (1<<PB0) | (1<<PB4) | (1<<PB5) | (1<<PB6) | (1<PB7) );
 
   for (int i=0; i<7; i++)
   {
       PORTE |= 0xFF;

       PORTE |= (0<<(6-i));
       delay(100);
       
    }

  PORTE |= 0xFF;
}



 // int portdpin[] = {21, 22, 0, 1, 28};
 //int portbpin[] = {26, 8, 11, 10, 9}; // port b 0, 4 , 5 , 6, 7 
    int portepin[] = {14, 15, 16, 17, 18, 19, 33, 35}; // port b 0, 4 , 5 , 6, 7 

  int portbpin[] = {36, 37, 4, 5, 6};
 
 byte led_row;
 
 byte triangle[] = { 0b00000000, 
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
 
 void blacol(int n)
{
/*
  for (int i=0; i<8; i++)
  {
    digitalWrite(portepin[i], HIGH);
  }
*/

    digitalWrite(portbpin[n], LOW);
  
}

 void bla()
{
  for (int i=0; i<5; i++)
  {
    blacol(i);
  }
}

void showcol(byte whole_col, int n)
{
  for (byte i=0; i<8; i++)
  {
    digitalWrite(portepin[i], bitRead(whole_col, 7-i));
    //digitalWrite(portepin[i], LOW);
  }
  
  digitalWrite(portbpin[n], HIGH);
}

void allcol(int n)
{
 showcol(0, n);
}


void setup()
{
   //DDRB = 0xF8;
   DDRE |= (  (1<<PE0) | (1<<PE1) | (1<<PE2) | (1<<PE3) | (1<<PE4) );

   DDRF = 0xFF;
   //DDRG |= ((1<<PB5)  );

   //initT();
   bla();
}

void loop()
{

      // bla();


  for (int i=0; i<5; i++)
  {
    bla();
    //allcol(i);
    //showcol(jag[i], i);
    showcol(triangle[i], i);
  }
  bla();
  
/*
  // 3x1
  PORTE |= ( (1<<PE0) | (0<<PE1) | (0<<PE2) | (0<<PE3) | (1<<PE4) |  (1<<PE5) |  (1<<PE6) |  (1<<PE7));
  PORTB |= ( (0<<PB0) | (1<<PB4) | (0<<PB5) | (0<<PB6) | (0<<PB7) );
 */
 /*
  digitalWrite(portepin[0], LOW);
  digitalWrite(portepin[1], LOW);
  digitalWrite(portepin[2], LOW);
  digitalWrite(portepin[3], LOW);
  digitalWrite(portepin[4], LOW);
  digitalWrite(portepin[5], LOW);
  digitalWrite(portepin[6], LOW);
  
  digitalWrite(portbpin[0], HIGH);

  bla();
 */

  /*
  // 1x1
  PORTE |= ( (1<<PE0) | (1<<PE1) | (0<<PE2) | (1<<PE3) | (1<<PE4) |  (1<<PE5) |  (1<<PE6) |  (1<<PE7));
  PORTB |= ( (0<<PB0) | (0<<PB4) | (1<<PB5) | (0<<PB6) | (0<<PB7) );
  delay(1000);
*/
  /*
  digitalWrite(portepin[3], LOW);
  digitalWrite(portepin[4], LOW);
  digitalWrite(portepin[5], LOW);
  digitalWrite(portepin[6], LOW);
  
  digitalWrite(portbpin[1], HIGH);

   bla();

  digitalWrite(portepin[4], LOW);
  digitalWrite(portepin[5], LOW);
  digitalWrite(portepin[6], LOW);
  
  digitalWrite(portbpin[2], HIGH);

   bla();

  digitalWrite(portepin[5], LOW);
  digitalWrite(portepin[6], LOW);
  
  digitalWrite(portbpin[3], HIGH);
  
  bla();
  
  digitalWrite(portepin[6], LOW);
  
  digitalWrite(portbpin[4], HIGH);
  
  bla();
  */
// off


// set all on (ground all D, power all E)
/*
for (int i=0; i<8; i++)
{
  digitalWrite(portepin[i], LOW);
}
*/
//cli();
//sei();
//delay(1000);
/*
PORTE |= ( (1<<PE0) | (1<<PE1) |  (1<<PE2) |  (1<<PE3) |  (1<<PE4) |  (1<<PE5) |  (1<<PE6) |  (1<<PE7));


PORTD |= (  (0<<PD0) | (0<<PD1) | (0<<PD2) | (0U<<PD3) | (0<<PD4) );
*/
/*for (int i=0; i<8; i++)
{
  digitalWrite(portepin[i], HIGH);
}

for (int i=0; i<5; i++)
{
  digitalWrite(portfpin[i], LOW);
}
*/
}


