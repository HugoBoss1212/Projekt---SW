#include <avr/io.h>
#include <util/delay.h>
#include "HD44780.h"
#include <stdlib.h>
#include <avr/interrupt.h>
#include <string.h>

uint16_t diff = 0;
const char text[] = " Do not go gentle into that good night "
		" Old age should burn and rave at close of day Rage"
		" rage against the dying of the light"
		" Though wise men at their end know dark is right"
		" Because their words had forked no lightning they"
		" Do not go gentle into that good night"
		" Good men the last wave by crying how bright"
		" Their frail deeds might have danced in a green bay"
		" Rage rage against the dying of the light"
		" Wild men who caught and sang the sun in flight"
		" And learn too late they grieved it on its way"
		" Do not go gentle into that good night"
		" Grave men near death who see with blinding sight"
		" Blind eyes could blaze like meteors and be gay"
		" Rage rage against the dying of the light";
const uint16_t rozmiar = sizeof(text);
uint16_t j = 0;

ISR(TIMER1_COMPA_vect){
	char buffor[16];

	LCD_Clear();
	for(uint8_t i = 0; i < 16; i++){
		LCD_WriteData(text[i+j]);
	}
	j++;
}

int main(){
	TCCR1B |= 1<<WGM12;
	OCR1A = 4000;
	TCCR1B |=1<<CS10 | 1<< CS12;
	TIMSK |= 1<<OCIE1A;

	LCD_Initalize();
	sei();
	while(1);

	return 0;
}
