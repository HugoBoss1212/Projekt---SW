/*
 * Projekt - SW.c
 *
 * Created: 04.06.2018 11:21:44
 * Author : Kacper Lechowicz
 // Port B0 i B1 do switch S1 i S2
 // Port A2 to LCD_RS
 // Port A3 to LCD_E
 // Port A4 to LCD_D4
 // Port A5 to LCD_D5
 // Port A6 to LCD_D6
 // Port A7 to LCD_D7
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "HD44780.h"
#include <string.h>
#include <stdio.h>

#define KEY_NEXT (1<<PB0)
#define KEY_PREVIOUS (1<<PB1)
#define STR1 "Mode 1"
#define STR2 "Mode 2"
#define STR3 "Mode 3"
#define STR4 "Mode 4"
#define STR5 "Mode 5"

void obsluga_delay( uint16_t ms, uint8_t *mode );
void print_to_LCD( const char* message);

uint16_t key_lock1=0, key_lock2=0;
uint16_t delay = 50;

int main(void){
	const char* TAB_MODE[5] = {STR1, STR2, STR3, STR4, STR5};
	uint8_t mode = 0;
	DDRB &= ~KEY_NEXT | ~KEY_PREVIOUS;
	PORTB |= KEY_NEXT | KEY_PREVIOUS;
	 
    while (1){
		switch (mode) {
			case 0: {
				print_to_LCD(TAB_MODE[mode]);
			
				obsluga_delay(delay, &mode);
			}
			case 1:{
				print_to_LCD(TAB_MODE[mode]);
			
				obsluga_delay(delay, &mode);
			}
			case 2:{
				print_to_LCD(TAB_MODE[mode]);
			
				obsluga_delay(delay, &mode);
			}
			case 3:{
				print_to_LCD(TAB_MODE[mode]);
			
				obsluga_delay(delay, &mode);
			}
			case 4:{
				print_to_LCD(TAB_MODE[mode]);
			
				obsluga_delay(delay, &mode);
			}
		}
    }
}


void obsluga_delay( uint16_t ms, uint8_t *mode) {
	while( ms-- ) {
		if( !key_lock1 && !(PINA & KEY_NEXT) ) {
			key_lock1 = 500;
			*mode += 1;
			if(*mode > 4){ *mode = 4; }
		} else if( key_lock1 && (PINA & KEY_NEXT) ) key_lock1--;

		if( !key_lock2 && !(PINA & KEY_PREVIOUS) ) {
			key_lock2 = 500;
			*mode -= 1;
			if(*mode < 0){ *mode = 0; }
		} else if( key_lock2 && (PINA & KEY_PREVIOUS) ) key_lock2--;
		_delay_ms(0.95);
	}
}

void print_to_LCD( const char* message){
	;
}