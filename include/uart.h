#include <stm32f103x6.h>
#include <stdint.h>
#include <stdbool.h>


void initUART1(uint16_t baudrate);
void transmitByte(uint8_t byte);
void transmitString(uint8_t* string, uint8_t length);
uint8_t receiveByte(void);
uint8_t* receiveString(void);