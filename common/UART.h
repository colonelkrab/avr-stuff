#define BAUD 9600
#define F_CPU 1000000

void initUART(void);
void transmitByte(uint8_t data);
uint8_t recieveByte(void);
void printString(const char myString[]);
void printWord(uint16_t word);
