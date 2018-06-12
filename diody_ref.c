#include <avr/io.h>
#include <util/delay.h>

void Czekaj(uint16_t czas){
        uint16_t i;

        for(i = 0; i < czas; i++)
                _delay_us(1);
}

int main(){
        DDRD |= 1<<PD7;
        int16_t r = 0;
        int16_t b = 0;
        int16_t g = 0;
        uint8_t flag = 0;
        uint8_t licznik = 0;

        while(1){

                PORTD |= 1<<PD7;
                Czekaj(1000 - r);

                PORTD &= ~(1<<PD7);
                Czekaj(r);

                if(licznik >= 3){
                        if(!flag && r < 1000)
                                r++;
                        else if(r >= 1000){
                                r--;
                                flag = 1;
                        }else if(r > 0 && flag)
                                r--;
                        else if(r <= 0 && flag){
                                flag = 0;
                                r++;
                        }

                                licznik = 0;
                }else
                        licznik++;
        }

        return 0;
}
