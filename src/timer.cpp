#include <stm32f103x6.h>
#include <stdint.h>
#include <stdbool.h>

/*Define funções para configurar interrupções geradas pelos timers                   */
/*Recebe uma frequência em Hz, um prescaler de 1 até 65535 e uma frequência em MHz                          */

void timer1ConfigInterrupt(uint16_t freq_hz, uint8_t clock_freq){

    uint16_t prescaler;
    uint16_t arr;
     // Loop para encontrar PSC/ARR válidos
    for (prescaler = 0; prescaler < 65536; prescaler++) {
        arr = (clock_freq*(1000000UL) / ((prescaler + 1) * freq_hz)) - 1;
        if (arr <= 0xFFFF) {
            break;  // Encontrou valores válidos
        }
    }
    
    
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;  // Habilita clock TIM1
    TIM1->PSC = prescaler;
    TIM1->ARR = arr;
   
    TIM1->EGR = TIM_EGR_UG;  // gera update event
    TIM1->DIER |= TIM_DIER_UIE;      // Habilita interrupção de update
    NVIC_EnableIRQ(TIM1_UP_IRQn);    // NVIC

    TIM1->CR1 |= TIM_CR1_CEN;        // Inicia contador

}

void timer1ConfigPWM(uint32_t freq_hz, uint8_t clock_freq, uint16_t prescaler, uint8_t duty_cycle, uint8_t channel){
     /*clock_freq em MHz, acha valor do regitrador ARR para gerar sinal de freq_hz   */
    uint16_t arr = (clock_freq*(1000000UL) / ((prescaler + 1) * freq_hz)) - 1;
    uint32_t ccr_value = (uint16_t)(duty_cycle * (arr + 1));
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;  // Clock TIM1

    TIM1->PSC = prescaler;
    TIM1->ARR = arr;

    switch (channel) {
        case 1:
            TIM1->CCR1 = ccr_value;
            TIM1->CCMR1 &= ~TIM_CCMR1_OC1M;
            TIM1->CCMR1 |= (6 << TIM_CCMR1_OC1M_Pos); // PWM1
            TIM1->CCMR1 |= TIM_CCMR1_OC1PE;
            TIM1->CCER  |= TIM_CCER_CC1E;
            break;
        case 2:
            TIM1->CCR2 = ccr_value;
            TIM1->CCMR1 &= ~TIM_CCMR1_OC2M;
            TIM1->CCMR1 |= (6 << TIM_CCMR1_OC2M_Pos);
            TIM1->CCMR1 |= TIM_CCMR1_OC2PE;
            TIM1->CCER  |= TIM_CCER_CC2E;
            break;
        case 3:
            TIM1->CCR3 = ccr_value;
            TIM1->CCMR2 &= ~TIM_CCMR2_OC3M;
            TIM1->CCMR2 |= (6 << TIM_CCMR2_OC3M_Pos);
            TIM1->CCMR2 |= TIM_CCMR2_OC3PE;
            TIM1->CCER  |= TIM_CCER_CC3E;
            break;
        case 4:
            TIM1->CCR4 = ccr_value;
            TIM1->CCMR2 &= ~TIM_CCMR2_OC4M;
            TIM1->CCMR2 |= (6 << TIM_CCMR2_OC4M_Pos);
            TIM1->CCMR2 |= TIM_CCMR2_OC4PE;
            TIM1->CCER  |= TIM_CCER_CC4E;
            break;
    }

    TIM1->EGR  |= TIM_EGR_UG;    // Atualiza registros
    TIM1->BDTR |= TIM_BDTR_MOE;  // Ativa saída principal (Timer avançado)
    TIM1->CR1  |= TIM_CR1_CEN;   // Inicia
}
