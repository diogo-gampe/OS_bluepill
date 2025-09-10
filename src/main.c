#include <stm32f103x6.h>
#include <stdlib.h>
#include <stdio.h>


#include "timer.h"
#include "clock.h"
#include "gpio.h"
#include "uart.h"

#define BAUDRATE 115200U


int main(void){

initSysClockPLL();
initUART1(BAUDRATE);
initGPIOConfig(GPIOA, 0, OUTPUT_PUSHPULL, GPIO_MODE_OUT_10MHz);
timer1ConfigInterrupt(10, getClockFrequencyMHz(), 7200);
char a = 'a';

  while(1){
  
    UART1_transmitByte(a);

  }
  return 0;
}

// Handler da interrupção
void TIM1_UP_IRQHandler(void) {
    if (TIM1->SR & TIM_SR_UIF) {
        TIM1->SR &= ~TIM_SR_UIF;  // limpa flag 
        gpioToggle(GPIOA, 0);
    }
    return;
}