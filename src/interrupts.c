#include "interrupts.h"
/* ========================
   Timer1 (UIF, CCx, etc.)
   ======================== */
bool TIM1_UIF_Flag(void)
{
    return(TIM1->SR & TIM_SR_UIF) ? 1:0;
}
void TIM1_UIF_Clear(void)
{
    TIM1->SR &= ~TIM_SR_UIF;
}
void TIM1_UIF_Enable(void)
{
    TIM1->DIER |= TIM_DIER_UIE;   // Update interrupt enable
    NVIC_EnableIRQ(TIM1_UP_IRQn); // habilita no NVIC
}
void TIM1_UIF_Disable(void)
{
    TIM1->DIER &= ~TIM_DIER_UIE;
    NVIC_DisableIRQ(TIM1_UP_IRQn);
}

/* ========================
   USART1 (RXNE, TXE, etc.)
   ======================== */
bool USART1_RXNE_Flag(void)
{
    return (USART1->SR & USART_SR_RXNE) ? 1 : 0;
}
void USART1_RXNE_Enable(void)
{
    USART1->CR1 |= USART_CR1_RXNEIE;
    NVIC_EnableIRQ(USART1_IRQn);
}
void USART1_RXNE_Disable(void)
{
    USART1->CR1 &= ~USART_CR1_RXNEIE;
    NVIC_DisableIRQ(USART1_IRQn);
}

bool USART1_TXE_Flag(void)
{
    return (USART1->SR & USART_SR_TXE) ? 1 : 0;
}
void USART1_TXE_Enable(void)
{
    USART1->CR1 |= USART_CR1_TXEIE;
    NVIC_EnableIRQ(USART1_IRQn);
}
void USART1_TXE_Disable(void)
{
    USART1->CR1 &= ~USART_CR1_TXEIE;
    NVIC_DisableIRQ(USART1_IRQn);
}
