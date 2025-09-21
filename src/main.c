#include <stm32f103x6.h>
#include <stdlib.h>
#include <stdio.h>


#include "timer.h"
#include "clock.h"
#include "gpio.h"
#include "uart.h"
#include "interrupts.h"

#define BAUDRATE 115200U
#define MAX_STRING_LEN 255

char c = 0x01;
bool apagando = false;
volatile bool tim_flag;
uint8_t message[3] = {""};
uint8_t byte = 'A';

int main(void){

initSysClockPLL();
initUART1(BAUDRATE);
for(int i = 0; i < 8; i++)
{
  initGPIOConfig(GPIOA, i, OUTPUT_PUSHPULL, GPIO_MODE_OUT_10MHz);
}

timer1ConfigInterrupt(10, getClockFrequencyMHz(), 7200);

while(1){
  
  
  if(tim_flag)
  {
    gpioWriteByte(GPIOA, c);
    if(!apagando)
    {
      c |= c << 1;
      if(c == 0xFF)
        apagando = true;
    }
    else 
    {
      c = c << 1;
      if(c == 0x00){
        c = 0x01;
        apagando = false;
      }
    }
    tim_flag = false;
  }

  }

  return 0;
}