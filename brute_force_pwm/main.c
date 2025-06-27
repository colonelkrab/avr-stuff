#include <avr/io.h>
#include "../common/UART.h"
#include <util/delay.h>


void pwm(uint8_t brightness) {
    uint8_t i;
    PORTC |= (1<<PC5);
    for(i=0; i<255; i++) {
        if (i>=brightness) {
            PORTC &= ~(1<<PC5);
        }
        _delay_us(80);
    }
}

int main(void ) {
    initUART();
    printString("==[ Serial In ]==\r\n\r\n");
    DDRC |= (1<<PC5);
    uint8_t brightness = 0;
    int8_t direction = 1;
    while(1) {
        if (brightness == 0 ) {
            direction = 1;
        }
        if(brightness == 255) {
            direction= -1;
        }
        brightness += direction;
        pwm(brightness);
        // // test blink
        // _delay_ms(1000);
        // PORTC ^= (1<<PC5);
    }
}

