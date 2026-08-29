

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


//RCC CLCOK ENABLED 
#define RCC_APB2ENR (*(int*)0x40023844)
	
#define GPIOB_MODE  (*(volatile int*)0x40020400)
#define GPIOB_ODR   (*(volatile int*)0x40020414)

#define GPIOC_PUPDR (*(volatile int*)0x4002080C)
	
	//SYSTEM CONFIGARATION
#define SYSCFG_EXTICR3 (*(int *)0x40013810)
	//FALLING TRIGGER SELECTION REGISTER
#define EXTI_FTSR (*(int*)0x40013C0C)
	//INTERRUPT MASK REGISTER
#define EXTI_IMR (*(int*)0x40013C00)
	//
#define EXTI_PR (*(int*)0x40013C14)
	
//LCD

void delay(int t)
{
	int i;
	for(i=0;i<1600*t;i++);
}


void UART_OUTCHAR(unsigned char ch);
char UART_INCHAR(void);

unsigned char ch=0;
unsigned char r='R';
unsigned char g='G';

int flag=0;

int main()
{
	
	//phase a initialization
	RCC_AHB1ENR |= ((1 << 1) | (1<<2));//SET CLOCK PORRT B & PORT C        
	//RCC_AHB1ENR |= (1 << 2);//SET CLOCK port C
  RCC_APB2ENR |= (1 << 14);//SET CLOCK FOR SYSCFG 14TH BIT

	
  //PHASE B CONFIFARATIONS
	 //GPIOB_MODER REGISTERS
	 GPIOB_MODE &=(~(0x3f000000));//CLEAR 24-29 POSITIONS PB12-13-14
	 GPIOB_MODE |=(0x15000000);//SRT 01 ON 24-29 POSITIONS PB 12-13-14

 //GPIOC_PUPDR REGISTERS
	GPIOC_PUPDR &=~(0x003f0000);//CLEAR 16-21 POSITIONS PC 8_9_10
	GPIOC_PUPDR |=(0x00150000);//SET 01 ON 16_21 POSITIONS PC 8_9_10
		 
 //GPIOB_ RED GREEN LED BOUZZER OFF
	GPIOB_ODR |=(0x3<<13);

 //SYSTEM CONFIGURARTIN PC 8-9-10
 SYSCFG_EXTICR3 &=~(0x0fff);//CLEAR
 SYSCFG_EXTICR3 |=(0x0222);//SET ON 0010 PC 8-9-10 BITS POSITIONS

	// SET FTSR PC 8-9-10
		 EXTI_FTSR |=((0x7<<8));

	//SER IMR PC8 PC9
		EXTI_IMR |=(0x7<<8);
	// NVIC ENABLE
		NVIC_ISER0 |=(0x1<<23); //BASED ON VRCTRO TABLE SET 23 BIT
		NVIC_ISER1 |=(0x1<<8);
					
					
	//INITIALIZATION PHASE A
	 
	  RCC_AHB1ENR |=(0x1<<0);//clock A
	  GPIOA_MODER |=(0xA<<4);//1010 on PA2 PA3

	
	//CONFIGARATION PHASE B
	
	GPIOA_AFRL &=~(0x00007700);
		GPIOA_AFRL |=(0x00007700);//PA2 ,PA3

		
		RCC_APB1ENR |=(0x1<<17);//ENABLE CLOCK FOR UART
		UART_BRR =0x683;//LOAD BAUD RATE VALUE
		UART_CR1 |=(0x1<<3);//ENABLE TX	
		UART_CR1 |=(0x1<<2);//ENABLE RX	
	
		//UART_CR1 |=(0x1<<7);//ENABLE TXEIE INTERRUPT	
		UART_CR1 |=(0x1<<5);//ENABLE RXNEIE INTERRUPT
	
	  NVIC_ISER0 |=(0x1<<23);
   	NVIC_ISER1 |=(0x1<<6);



  UART_CR1 |=(0x1<<13);//ENABLE UART UE BIT	

	

//OPERATION PHASE
	while (1)
	{
		    if(flag==1)
		     {
		        UART_DR=r;
					 flag=0;
	       	}
		
	      	else if(flag==2)
		      {
           UART_DR=g;
						flag=0;
	       	}
		
	     	else if( (ch=='R') || (ch=='r') )
			   {
            GPIOB_ODR &=~(0x1<<13);//RED LED ON
					 delay(200);
					GPIOB_ODR |=(0x1<<13);//RED LED OFF

			    }
			
			   else if( (ch=='G') || (ch=='g') )
			    {
				
				   GPIOB_ODR &=~(0x1<<14);//GREEN LED ON
						delay(200);
					 GPIOB_ODR |=(0x1<<14);//GREEN LED OFF
	
			    }

		}			
		
}

void USART2_IRQHandler()
{
   // RX interrupt
         ch = UART_DR;        // read received data

}

//HANDLER MODE ON PB 8-9
void EXTI9_5_IRQHandler(void)
{
	   if(EXTI_PR & (0x1 << 8))
	   {
		  flag=1;
		  EXTI_PR |=(0x1 << 8);//CLEAR PR PENDING STATUS REGESTER
	    }
	   else if(EXTI_PR &(0x1 << 9))
	   {
		  flag=2;
		  EXTI_PR |=(0x1 << 9);//CLEAR PR PENDING STATUS REGESTER
	   }
}

