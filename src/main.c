#include "stm32l476xx.h"
#include "clock.h"
#include "pin.h"
#include <uart.h>
#include "post.h"
#include "reading.h"
uint8_t buffer[100];
uint8_t buffer1[100];
char rxByte;
int u,flag;

int main()
{


	//int c,pulse_array[1000],pulse,Freq[1000];


	clock_init(); //Initializing clock for USART

	USART2_Init(115200); //Setting baud rate

	pin_init(); //Initializing GPIO pin

	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM4EN; //Enable clock for Timer 4

	TIM4->PSC = 8-1; //Loading pre scaler value

	TIM4->ARR = 0xFFFF; //Setting Auto Reload value

	TIM4->EGR = TIM_EGR_UG; //Generating an update event to reload prescaler value

	TIM4->CCMR1 &= ~TIM_CCMR1_CC1S; // Clearing CC selection bits

	TIM4->CCMR1 |= TIM_CCMR1_CC1S_0; //Setting up CCMR for the desired capture channel

	TIM4->CCMR1 &= ~(TIM_CCMR1_IC1F); //Disabling input filtering

	TIM4->CCER &= ~(TIM_CCER_CC1P|TIM_CCER_CC1NP); //Clearing bits

	TIM4->CCER |= TIM_CCER_CC1P; //Rising edges generates interrupts

	TIM4->CCMR1 &= ~(TIM_CCMR1_IC1PSC); //Clear input prescaler bits

	TIM4->SMCR &= ~(TIM_SMCR_TS); //Clear trigger selection bits

	TIM4->SMCR |= 4UL << 4; //Selecting input trigger source

	TIM4->SMCR &= ~TIM_SMCR_SMS; //Clear slave mode bits

	TIM4->SMCR |= 4; //Slave mode with reset

	TIM4->CCER |= TIM_CCER_CC1E; //Enable CC1

	TIM4->CR1 |= TIM_CR1_CEN; //Enable timer counter

	flag = power_on_self(); // flag ==1 if input is detected otherwise 0.
	if(flag==1){
		u = sprintf((char *)buffer, "POST Successful!\r\n");
	    USART_Write(USART2, buffer, u);
	}

	//while(1)
	//{
		read(); //function to read the input signal
		flag = 0;
		main(); // Calling the main() function at the end to create a loop

	//}
}





