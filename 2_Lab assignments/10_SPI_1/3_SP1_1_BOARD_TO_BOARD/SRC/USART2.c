 #include "../inc/stm32f401rbt6.h"
 #include "../inc/GPIO.h"
  #include "../inc/systicktimer.h"
	 #include "../inc/USART2.h"

//char ch=0;
void KM_USART2_MUX_INIT()
{
	//INITIALIZATION PHASE A
	 
	  RCC_AHB1ENR |=(0x1<<0);//clock A
	
		 	  GPIOA_MODER &=~(0xA<<4);//1010 on PA2 PA3
 GPIOA_MODER |=(0xA<<4);//1010 on PA2 PA3

	   	// GPIOA_MODER |=(0x2<<4);//CLEAR 24-29 POSITIONS PB12-13-14
	   	 //GPIOA_MODER |=(0x2<<6);//CLEAR 24-29 POSITIONS PB12-13-14

	
	 // KM_GPIO_PORT_CONFIG(GPIOA,ALT,2);// PA2 MODE REGESTER SET
 //  KM_GPIO_PORT_CONFIG(GPIOA,ALT,3);//PA3 MODE REGESTER SET

	  GPIOA_AFRL &=~(0x00007700);
		GPIOA_AFRL |=(0x00007700);//PA2 ,PA3

    RCC_APB1ENR |=(0x1<<17);//ENABLE CLOCK FOR UART
}
void KM_USART2_CONFIG()
{
	
	//CONFIGARATION PHASE B
	
	
		USART2_BRR =0x683;//LOAD BAUD RATE VALUE
		USART2_CR1 |=(0x1<<3);//ENABLE TX	
		USART2_CR1 |=(0x1<<2);//ENABLE RX	
	
		//UART_CR1 |=(0x1<<7);//ENABLE TXEIE INTERRUPT	
		USART2_CR1 |=(0x1<<5);//ENABLE RXNEIE INTERRUPT
	
	  NVIC_ISER0 |=(0x1<<23);
   	NVIC_ISER1 |=(0x1<<6);

     USART2_CR1 |=(0x1<<13);//ENABLE UART UE BIT
}
 
void KM_USART2_OUTCHAR(unsigned char ch)
{
	while(!(USART2_SR & (0x1<<7)));//TX
	USART2_DR =ch;
}

char KM_USART2_INCHAR(int  t)
{
	     int i=1000;
	      while(i*t)
				{
	      
        if(USART2_SR & (0x1<<5))//TX
					{
  	      return  USART2_DR ; 
					}
					i--;
				}
}

void KM_USART2_OUT_STR(unsigned char str[])
{
	int i=0;
	while(str[i])
	{
		KM_USART2_OUTCHAR(str[i]);//calling
		i++;
	}
}
