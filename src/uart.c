#include "uart.h"
#include "gpio.h"
#include "clock.h"


void initUART1(uint32_t baudrate)
{
     // 1. Habilita clock para USART1
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    // 2. Configura PA9 (TX) como Alternate Function Push-Pull, 50 MHz
    initGPIOConfig(GPIOA, 9, ALT_FUNCTION_PUSHPULL, GPIO_MODE_OUT_50MHz);

    // 3. Configura PA10 (RX) como Floating Input
    initGPIOConfig(GPIOA, 10, FLOATING_INPUT, GPIO_MODE_INPUT);

      // 4. Calcula USARTDIV
    uint32_t clock = getClockFrequencyHz();  // clock APB2 em Hz
   uint32_t usartdiv = (clock + (baudrate/2)) / baudrate; // arredonda para mais próximo
    uint32_t mantissa = usartdiv / 16;
    uint32_t fraction = usartdiv % 16;

    if (fraction == 16) {
        mantissa += 1;
        fraction = 0;
    }

    USART1->BRR = (mantissa << 4) | (fraction);
    // USART1->BRR = 0x139;
    // 5. Habilita USART
    USART1->CR1 |= USART_CR1_UE;
    // 6. Habilita TX e RX
    USART1->CR1 |= USART_CR1_TE | USART_CR1_RE;



}
void UART1_transmitByte(uint8_t byte)
{
    while (!(USART1->SR & USART_SR_TXE)); // espera buffer livre
    USART1->DR = byte;
    gpioToggle(GPIOA, 0);

}
void UART1_transmitString(uint8_t* string, uint8_t maxlen)
{
    for (uint8_t i = 0; i < maxlen; i++) {
        if(string[i] == '\0')
            break;
        else
            UART1_transmitByte(string[i]);

        
    }

}
uint8_t UART1_receiveByte(void)
{
    while (!(USART1->SR & USART_SR_RXNE)); // espera dado chegar
    return (uint8_t)(USART1->DR & 0xFF);
}
bool UART1_receiveString(uint8_t* buffer, uint8_t maxlen)
{
    uint8_t i = 0;
    while (i < maxlen) {
        buffer[i] = UART1_receiveByte();
        if(buffer[i] == '\0')
            break;
        
        i++;
    }
    buffer[i] = '\0'; // termina string
    return true;

}