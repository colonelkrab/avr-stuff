#include <avr/io.h>
#include "../common/UART.h"
#include <util/delay.h>


void initPWM() {
    TCCR0A = 0b10100011; // set output mode on both pins and fast pwm mode
    TCCR0B |= (1<<CS01); // pwm freq = 1M/256/8 = 488 Hz (fast enough for human eye)
}

int main(void ) {
    initUART();
    printString("==[ Serial In ]==\r\n\r\n");
    initPWM();
    DDRD |= (1<<PD5) | (1<<PD6); // set pwm pins as out
    //start both pins off
    OCR0A = 0;
    OCR0B = 0;
    uint8_t new;
    while(1) {
        new = recieveNumber();
        OCR0A = OCR0B;
        OCR0B = new;
        // // test blink
        // _delay_ms(1000);
        // PORTC ^= (1<<PC5);
    }
}

