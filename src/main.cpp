#include <stm32f103x6.h>
#include <stdlib.h>
#include <stdio.h>


#include "timer.h"
#include "clock.h"
#include "gpio.h"

// Handler da interrupção
void TIM1_UP_IRQHandler(void) {
    if (TIM1->SR & TIM_SR_UIF) {
        TIM1->SR &= ~TIM_SR_UIF;  // limpa flag 
        gpioToggle(GPIOA, 0);
    }
    return;
}
int main(void){

initSysClockPLL();
initGPIOConfig(GPIOA, 0, OUTPUT_PUSHPULL, GPIO_MODE_OUT_10MHz);
//timer1ConfigInterrupt(100, 72);
RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; // habilita clock do TIM1

    TIM1->PSC = 36000 - 1;  // prescaler: 36 MHz / 36000 = 1 kHz
    TIM1->ARR = 1000 - 1;   // 1000 ticks = 1 s
    TIM1->EGR = TIM_EGR_UG; // força update para carregar PSC/ARR

    TIM1->DIER |= TIM_DIER_UIE;   // habilita interrupção de update
    NVIC_EnableIRQ(TIM1_UP_IRQn);

    TIM1->CR1 |= TIM_CR1_CEN;     // inicia contador
  while(1){

  }
  return 0;
}