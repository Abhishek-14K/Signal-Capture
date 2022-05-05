#include "stm32l476xx.h"
#include "clock.h"
#include <stdlib.h>

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <uart.h>

uint8_t buffer[100];
int limit(void){

	int		n ;
	char rxByte;
	int lower, upper, low;

	clock_init(); // Initialize system clock
	USART2_Init(115200);	// initialize USART2

	n = sprintf((char *)buffer, "Lower limit: 950 and upper limit: 1050 microseconds. Press 'Y' to accept or 'N' to change.\r\n");
    USART_Write(USART2, buffer, n);

    rxByte = USART_Read(USART2); // Ask for users choice

    if(rxByte==89||rxByte==121){ //If user presses Y proceed with default inputs
    	lower = 1000; low = 950; upper = low+100;
        n = sprintf((char *)buffer, "Lower: %d and Upper: %d \r\n",low,upper);
        USART_Write(USART2, buffer, n);
    }

    else if(rxByte==78||rxByte==110){ //If user presses N ask for new inputs
    	n = sprintf((char *)buffer, "Enter new lower limit.\r\n");
        USART_Write(USART2, buffer, n);
    	lower = limit_select();
    	upper = lower+100;
        n = sprintf((char *)buffer, "Lower: %d and Upper: %d \r\n",lower,upper);
        USART_Write(USART2, buffer, n);
    }

    else{ //If user presses any key other than Y or N throw invalid statement
    	n = sprintf((char *)buffer, "Invalid entry. Try Again.  \r\n");
        USART_Write(USART2, buffer, n);
        limit();
    }


    return lower; //Return lower limit value
}


int limit_select(){
	int		n ;
	char rxByte;
	int num;


	char str[4] = "";

	n = sprintf((char *)buffer, " \r\n");
    USART_Write(USART2, buffer, n);

    rxByte = USART_Read(USART2); //Take user input
    while(rxByte!= 13){ //Until ENTER key is pressed
    	if(rxByte>47 || rxByte<58){ //Only consider 0-9 keys
    		strncat(str,&rxByte,1);
    		rxByte = USART_Read(USART2);
    	}
    }
    num = atoi(str); //Convert ascii to int
    if(num<50 || num>9950){ //Check if number is within range
    	n = sprintf((char *)buffer, "Invalid entry. Valid range is 50 -> 9950. Try Again.  \r\n");
        USART_Write(USART2, buffer, n);
        limit();
    }
    else{
    n = sprintf((char *)buffer, "You entered: %d\r\n",num);
    		    USART_Write(USART2, buffer, n);

    return num;  //Return entered number
    }
}