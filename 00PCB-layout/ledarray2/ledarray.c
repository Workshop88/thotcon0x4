// ledarray.c
// for NerdKits with ATmega168
// mrobbins@mit.edu

#define F_CPU 14745600

#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <inttypes.h>

#include "../libnerdkits/delay.h"
#include "../libnerdkits/uart.h"

#include "font.h"

// PIN DEFINITIONS:
//
// PB1-5 ROW DRIVERS (0-4)
// PC0-5,PD2-7: COLUMN DRIVERS (0-11)
#define ROWS 5
#define COLS 24

volatile uint8_t la_row, real_row;
volatile uint8_t la_data[COLS];

inline uint8_t ledarray_get(uint8_t i, uint8_t j) {
  if(i < ROWS && j < COLS) {
    if((la_data[j] & (1<<i)) != 0) {
      return 1;
    } else {
      return 0;
    }
  } else {
    return 0;
  }
}

inline void ledarray_set(uint8_t i, uint8_t j, uint8_t onoff) {
  if(i < ROWS && j < COLS) {
    if(onoff) {
      la_data[j] |= (1<<i);
    } else {
      la_data[j] &= ~(1<<i);
    }
  }
}

inline void ledarray_set_columndriver(uint8_t j, uint8_t onoff, uint8_t sense) {
  // cols 0-5: PC0-5
  // cols 6-11: PD2-7
  if(j < 6) {
    if(onoff) {
      PORTC |= (1 << (PC0 + j));
    } else {
      PORTC &= ~(1<< (PC0 + j));
    }
    if(sense == onoff) {
      DDRC |= (1 << (PC0 + j));
    } else {
      DDRC &= ~(1 << (PC0 + j));
      PORTC &= ~(1 << (PC0 + j));
    }
  } else {
    if(onoff) {
      PORTD |= (1 << (PD2 + (j-6)));
    } else {
      PORTD &= ~(1<< (PD2 + (j-6)));
    }  
    if(sense == onoff) {
      DDRD |= (1 << (PD2 + (j-6)));
    } else {
      DDRD &= ~(1 << (PD2 + (j-6)));
      PORTD &= ~(1 << (PD2 + (j-6)));
    }
  }
}

inline void ledarray_all_off() {
  // turn off all row drivers
  DDRB &= ~( (1<<PB1)|(1<<PB2)|(1<<PB3)|(1<<PB4)|(1<<PB5) );
  PORTB &= ~( (1<<PB1)|(1<<PB2)|(1<<PB3)|(1<<PB4)|(1<<PB5) );
    
  // turn off all column drivers
  DDRC &= ~( (1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC3) | (1<<PC4) | (1<<PC5) );
  PORTC &= ~( (1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC3) | (1<<PC4) | (1<<PC5) );
  DDRD &= ~( (1<<PD2) | (1<<PD3) | (1<<PD4) | (1<<PD5) | (1<<PD6) | (1<<PD7) );
  PORTD &= ~( (1<<PD2) | (1<<PD3) | (1<<PD4) | (1<<PD5) | (1<<PD6) | (1<<PD7) );  
}

SIGNAL(SIG_OVERFLOW0) {
  // turn off old row driver
  DDRB &= ~(1 << (PB1 + real_row));
  PORTB &= ~(1 << (PB1 + real_row));
  ledarray_all_off();

  // increment row number
  if(++la_row == 2*ROWS)
    la_row = 0;

  // set column drivers appropriately
  uint8_t j;
  if(la_row%2 == 0) {
    // even la_row number: fill even columns
    real_row = la_row / 2;
    for(j=0; j<COLS/2; j++) {
      ledarray_set_columndriver(j, ledarray_get(real_row, 2*j), 1);
    }
    // activate row driver SINK
    PORTB &= ~(1 << (PB1 + real_row));
    DDRB |= (1 << (PB1 + real_row));
  } else {
    // odd la_row number: fill odd columns
    real_row = (la_row-1)/2;
    for(j=0; j<COLS/2; j++) {
      ledarray_set_columndriver(j, 1 - ledarray_get(real_row, 2*j + 1), 0);
    }
    // activate row driver SOURCE
    PORTB |= (1 << (PB1 + real_row));
    DDRB |= (1 << (PB1 + real_row));
  }  
}

void ledarray_init() {
  // Timer0 CK/64 (900Hz)
  TCCR0B = (1<<CS01) | (1<<CS00);
  TIMSK0 = (1<<TOIE0);
  
  // outputs (set row drivers high for off)
  DDRC &= ~( (1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC3) | (1<<PC4) | (1<<PC5) );
  DDRD &= ~( (1<<PD2) | (1<<PD3) | (1<<PD4) | (1<<PD5) | (1<<PD6) | (1<<PD7) );
  DDRB &= ~( (1<<PB1)|(1<<PB2)|(1<<PB3)|(1<<PB4)|(1<<PB5) );
}

