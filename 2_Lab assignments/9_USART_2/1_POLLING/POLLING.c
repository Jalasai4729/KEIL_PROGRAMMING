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
void UART_OUTCHAR(unsigned char ch);
char UART_INCHAR(void);

unsigned char ch='a';
unsigned char s=0;



int main()
{
	//INITIALIZATION PHASE A
	 
	  RCC_AHB1ENR |=(0x1<<0);//clock A
	  GPIOA_MODER |=(0xA<<4);//1010 on PA2 PA3 
	
	//CONFIGARATION PHASE B
	
	GPIOA_AFRL &=~(0x00007700);
		GPIOA_AFRL |=(0x00007700);

	
	RCC_APB1ENR |=(0x1<<17);//ENABLE CLOCK FOR UART
	UART_BRR =0x683;//LOAD BAUD RATE VALUE
	UART_CR1 |=(0x1<<3);//ENABLE TX	
		UART_CR1 |=(0x1<<2);//ENABLE RX

  UART_CR1 |=(0x1<<13);//ENABLE UART UE BIT	

	//OPEARTION PHASE C
	while(1)
	{
		UART_OUTCHAR(ch);//TX 
		ch=UART_INCHAR();
		ch++;	
		
	}
	
}
void UART_OUTCHAR(unsigned char ch)
{
	while(!(UART_SR & (0x1<<7)));//TX
	UART_DR =ch;
}
char UART_INCHAR(void)
{
	         while(!(UART_SR & (0x1<<5)));//TX
	     ch= UART_DR ;
	  return ch;
	      
	    // return ch++;
}



