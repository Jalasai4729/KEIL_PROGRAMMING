#define RCC_AHB1ENR (*(volatile int*)0x40023830)
#define GPIOB_ODR   (*(volatile int*)0x40020414)
#define GPIOB_MODE  (*(volatile int*)0x40020400)
	
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

//LCD DECLARATOINS
void km_Lcd_init(void);
void km_write_cmd(unsigned char data);
void km_write_data(unsigned char data);
void km_higher_nibble(unsigned char data);
void km_lower_nibble(unsigned char data);
void km_write_string(unsigned char str[]);


void delay(int t)
{
	int i;
	for(i=0;i<1600*t;i++);
}

//STRINGS DECLARATIONS
unsigned char str[]="WELCOME";

void UART_OUTCHAR(unsigned char ch);
char UART_INCHAR(void);

unsigned char ch='a';
unsigned char s=0;



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
	UART_CR1 |=(0x1<<3);//ENABLE TX	AND RX
		UART_CR1 |=(0x1<<2);//ENABLE TX	AND RX

  UART_CR1 |=(0x1<<13);//ENABLE UART UE BIT	
	
	
	
	//km_Lcd_init();
 
 GPIOB_MODE &=~(0x000003ff);
 GPIOB_MODE |=(0x00000555);
 GPIOB_MODE &=~(0x3<<16);
 GPIOB_MODE |=(0x1<<16);
 
//pins
GPIOB_ODR &=~(0x1f);
GPIOB_ODR |=(0x0f);
 GPIOB_ODR |=(0x1<<8);
	  km_Lcd_init();

	//OPEARTION PHASE C
	while(1)
	{
		UART_OUTCHAR(ch);//TX 
		ch=UART_INCHAR();
		s=ch++;	
		km_write_data(s);
		
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





void km_Lcd_init(void)
{
    
	  km_write_cmd(0x33);
	  delay(20);
	  km_write_cmd(0x32);
    delay(1);
  	km_write_cmd(0x0c);
	  km_write_cmd(0x01);
}
void km_write_cmd(unsigned char data)
{
	GPIOB_ODR &=~(0x1<<4);//RS=0
	km_higher_nibble(data);
	km_lower_nibble(data);
	
}
void km_write_data(unsigned char data)
{
	GPIOB_ODR |=(0x1<<4);//RS=1
	km_higher_nibble(data);
	km_lower_nibble(data);
}
void km_higher_nibble(unsigned char data)
{
	data = data & (0xf0);
	data=(data>>4);
	GPIOB_ODR &=~(0x0f);
	GPIOB_ODR |=(data);
	GPIOB_ODR |=(0x1<<8);//EN=1
	delay(10);
	GPIOB_ODR &=~(0x1<<8);//EN=0
}
void km_lower_nibble(unsigned char data)
{
	data = (data & (0x0f));
	GPIOB_ODR &=~(0x0f);
	GPIOB_ODR |=(data);
	GPIOB_ODR |=(0x1<<8);//EN=1
	delay(10);
	GPIOB_ODR &=~(0x1<<8);//EN=0
}
void km_write_string(unsigned char str[])
{
	int i=0;
	while(str[i])
	{
		km_write_data(str[i]);
		i++;
	}
}




