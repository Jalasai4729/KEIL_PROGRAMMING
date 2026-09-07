#define RCC_AHB1ENR (*(volatile int*)0x40023830)
	
#define GPIOA_MODER  (*(volatile int*)0x40020000)
	
//USART
#define RCC_APB1ENR  (*(volatile int*)0x40023840)

#define UART_SR      (*(volatile int*)0x40004400)
#define UART_DR      (*(volatile int*)0x40004404)			
#define UART_BRR     (*(volatile int*)0x40004408)
#define UART_CR1     (*(volatile int*)0x4000440C)
#define UART_CR2     (*(volatile int*)0x40004410)		
#define UART_CR3     (*(volatile int*)0x40004414)			
#define GPIOA_AFRL   (*(volatile int*)0x40020020)
	
#define NVIC_ISER0 (*(int*)0xE000E100)
#define NVIC_ISER1 (*(int*)0xE000E104)

void UART_OUTCHAR(unsigned char ch);
char UART_INCHAR(void);

unsigned char ch='a';
unsigned char alpha;


int main()
{
	//INITIALIZATION PHASE A
	 
	  RCC_AHB1ENR |=(0x1<<0);//clock A
	  GPIOA_MODER |=(0xA<<4);//1010 on PB2 PB3
	
	//CONFIGARATION PHASE B
	
	GPIOA_AFRL &=~(0x00007700);
		GPIOA_AFRL |=(0x00007700);

	
	RCC_APB1ENR |=(0x1<<17);//ENABLE CLOCK FOR UART
	UART_BRR =0x683;//LOAD BAUD RATE VALUE
	UART_CR1 |=(0x1<<3);//ENABLE TX	
		UART_CR1 |=(0x1<<2);//ENABLE RX	
	
		UART_CR1 |=(0x1<<7);//ENABLE TXEIE INTERRUPT	
		UART_CR1 |=(0x1<<5);//ENABLE RXNEIE INTERRUPT
	
	  //NVIC_ISER0 |=(0x1<<23);
   	NVIC_ISER1 |=(0x1<<6);



  UART_CR1 |=(0x1<<13);//ENABLE UART UE BIT	

	//OPEARTION PHASE C
	while(1)
	{
		;
	}
	
}

void USART2_IRQHandler()
{
	 // TX interru	
	if(UART_SR & (0X1<<7))
	{
       UART_DR = ch;        // send data
			ch++;
	}
	
	if(UART_SR & (0X1<<5))
	{
   // RX interrupt
         alpha= UART_DR;        // read received data
		alpha++;
	}
   
}

