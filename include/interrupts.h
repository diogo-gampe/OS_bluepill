
#include <stm32f103x6.h>
#include <stdint.h>
#include <stdbool.h>

/* ========================
   Timer1 (UIF, CCx, etc.)
   ======================== */
bool TIM1_UIF_Flag(void);
void TIM1_UIF_Clear(void);
void TIM1_UIF_Enable(void);
void TIM1_UIF_Disable(void);

/* ========================
   USART1 (RXNE, TXE, etc.)
   ======================== */
bool USART1_RXNE_Flag(void);
void USART1_RXNE_Enable(void);
void USART1_RXNE_Disable(void);

bool USART1_TXE_Flag(void);
void USART1_TXE_Enable(void);
void USART1_TXE_Disable(void);

/* ========================
   EXTI (linhas 0–15)
   ======================== */
bool EXTI_Flag(uint8_t line);
void EXTI_Clear(uint8_t line);
void EXTI_Enable(uint8_t line);
void EXTI_Disable(uint8_t line);
