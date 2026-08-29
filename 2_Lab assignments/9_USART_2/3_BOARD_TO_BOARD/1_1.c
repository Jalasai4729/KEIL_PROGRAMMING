// define the physical address using macros
#define RCC_AHB1ENR   *((volatile int *)0X40023830)
#define RCC_APB1ENR   *((volatile int *)0X40023840)
#define GPIOA_MODER   *((volatile int *)0X40020000)
#define GPIOA_AFRL    *((volatile int *)0X40020020)
#define UART_BRR      *((volatile int *)0X40004408)
#define UART_CR1      *((volatile int *)0X4000440C)
#define UART_SR       *((volatile int *)0X40004400)
#define UART_DR       *((volatile int *)0X40004404)
#define NVIC_ISER1    *((volatile int *)0XE000E104)
#define GPIOC_PUPDR   *((volatile int*)0x04002080c)
#define GPIOB_MODER   *((volatile int*)0x40020400)
#define SYSCFG_EXTICR3  *((volatile int*)0x40013810)
#define EXTI_FTSR    *((volatile int*)0x40013c0c)
#define EXTI_IMR     *((volatile int*)0x40013c00)
#define EXTI_PR      *((volatile int*)0x40013c14)
#define GPIOB_ODR    *((volatile int*)0x40020414)
#define RCC_APB2ENR  *((volatile int*)0x40023844)
#define NVIC_ISER0   *((volatile int*)0xE000E100)
	
// DECLERATION	
//void EXTI9_5_IRQHandler (void);
//void EXTI9_5_IRQHandler(void);

// GLOBAL VARIABLES DECLERATION

int flag=1;
//unsigned char R;
//unsigned char G;
unsigned char ch=0;


void delay(int n)
{
	int i;
	for(i=0;i<1600*n;i++);
}

void UART2_Outchar(unsigned char ch)
{
	  //   while(!(UART_SR & (0X01<<7))); //READ UART2_SR CHECK 7TH BIT(TXE VALUE) 
		UART_DR = ch; //LOAD A INTO UART_DR REGISTER
}


unsigned char UART2_Inchar(void)
{
	//while(!(UART_SR & (0X01<<5))); //READ UART2_SR CHEC WITH 5TH BIT(RXNE) 
	return UART_DR; //READ UART_DR AND STORE 
}


