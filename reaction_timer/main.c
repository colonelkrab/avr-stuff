#include <avr/io.h>
#include "../common/UART.h"
#include <util/delay.h>

int main(void ) {
    initUART();
    printString("\r\n==[ Serial In ]==");
    TCCR1B |= (1<<CS12)|(1<<CS10); // CPU/1024 = approx 976 clock ticks/s
    DDRC |= (1<<PC5); // led ddr
    uint16_t time;
    while(1) {
        printString("\r\npress any key ");
        char _ = recieveByte(); // wait for key press
        printString("\r\nReady...");
        _delay_ms(500);
        printString("GO");
        PORTC |= (1<<PC5); // led ON
        TCNT1=0;
        loop_until_bit_is_set(PIND,PD4); // button pin here
        time = TCNT1 + 12 ;// add 12 since most reaction times will be around 500ms
        PORTC &= ~(1<<PC5); // led OFF
        printString("\r\nreaction time: ");
        printWord(time);
        printString("ms");
    }
}

