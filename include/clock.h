#include <stm32f103x6.h>
#define EXT_CLOCK_FREQ (8000000UL)
#define INT_CLOCK_FREQ (8000000UL)



void initSysClockPLL(void);
void initSysClockHSI(void);
uint32_t getClockFrequencyHz(void);
uint32_t getClockFrequencyMHz(void);





