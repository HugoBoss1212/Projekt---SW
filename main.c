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
 * Porty PC od 0 do 7 pod³¹czyæ do led od 0 do 7
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "HD44780.h"
#include <stdbool.h>

#define KEY_NEXT (1<<PB0)
#define KEY_PREVIOUS (1<<PB1)
#define STR1 "Mode 1"
#define STR2 "Mode 2"
#define STR3 "Mode 3"
#define STR4 "Mode 4"
#define STR5 "Mode 5"

void LED_ON(int nr){ PORTC &= ~(1<<nr); }	
void LED_OFF(int nr){ PORTC |= (1<<nr); }	
void LED_TOG(int nr){ PORTC ^= (1<<nr); }	
void LEDS_OFF(){ for(int i = 0; i < 8; i++){LEDS_OFF(i);}}
void LEDS_ON(){ for(int i = 0; i < 8; i++){LEDS_ON(i);}}
bool LED_isON(int nr){ return ((PORTC>>nr)&1 == 1) ? true : false; }
void obsluga_delay( uint16_t ms );

uint16_t key_lock1=0, key_lock2=0;
char* TAB_MODE[5] = {STR1, STR2, STR3, STR4, STR5};
uint16_t delay = 100;
uint16_t j = 0;
uint8_t mode = 0;

int main(void){
	//key ports init
	DDRB &= ~KEY_NEXT | ~KEY_PREVIOUS;
	PORTB |= KEY_NEXT | KEY_PREVIOUS;

	//led init
	DDRC |= 0xff;
	PORTC |= 0;

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
				for (uint8_t i=0; i<8; i++){
					LED_ON(i);
					obsluga_delay(delay);
				}
				for (int8_t i=8; i>-1; i--){
					LED_OFF(i);
					obsluga_delay(delay);
				}
			}
			case 1:{
				for (uint8_t i=0; i<8; i++){
					LED_ON(i);
					if (i>0){ LED_OFF(i-1); }
					obsluga_delay(delay);
				}
				for (int8_t i=8; i>-1; i--){
					LED_ON(i);
					LED_OFF(i+1);
					obsluga_delay(delay);
				}
			}
			case 2:{
				LEDS_ON();
				obsluga_delay(delay);
				LEDS_OFF();
				obsluga_delay(delay);
			}
			case 3:{
				int ports = 0b00000000;
				while (ports != 0b11111111){
					LEDS_OFF();
					for(int i = 0; i < 8; i++){
						if ((ports>>i)&1 == 1){
							LED_ON(i);
						}
					}
					ports++;
					obsluga_delay(delay);
				}
			}
			case 4:{
				for (int i = 0; i < 8; i++){
					LEDS_OFF();
					LED_ON(i);
					LED_ON(7-i);
					obsluga_delay(delay);
				}			
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
	LCD_Clear();
	for(uint8_t i = 0; i < 16; i++){
		LCD_WriteData(TAB_MODE[mode][i+j]);
	}
	j++;
}