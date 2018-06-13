/*
 * Projekt - SW.c
 *
 * Created: 04.06.2018 11:21:44
 * Author : Kacper Lechowicz
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "HD44780.h"
#include <string.h>
#include <stdio.h>

// Port B1 i B2 do switch S1 i S2
//obs³uga przycisków
#define KEY_NEXT (1<<PB0)
#define KEY_PREVIOUS (1<<PB1)
#define STR1 "Mode 1"
#define STR2 "Mode 2"
#define STR3 "Mode 3"
#define STR4 "Mode 4"
#define STR5 "Mode 5"

void obsluga_delay( uint16_t ms, uint8_t *mode );

uint16_t key_lock1=0, key_lock2=0;
uint16_t delay = 50;

int main(void){
	const char* TAB_MODE[5] = {STR1, STR2, STR3, STR4, STR5};
	uint8_t mode = 0;
	DDRB &= ~KEY_NEXT | ~KEY_PREVIOUS;
	PORTB |= KEY_NEXT | KEY_PREVIOUS;
	 
    while (1){
		obsluga_delay(delay, &mode);
		printf("%s", TAB_MODE[mode]);
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
