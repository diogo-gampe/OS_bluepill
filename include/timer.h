#include <stm32f103x6.h>
#include <stdint.h>
#include <stdbool.h>

/*Define funções para configurar interrupções geradas pelos timers                  */
/*Recebe uma frequência em Hz, um prescaler                                  */

void timer1ConfigInterrupt(uint16_t freq_hz, uint8_t clock_freq);
void timer1ConfigPWM(uint32_t freq_hz, uint8_t clock_freq, uint16_t prescaler, uint8_t duty_cycle, uint8_t channel);


