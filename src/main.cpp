#include <stm32f103x6.h>
#include <stdlib.h>
#include <stdio.h>


#include "clock.h"
#include "gpio.h"
int main(void){

initSysClockPLL();
initGPIOConfig(GPIOA, 0, OUTPUT_PUSHPULL, GPIO_MODE_OUT_10MHz);

volatile uint32_t count = 0;
  while(1){

    while(count < 100000){
      count++;
    }
    gpioToggle(GPIOA, 0);
    count = 0;
  }
  return 0;
}