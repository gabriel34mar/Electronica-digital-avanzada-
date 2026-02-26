#include "stm32f10x.h"

// Tabla 7 segmentos HEX 
const uint8_t hex7seg[16] = 
{
    0x3F,0x06,0x5B,0x4F,
    0x66,0x6D,0x7D,0x07,
    0x7F,0x6F,0x77,0x7C,
    0x39,0x5E,0x79,0x71
};

void delay() 
{
    for(volatile int i=0; i<100000; i++);
}

int main() 
{

    // Habilitar reloj
    RCC->APB2ENR |= (1<<2) | (1<<3) | (1<<4);

    // PA0–PA8 
    GPIOA->CRL = 0x33333333;  // PA0–PA7
    GPIOA->CRH = 0x00000003;  // PA8

    // PB0, PB1 
    GPIOB->CRL &= ~(0xFF);
    GPIOB->CRL |= 0x44;

    // PC0, PC1 
    GPIOC->CRL &= ~(0xFF);
    GPIOC->CRL |= 0x44;

    while(1) {

        uint8_t b3 = (GPIOB->IDR >> 1) & 1;
        uint8_t b2 = (GPIOB->IDR >> 0) & 1;
        uint8_t b1 = (GPIOC->IDR >> 1) & 1;
        uint8_t b0 = (GPIOC->IDR >> 0) & 1;

        uint8_t num = (b3<<3) | (b2<<2) | (b1<<1) | b0;

        // impar
        if(num & 1)
            GPIOA->BSRR = (1<<0);
        else
            GPIOA->BRR = (1<<0);

        // potencia de 2
        if(num != 0 && (num & (num-1)) == 0)
            GPIOA->BSRR = (1<<1);
        else
            GPIOA->BRR = (1<<1);

        // Mostrar en 7 segmentos 
        GPIOA->ODR &= ~(0x1FC);
        GPIOA->ODR |= (hex7seg[num] << 2);

        delay();
    }
}
