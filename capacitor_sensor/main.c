#include <avr/io.h>
#include "../common/UART.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/power.h>

#define isrPIN PCINT0
void initPCINT0(uint8_t pin) {
    PCICR |= (1<<PCIE0);
    PCMSK0 |= (1<<pin);
}

volatile uint16_t dischargeCount;
ISR(PCINT0_vect) {
    dischargeCount++;
    DDRB |= (1<<isrPIN);
    PORTB |= (1<<isrPIN);
    // above code sets  isrPIN to high
    _delay_us(1); // charge capacitor
    PCIFR = (1<<PCIF0); // clear interrput triggered during charging
    DDRB &= ~(1<<isrPIN);
    PORTB &= ~(1<<isrPIN);
    // discharge
}

volatile uint16_t upper = 5200;
void generateMeter(uint8_t *buf, uint16_t count) {
    if (upper > dischargeCount) {
        uint16_t i;
        while (i < count) {
            buf[i] = '-';
            i++;
        }
    }
}

int main(void ) {
    clock_prescale_set(clock_div_1);
    initUART();
    initPCINT0(isrPIN);
    printString("==[ Serial In ]==\r\n\r\n");

    while(1) {
        dischargeCount=0;
        DDRB |= (1<<isrPIN);
        PORTB |= (1<<isrPIN);
        sei();
        // start charging capacitor to trigger ISR
        _delay_ms(50 );
        cli();
        uint16_t meterCount = ((upper - dischargeCount)/10);
        uint8_t meter[64] = {0};
        if (meterCount > 64) {

            generateMeter(meter, 64);
        } else {

            generateMeter(meter, meterCount);
        }
        printString(meter);
        printWord(dischargeCount);
        printString("->\r\n");
        // test blink
        // _delay_ms(1000);
        // PORTC ^= (1<<PC5);
    }
}

