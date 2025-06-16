#include <avr/io.h>
#include "UART.h"
#include <util/setbaud.h>

void initUART(void) {
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
#if USE_2X
    UCSR0A |= (1 << U2X0);
#else
    UCSR0A &= ~(1 << U2X0);
#endif
    //enable rx and tx
    UCSR0B = (1<<RXEN0) | (1<<TXEN0);
    // default frame is 8 data bits and 1 stop bit
}

uint8_t recieveByte(void ) {
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}

void transmitByte(uint8_t data) {
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = data;
}
void printString(const char myString[]) {
    uint8_t i = 0;
    while (myString[i]) {
        transmitByte(myString[i]);
        i++;
    }
}
void printWord(uint16_t word) {
    transmitByte('0' + (word / 10000));                 /* Ten-thousands */
    transmitByte('0' + ((word / 1000) % 10));               /* Thousands */
    transmitByte('0' + ((word / 100) % 10));                 /* Hundreds */
    transmitByte('0' + ((word / 10) % 10));                      /* Tens */
    transmitByte('0' + (word % 10));                             /* Ones */
}



