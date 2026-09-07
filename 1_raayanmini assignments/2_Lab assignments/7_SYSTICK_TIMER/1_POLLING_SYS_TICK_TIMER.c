#define RCC_AHB1ENR (*(volatile int*)0x40023830)
#define GPIOB_MODE  (*(volatile int*)0x40020400)
#define GPIOB_ODR   (*(volatile int*)0x40020414)
#define GPIOC_IDR   (*(volatile int*)0x40020810)
#define GPIOC_PUPDR (*(volatile int*)0x4002080C)
#define STK_CTRL (*(volatile int *)0xE000E010)
#define STK_LOAD (*(volatile int *)0xE000E014)
#define STK_VAL (*(volatile int *)0xE000E018)
int count;
int main()
{
	//phase a initialization
	
	            RCC_AHB1ENR |= (1 << 1);//SET CLOCK port B
              STK_CTRL |=(0x05<<0);// set 1 on clock source and enable bit	
	
	//PHASE B CONFIGARATION
	           
	         // PB13 RED LED CONFIGARATION
	         GPIOB_MODE &= ~(0x3<<26);//CLAER 27,26 positions 
	         GPIOB_MODE |= (0x1<<26);//set 0 1 on 27,26 positions
			   //PB 13 RED LED OFF
	         GPIOB_ODR |=(0x1<<13);// RED LED OFF

     
	        //SYSTICK TIMER 
	        STK_LOAD =(1600000-1);//LOAD VALUE
	        STK_VAL =(0X1); //CLEAR VALUE
	        STK_CTRL |=(0x1<<0);//SET 0 TH BIT ON CTRL
	//OPEARTION PHASE
	while(1)
	{
		     GPIOB_ODR &= ~(0x1<<13);// RED LED ON
		//STK_CTRL 
		        while(!(STK_CTRL & (0x1<<16)));
		//count = 1;
		  
		       GPIOB_ODR |=(0x1<<13);//TOGGLE RED LED 

			while(!(STK_CTRL & (0x1<<16)));

	}
}