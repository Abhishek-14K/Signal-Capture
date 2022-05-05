#include "stm32l476xx.h"

void pin_init()
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN; //Enabling the GPIOB Clock

	GPIOB->MODER &= ~(3<<12); //pin PB6 in alternate function mode

	GPIOB->MODER |= (2<<12);

	GPIOB->AFR[0] &= ~(15<<24); // Set up AF register to AF2
	GPIOB->AFR[0] |=  (2<<24);

	GPIOB->PUPDR &= ~(3<<12); //Set pin as no pull up and no pull down
}