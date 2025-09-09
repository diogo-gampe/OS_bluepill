
#include "clock.h"

void initSysClockPLL(void){

    /*Habilita HSI                                          */
    RCC->CR |= 1 << 0;

    /*Aguarda HSI estabilizar                               */
    while (!(RCC->CR & (1 << 1)));

    /*PLL multiplica clock por 9; clock é (8/2)*9  MHz = 36 MHz */
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

/*Retorna frequencia de clock em Hertz                  */
uint32_t getClockFrequencyHz(){

    uint32_t clock;
    uint32_t source;

    /*captura registrador SWS que define fonte do sysclk        */
    source = (RCC->CFGR & RCC_CFGR_SWS) >> 2;

    switch (source){
        
    /*se SWS = 0x00 clock é HSI                                 */
        case (0x00): 
            clock = INT_CLOCK_FREQ;
            break;
    /*se SWS = 0x01 clock é HSE                                 */
        case(0x01):
            clock = EXT_CLOCK_FREQ;
            break;
    /*se SWS = 0x02 clock é PLL                                 */
        case(0x02):
        {
    /*  Registrador pllmul contém multiplicador de PLL          */
            uint32_t pllmul = ((RCC->CFGR & RCC_CFGR_PLLMULL) >> 18) + 2; 
            uint32_t pllsrc = (RCC->CFGR & RCC_CFGR_PLLSRC) >> 16;

             if (pllsrc == 0) { // HSI/2
                clock = (INT_CLOCK_FREQ / 2) * pllmul;
            } else {            // HSE
                clock = EXT_CLOCK_FREQ* pllmul;
            }
            break;
        }

    }
    
    return clock;
}

uint32_t getClockFrequencyMHz(){
    uint32_t clock = getClockFrequencyHz()/(1000000UL);
    return clock;
}