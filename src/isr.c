#include <stm32f103x6.h>
#include <stdint.h>
#include <stdbool.h>
#include "interrupts.h"

extern bool uart_flag = false;
extern bool tim_flag = false;

// Handler da interrupção
void TIM1_UP_IRQHandler(void) {
    if (TIM1_UIF_Flag()) {
        TIM1_UIF_Clear();  // limpa flag 
        tim_flag = true;
    }
    return;
}

void USART1_IRQHandler(void) {
    if (USART1_RXNE_Flag()) {
        uart_flag = true;
    }
}