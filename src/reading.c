#include "stm32l476xx.h"
#include "clock.h"
#include <uart.h>
#include "lim_sel.h"
#include "freq_count.h"
#include "post.h"

int lower,n;


void read(){
	int c=0,pulse_array[1000],pulse,Freq[1000]; //Intialize array to store values

	lower = limit(); //Get lower limit value

		while(c<1000){ //While array size is within range
		while((TIM4->SR & TIM_SR_CC1IF) != 0) //Check if flag is set
		{
				pulse = TIM4->CCR1; //Read CCR1. This clears CC1IF
					if(c<1000) //If there is space in array
					{
						if(pulse < lower+151 && pulse > lower-51) //If the value is within range
						{
							pulse_array[c] = pulse; //Store the value
							c++; //Increment the index
						}

					}
		}
		}
		countFreq(pulse_array,1000,Freq); // Call function to generate the list of counts
		TIM4->CR1 &= ~(TIM_CR1_CEN); //Disable the the timer counter

		if((TIM4->SR & TIM_SR_UIF)!=0){ // Check for overflow
			TIM4->SR &= ~TIM_SR_UIF;
		}
		}