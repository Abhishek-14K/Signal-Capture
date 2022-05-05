int comparator (const void * p1, const void * p2)
{
  return (*(int*)p1 - *(int*)p2);
}

void countFreq(int a[],int n,int Freq[]){   //Function Definition
	int x,y;
	for(int p=0;p<1000;p++){
		Freq[p]=-1;
	}

	qsort(a,1000,sizeof(int),comparator); //inbuilt function to sort the output values

     for (int i = 0; i < n; i++)
	{
		int Count = 1;

		for(int j = i + 1; j < n; j++)
		{
    		if(a[i] == a[j])    //Check for duplicate elements
    		{
    			Count++;
    			Freq[j] = 0;    //Make sure not to count frequency of same element again
    		}
    	}
    	if(Freq[i] != 0)        // If frequency of current element is not counted
    	{
    		Freq[i] = Count;
		}
	}
    //Print frequency of each element
		x = sprintf((char *)buffer, "List of Counts :\r\n");
		USART_Write(USART2, buffer, x);


 	for (int i = 0; i < n; i++)
  	{
  		if(Freq[i] != 0)
  		{
  			y = sprintf((char *)buffer, "%d Microseconds :  %d Times \r\n", a[i], Freq[i]);
  			USART_Write(USART2, buffer, y);
  			//printf("%d Occurs %d Times \n", a[i], Freq[i]);

		}
  	}
}
