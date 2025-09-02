
#include "clock.h"
void initSysClockPLL(void){

    /*Habilita HSI                                          */
    RCC->CR |= 1 << 0;

    /*Aguarda HSI estabilizar                               */
    while (!(RCC->CR & (1 << 1)));

    /*PLL multiplica clock por 9; clock é 8*9  MHz = 72 MHz */
    RCC->CFGR &= ~(0xF << 18); // limpa PLLMUL
    RCC->CFGR |= (7 << 18); 

    /*Fonte de clock do PLL é HSI                           */
    RCC->CR &= ~(1 << 16); // HSE OFF

    /*disabilita HSE e habilita PLL                         */
    RCC->CR |= (0 << 16);
    RCC->CR |= (1 << 24); 

    /*Aguarda PLL travar                                    */
    while (!(RCC->CR & (1 << 25)));

    /*Seta PLL como sytem clock                             */
    RCC->CFGR &= ~(0x3 << 0); // limpa SW
    RCC->CFGR |= (2 << 0);

}

void initSysClockHSI(void){

      /*Habilita HSI                                          */
    RCC->CR |= 1 << 0;

    /*Aguarda HSI estabilizar                               */
    while (!(RCC->CR & (1 << 1)));

    /*PLL multiplica clock por 9; clock é 8*9  MHz = 72 MHz */
    RCC->CFGR |= (7 << 18); 

    /*Seta PLL como sytem clock                             */
    RCC->CFGR |= (0 << 0);


}