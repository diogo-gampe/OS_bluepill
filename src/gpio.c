
#include "gpio.h"

/*inicializa GPIOs com modos, e configurações           */
void initGPIOConfig(GPIO_TypeDef *port, uint8_t pin, GPIO_CONFIG_T config, GPIO_MODE_T mode){


    // habilita clock do GPIO automaticamente
    if(port == GPIOA)       RCC->APB2ENR |= (1 << 2);
    else if(port == GPIOB)  RCC->APB2ENR |= (1 << 3);
    else if(port == GPIOC)  RCC->APB2ENR |= (1 << 4);
    else if(port == GPIOD)  RCC->APB2ENR |= (1 << 5);
    
    /*Calcula posição de registrador baseado em pino e cria mascara  */
    uint32_t position = (pin % 8) * 4;
    uint32_t mask = (mode) | (config << 2);

    /*Verifica se escreve em CRL ou CRH baseado em pin               */
    if(pin < 8){
    /*limpa os 4 bits de CRL primeiro                                 */
       port->CRL &= ~(0xF << position);
       port->CRL |= mask << position; 
    }
    else{
        port->CRH &= ~(0xF << position);
        port->CRH |= mask << position; 
    }
}

/*seta pino HIGH*/
void gpioSet(GPIO_TypeDef *port, uint8_t pin){

    port->BSRR |= 1 << pin;
}

/*seta pino LOW*/
void gpioReset(GPIO_TypeDef *port, uint8_t pin){
    port->BSRR |= 1 << (pin + 16);    
}

/*retorna valor do pino*/
bool gpioGet(GPIO_TypeDef *port, uint8_t pin){
    return(port->IDR & (1U << pin));
}

/*inverte valor do pino*/
void gpioToggle(GPIO_TypeDef *port, uint8_t pin){
    if (port->ODR & (1 << pin)) {
        gpioReset(port, pin);
    } else {
        gpioSet(port, pin);
    }
}
void gpioWriteBit(GPIO_TypeDef *port, uint8_t pin, bool value){

    if (value) {
        port->ODR |= (1 << pin);   // seta o bit
    } else {
        port->ODR &= ~(1 << pin);  // limpa o bit
    }
}


/*Escreve valor de 8bits em Px0 até Px7                     */
void gpioWriteByte(GPIO_TypeDef *port, uint8_t value) {
    // Limpa PA0..PA7
    port->ODR &= ~0xFFu;

    // Escreve novo valor nos 8 bits menos significativos
    port->ODR |= (value & 0xFFu);
}

