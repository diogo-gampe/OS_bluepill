
#include <stm32f103x6.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum{

    GPIO_MODE_INPUT  = 0x0,
    GPIO_MODE_OUT_10MHz = 0x1,
    GPIO_MODE_OUT_2MHz  = 0x2,
    GPIO_MODE_OUT_50MHz = 0x3,

} GPIO_MODE_T;


typedef enum{

    ANALOG_INPUT = 0x0,
    FLOATING_INPUT = 0x1,
    INPUT_PULLUPDWN = 0x2,

    OUTPUT_PUSHPULL = 0x0,
    OUTPUT_OPENDRAIN= 0x1,
    ALT_FUNCTION_PUSHPULL = 0x2,
    ALT_FUNCTION_OPENDRAIN = 0x3

} GPIO_CONFIG_T;

/*inicializa GPIOs com modos, e configurações           */
void initGPIOConfig(GPIO_TypeDef *port, uint8_t pin, GPIO_CONFIG_T config, GPIO_MODE_T mode);

/*seta pino HIGH                                        */
void gpioSet(GPIO_TypeDef *port, uint8_t pin);
/*seta pino LOW                                          */
void gpioReset(GPIO_TypeDef *port, uint8_t pin);
/*retorna valor do pino                                  */
bool gpioGet(GPIO_TypeDef *port, uint8_t pin);

/*inverte valor do pino                                   */
void gpioToggle(GPIO_TypeDef *port, uint8_t pin);

