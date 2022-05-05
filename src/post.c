#include "stm32l476xx.h"
#include "clock.h"
#include <uart.h>
uint8_t buffer[100];
char rxByte;
uint32_t prev1 = 0, pf;
int u;
int flag;

int power_on_self(){

	while(1){

		while(TIM4->CNT - prev1 < 100000){ // checking within 100ms
			if((TIM4->SR & TIM_SR_CC1IF) != 0){ //check if interrupt flag is set
				pf = 1; // If interrupt is called, flag is set
			}
			prev1 = TIM4->CNT; // Previous value becomes current counter value
		}

		if(pf == 0){ //If Interrupt flag is not set

			u = sprintf((char *)buffer, "No input detected. Try Again?Press 'Y' to accept.\r\n");
		    USART_Write(USART2, buffer, u);
		    rxByte = USART_Read(USART2);

		    if(rxByte==89||rxByte==121){ //Take user input to retry
		    	prev1 = 0;
		    	power_on_self();
		}

	}
		if(pf==1){
			prev1 = 0;
			//u1 = sprintf((char *)buffer1, "POST Successful!\r\n");
		   // USART_Write(USART2, buffer1, u1);
		    return pf; //Return a value to main function if POST id successful
		}


	}
}