int main()
{

  //Intilization phase
  RCC_AHB1ENR |= (0X1<<1); // set 1 bit enable for GPIOB
	RCC_AHB1ENR |= (0X1<<2); // set 2 bit enable for GPIOC
  //RCC_AHB1ENR |= (0x01<<0); //ENABLE THE PORT A CLOCK
	//RCC_APB1ENR |= (0X01<<17); // UART CLOCK ENABLE 
	RCC_APB2ENR |= (0X1<<14); // set 14 bit enable for SYSCFGEN 
	
	//configuration phase for RED LED AND GREEN LED GPIOB_MODER 
	GPIOB_MODER &=~ (0X3<<28); // CLEAR THE 29,28,27,28 BIT POSITION
	GPIOB_MODER |= (0X01<<28);  // LOAD THE "01" IN 29,28,27,28 BIT POSITION IN OUTPUT DIRECTION
	
	GPIOB_MODER  &= ~(0x03<<26);//RED 01
	GPIOB_MODER  |= (0x01<<26);
	
	
	
	//configuration phase for  SWITCH UP PC8,PC9,PC10
	GPIOC_PUPDR &= (~(0X03<<16)); //CLEAR THE 21,20,19,18,17,16 BIT POSITION 
	GPIOC_PUPDR |=  (0X01<<16);   // LOAD THE "01" 21,20,19,18,17,16 BIT POSITION IN PULL UP DIRECTION
	GPIOC_PUPDR &= (~(0X03<<18)); //CLEAR THE 21,20,19,18,17,16 BIT POSITION 
	GPIOC_PUPDR |=  (0X01<<18); 
	
	
	//configuration phase for SYSCFG
	SYSCFG_EXTICR3 |=(0X00000222); // load the "0010" BIT POSITION OF "11,10,9,8" "7,6,5,4"  "3,2,1,0"
	// configuration EXTI_FTSR 
	EXTI_FTSR |=(0X1<<8);    //SET THE BIT 8TH BIT IN  EXTI_FTSR
	EXTI_FTSR |=(0X1<<9);     //SET THE BIT 9TH BIT IN  EXTI_FTSR

	
	// configuration EXTI_IMR 
	EXTI_IMR  |=(0X1<<8);     //SET THE BIT 8TH BIT IN EXTI_IMR
	EXTI_IMR  |=(0X1<<9);     // SET THE BIT 9TH BIT IN EXTI_IMR

	
	// configuration NVIC_ISER0
	RCC_AHB1ENR |= (0x01<<0); //ENABLE THE PORT A CLOCK
	
	GPIOA_MODER &= ~(0X02<<4);  // ENABLE PA2 AS ALTERNATE FUNCTIONS(LOAD '10' IN GPIOA_MODER)
	GPIOA_MODER  |= (0X2<<4);
	GPIOA_MODER  &=  ~(0X02<<6); // ENABLE PA3 AS ALTERNATE FUNCTIONS(LOAD '10' IN GPIOA_MODER)
	GPIOA_MODER  |= (0X2<<6);
	
	//0GPIOA_MODER |=(0xA<<4);

	NVIC_ISER0 |=(0X1<<23);     // SET THE BIT 23TH BIT IN NVIC_ISER0 
	NVIC_ISER1 |=(0X00000100);  //SET THE BIT 40TH BIT IN NVIC_ISER1 
	GPIOB_ODR |= (0X1<<13);     // 13TH BIT SHOULD BE SET TO BE OFF RED LED
	GPIOB_ODR |= (0X1<<14);     // 14TH BIT SHOULD BE SET TO BE OFF GREEN LED
	
	
	GPIOA_AFRL  &=  ~(0x00007700);
	GPIOA_AFRL  |= (0x00007700); //LOAD '7' IN GPIOA_AFRL TO SELECT UART_TX AND UART_RX FUNCTIONALLY USING MUX REGISTER.
	
	RCC_APB1ENR |= (0X01<<17); // UART CLOCK ENABLE 

	//PHASE B: CONFIGURATION PHASE 
	UART_BRR = (0X683); //BURD RATE FOR 9600 8N1
	UART_CR1 &= ~(0x1<<3); // CLEAR AND ENABLE THE 'TE' IN UART_CR1
	UART_CR1 |= (0x1<<3);//
	UART_CR1 &= ~(0x1<<2); // CLEAR AND ENABLE THE 'RE' IN UART_CR1
	UART_CR1 |= (0x1<<2);
	
		//UART_CR1 |= (0x01<<7); //TXEIE ENABLE FOR INTERRUPT TO GENERATE
	UART_CR1 |= (0x01<<5); //RXNEIE ENABLE FOR INTERRUPT TO GENERATE
	
	   	NVIC_ISER1 |=(0x1<<6);

	UART_CR1 &= ~(0x1<<13);
	UART_CR1 |= (0x1<<13); //SET THE 13TH BIT FOR 'UE' IN UART_CR1

  while(1)
	{
		if(flag==1)
		{
			UART2_Outchar('R');
			flag=0;
		}
		else if(flag==2)
		{
		UART2_Outchar('G');
			flag=0;
		}
		else if(flag==3)
		{
			GPIOB_ODR &= ~(0x01<<13); //RED LED ON
			flag=0;
		}
		else if(flag==4)
		{
			GPIOB_ODR &= ~(0x01<<14); //GREEN LED ON
			flag=0;
		}
	}
}


// handler mode*************************************
//***************************************
	void EXTI9_5_IRQHandler(void)
	{
		if(EXTI_PR &(0x01<<8)) //CHECK THE PR WITH PC8 UNTIL IT SET IF SET THEN FLAG=1
		{
			flag=1;
		EXTI_PR |= (0x01<<8);
		}
		else if(EXTI_PR &(0x01<<9)) //CHECK THE PR WITH PC9 UNTIL IT SET IF SET THEN FLAG=1
		{
			flag=2;
			EXTI_PR |= (0x01<<9);
		}
	}
void USART2_IRQHandler()
{
	ch = UART_DR;
	if(ch=='R') 
	{
		flag=3;
	}
	else if(ch=='G')
	{
		flag=4;
	}
}
