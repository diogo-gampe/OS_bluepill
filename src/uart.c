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
    double usartdiv = (double)clock / (double)baudrate;

    uint32_t mantissa = (uint32_t)usartdiv;
    uint32_t fraction = (uint32_t)((usartdiv - mantissa) * 16.0 + 0.5); // arredonda

    if (fraction == 16) {
        mantissa += 1;
        fraction = 0;
    }

    USART1->BRR = (mantissa << 4) | (fraction);

    // 5. Habilita TX e RX
    USART1->CR1 |= USART_CR1_TE | USART_CR1_RE;

    // 6. Habilita USART
    USART1->CR1 |= USART_CR1_UE;



}
void UART1_transmitByte(uint8_t byte)
{
    while (!(USART1->SR & USART_SR_TXE)); // espera buffer livre
    USART1->DR = byte;
    while (!(USART1->SR & USART_SR_TXE)); // espera buffer livre

}
void UART1_transmitString(uint8_t* string, uint8_t length)
{
    for (uint8_t i = 0; i < length; i++) {
        UART1_transmitByte(string[i]);
    }

}
uint8_t UART1_receiveByte(void)
{
    while (!(USART1->SR & USART_SR_RXNE)); // espera dado chegar
    return (uint8_t)(USART1->DR & 0xFF);
}
uint8_t* UART1_receiveString(uint8_t* buffer, uint8_t maxlen)
{
    uint8_t i = 0;
    while (i < (maxlen - 1)) {
        buffer[i] = UART1_receiveByte();
        i++;
    }
    buffer[i] = '\0'; // termina string
    return buffer;

}