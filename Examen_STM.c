#include "stm32f4xx.h"

void delay() {
    for(volatile int i=0; i<100000; i++);
}

// Tabla 7 segmentos HEX 
const uint8_t hex7seg[16] = 
{
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F, // 9
    0x77, // A
    0x7C, // B
    0x39, // C
    0x5E, // D
    0x79, // E
    0x71  // F
};

int main() {

    // Habilita reloj 
    RCC->AHB1ENR |= (1<<0) | (1<<1) | (1<<2);

    // PB1, PB0 entradas
    GPIOB->MODER &= ~(0xF);

    // PC1, PC0 entradas
    GPIOC->MODER &= ~(0xF);

    // PA0–PA8 salidas
    GPIOA->MODER |= 0x15555;

    while(1) {

        // Leer switches
        uint8_t b3 = (GPIOB->IDR >> 1) & 1;
        uint8_t b2 = (GPIOB->IDR >> 0) & 1;
        uint8_t b1 = (GPIOC->IDR >> 1) & 1;
        uint8_t b0 = (GPIOC->IDR >> 0) & 1;

        uint8_t num = (b3<<3) | (b2<<2) | (b1<<1) | b0;

        // Impar
        if(num & 1)
            GPIOA->ODR |= (1<<0);
        else
            GPIOA->ODR &= ~(1<<0);

        // Potencia de dos
        if(num != 0 && (num & (num - 1)) == 0)
            GPIOA->ODR |= (1<<1);
        else
            GPIOA->ODR &= ~(1<<1);

        //Mostrar en 7 segmentos
        uint8_t seg = hex7seg[num];

        GPIOA->ODR &= ~(0x1FC);          // limpiar
        GPIOA->ODR |= (seg << 2);        // escribir segmentos

        delay();
    }
}
