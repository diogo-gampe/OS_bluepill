#include <stm32f103x6.h>
#include <stdint.h>
#include <stdbool.h>


void initUART1(uint32_t baudrate);
void UART1_transmitByte(uint8_t byte);
void UART1_transmitString(uint8_t* string, uint8_t maxlen);
uint8_t UART1_receiveByte(void);
bool UART1_receiveString(uint8_t* buffer, uint8_t maxlen);