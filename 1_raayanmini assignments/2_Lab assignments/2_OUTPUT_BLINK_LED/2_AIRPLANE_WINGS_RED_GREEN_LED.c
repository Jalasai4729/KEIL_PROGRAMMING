#define RCC_AHB1ENR *(int*)0x40023830
#define GPIOB_MODE *(int*)0x40020400
#define GPIOB_ODR *(int*)0x40020414
void delay(int t);	//dalay declaration
int main()
{
	// initialization phase a
	RCC_AHB1ENR |=(0x1<<1); //set rcc clock to gpio port
	
	//phase b configaration GREEN LED
	GPIOB_MODE &=(0x3fffffff);//clear mode 29 28 bits
	GPIOB_MODE |=(0x10000000);//ser 01 on mode 29 28 positions
	GPIOB_ODR |=(0x1<<14);//set 1 output device 
	
	//phase b configaration RED LED
	GPIOB_MODE &=(0xf3ffffff);//clear 27 26 bits
	GPIOB_MODE |=(0x04000000);//set 0 1 on 27 26 bits
	GPIOB_ODR |=(0x1<<13);//set 1 on output data register
	
	while(1)
	{
		int i;
		for(i=1;i<=2;i++)
		{
			//GREEN LED ON 50
		  GPIOB_ODR &=~(0x1<<14);
		  delay(50);
			
			// RED LED ON 50
			GPIOB_ODR &= ~(0x1<<13);
	   	delay(50);
			
			if(i==1)
			{
				//GREEN LED OFF 50m sec
				GPIOB_ODR |=(0x1<<14);
				delay(50);
				
				//RED LED OFF 250m sec
		   GPIOB_ODR |=(0x1<<13);
		    delay(250);
			}
			else if(i==2)
			{
				//GREEN LED OFF
				GPIOB_ODR |=(0x1<<14);
				delay(150);
				
				//RED LED OFF
				GPIOB_ODR |=(0x1<<13);
				delay(500);
			}
	  }
  }
}
void delay(int t)//defination
{
	  int j;
	  for(j=0;j<=5000*t;j++)
	    {
		    ;
    	}
}