/*
 * Projekt - SW.c
 *
 * Created: 04.06.2018 11:21:44
 * Author : Kacper Lechowicz
 * Port B0 i B1 do switch S1 i S2
 * Port A2 to LCD_RS
 * Port A3 to LCD_E
 * Port A4 to LCD_D4
 * Port A5 to LCD_D5
 * Port A6 to LCD_D6
 * Port A7 to LCD_D7
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "HD44780.h"
#include <stdlib.h>
#include <string.h>

#define KEY_NEXT (1<<PB0)
#define KEY_PREVIOUS (1<<PB1)
#define STR1 "Mode 1"
#define STR2 "Mode 2"
#define STR3 "Mode 3"
#define STR4 "Mode 4"
#define STR5 "Mode 5"

void obsluga_delay( uint16_t ms );

uint16_t key_lock1=0, key_lock2=0;
char* TAB_MODE[5] = {STR1, STR2, STR3, STR4, STR5};
uint16_t delay = 50;
uint16_t j = 0;
uint8_t mode = 0;

int main(void){
	//key ports init
	DDRB &= ~KEY_NEXT | ~KEY_PREVIOUS;
	PORTB |= KEY_NEXT | KEY_PREVIOUS;

	//lcd ports init
	TCCR1B |= 1<<WGM12;
	OCR1A = 4000;
	TCCR1B |=1<<CS10 | 1<< CS12;
	TIMSK |= 1<<OCIE1A;
	LCD_Initalize();
	sei();
	 
    while (1){
		switch (mode) {
			case 0: {
			
				obsluga_delay(delay);
			}
			case 1:{
			
				obsluga_delay(delay);
			}
			case 2:{
			
				obsluga_delay(delay);
			}
			case 3:{
			
				obsluga_delay(delay);
			}
			case 4:{
			
				obsluga_delay(delay);
			}
		}
    }
}


void obsluga_delay( uint16_t ms ) {
	while( ms-- ) {
		if( !key_lock1 && !(PINA & KEY_NEXT) ) {
			key_lock1 = 500;
			mode += 1;
			if(mode > 4){ mode = 4; }
		} else if( key_lock1 && (PINA & KEY_NEXT) ) key_lock1--;

		if( !key_lock2 && !(PINA & KEY_PREVIOUS) ) {
			key_lock2 = 500;
			mode -= 1;
			if(mode < 0){ mode = 0; }
		} else if( key_lock2 && (PINA & KEY_PREVIOUS) ) key_lock2--;
		_delay_ms(0.95);
	}
}

ISR(TIMER1_COMPA_vect){
	char buffor[16];
	LCD_Clear();
	for(uint8_t i = 0; i < 16; i++){
		LCD_WriteData(TAB_MODE[mode][i+j]);
	}
	j++;
}