void ledarray_left_shift() {
  // shift everything one position left
  uint8_t i, j;
  for(i=0; i<ROWS; i++) {
    for(j=0; j<COLS-1; j++) {
      ledarray_set(i,j, ledarray_get(i, j+1));
    }
  }
}

void ledarray_blank() {
  uint8_t i, j;
  for(i=0; i<ROWS; i++) {
    for(j=0; j<COLS; j++) {
      ledarray_set(i,j,0);
    }
  }
}

void ledarray_testpattern() {
  uint8_t i, j;
  ledarray_blank();
  
  for(i=0;i<ROWS;i++) {
    for(j=0;j<COLS;j++) {
      ledarray_set(i,j, 1 - ledarray_get(i,j));
      delay_ms(30);
    }
  }

  for(i=0;i<ROWS;i++) {
    for(j=0;j<COLS;j++) {
      ledarray_set(i,j, 1 - ledarray_get(i,j));
      delay_ms(30);
    }
  }
}


void font_get(char match, char *buf) {
  // copies the character "match" into the buffer
  uint8_t i;
  PGM_P p;
  
  for(i=0; i<FONT_SIZE; i++) {
    memcpy_P(&p, &font[i], sizeof(PGM_P));
    
    if(memcmp_P(&match, p,1)==0) {
      memcpy_P(buf, p, 7);
      return;
    }
  }
  
  // NO MATCH?
  font_get('?', buf);
}

uint8_t font_width(char c) {
  char buf[7];
  buf[1] = 0;
  
  font_get(c, buf);
  
  return buf[1];
}

void font_display(char c, uint8_t offset) {
  char buf[7]; 
  font_get(c, buf);
  
  uint8_t width = buf[1];
  uint8_t i, j;
  for(i=0; i<ROWS; i++) {
    for(j=0; j<width; j++) {
      if((offset + j) < COLS) {
        if( (buf[2+j] & (1<<i)) != 0) {
          ledarray_set(i,offset + j,1);
        } else {
          ledarray_set(i,offset + j,0);
        }
      }
    }
  }
  
  // blank the next column to the right
  for(i=0; i<ROWS; i++) {
    ledarray_set(i, offset+width, 0);
  }
}

void do_testpattern() {
  // mode 1: test pattern
  int8_t offset=0;
  while(1) {
    // break out?
    if(uart_char_is_waiting()) break;

    // test pattern
    ledarray_testpattern();

    // break out?
    if(uart_char_is_waiting()) break;

    // test letters    
    ledarray_blank();
    offset=0;
    font_display('H', offset); offset += font_width('H')+1; delay_ms(1000);
    font_display('E', offset); offset += font_width('E')+1; delay_ms(1000);
    font_display('L', offset); offset += font_width('L')+1; delay_ms(1000);
    font_display('L', offset); offset += font_width('L')+1; delay_ms(1000);
    font_display('O', offset); offset += font_width('O')+1; delay_ms(1000);
    
    // break out?
    if(uart_char_is_waiting()) break;
  }
}

void do_scrolling_display() {
  ledarray_blank();
  int8_t offset = 0, next_offset = 0;
  uint8_t is_started = 0;
  char x=' ';
  
  while(1) {
    if(is_started) {
      delay_ms(125);
      ledarray_left_shift(); 
      if(next_offset > 0) {
        offset -= 1;
        next_offset -= 1;
      }
      font_display(x, offset); 
    } else {
      offset = COLS-1;
    }

    // if we can now accept a new character, tell the computer
    if(next_offset == COLS)
      uart_write('n');
    
    while(uart_char_is_waiting()) {
      if(is_started)
        offset = next_offset;
      
      x = uart_read(); 
      if(x=='a') {
        ledarray_blank();
        return;
      }
      font_display(x, offset);
      next_offset = offset + font_width(x)+1;
      is_started = 1;
       
      // if we can now accept a new character, tell the computer
      if(next_offset <= COLS)
        uart_write('n');
      
    }
    
  }
}

void do_simple_display() {
  ledarray_blank();
  uint8_t offset = 0;
  char buf[16];
  uint8_t bufpos=0, i=0;
  char x;

  while(1) {
    // fill buffer
    x = uart_read();
    
    if(x=='a') {
      // ignore
    } else if(x=='b') {
      // change modes
      ledarray_blank();
      return;
    } else if(x=='\r' || x=='\n') {
      // render
      for(i=0; i<bufpos; i++) {
        if(buf[i]=='z') {
          ledarray_blank();
          offset = 0;
        } else {
          font_display(buf[i], offset); offset += font_width(buf[i])+1;
        }
      }
      // clear buffer for next line
      bufpos = 0;
    } else {  
      // add to buffer
      buf[bufpos] = x;
      if(bufpos < 16-1) bufpos++;
    }    
  }
  
}

int main() {
  ledarray_init();
  
  // activate interrupts
  sei();

  // init serial port
  uart_init();
  FILE uart_stream = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);
  stdin = stdout = &uart_stream;
  
  // mode 1: test pattern
  do_testpattern();

  
  while(1) {
    do_simple_display();
    do_scrolling_display();
  }
  return 0;
}

