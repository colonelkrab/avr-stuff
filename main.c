#include <avr/io.h>
#include "common/UART.h"
#include <util/delay.h>

int main(void ) {
    initUART();
    printString("==[ Serial In ]==\r\n\r\n");
    DDRC |= (1<<PC5);
    while(1) {
        // test blink
        _delay_ms(1000);
        PORTC ^= (1<<PC5);
    }
}

