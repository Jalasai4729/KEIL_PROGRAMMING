#define RCC_AHB1ENR (*(volatile int*)0x40023830)
	
#define GPIOA_MODER  (*(volatile int*)0x40020000)
	
//SP1_1
#define RCC_APB2ENR  (*(volatile int*)0x40023844)	
#define GPIOA_AFRL   (*(volatile int*)0x40020020)
	
#define SPI1_CR1      (*(volatile int*)0x40013000)  
#define SPI1_CR2      (*(volatile int*)0x40013004)  
#define SPI1_SR       (*(volatile int*)0x40013008)  
#define SPI1_DR       (*(volatile int*)0x4001300C)   

#define NVIC_ISER1 (*(int*)0xE000E104)

char ch='A';
char s;

void SPI1_MUX_INIT();
void SPI1_CONFIG();
void SPI1_OUTCHAR();
void SPI1_INCHAR();
int main()
{
/***** SPI_1 MUX INIT *******************************************/
	
	SPI1_MUX_INIT();
	
/**** SPI_1 CONFIG *************************************************/
	
	SPI1_CONFIG();

/***** OPERATION PHASE ***********************************************/
	
	while(1)
	{
		;
	}
	
}


/************* SPI1_MUX_INIT *************************************************************/

void SPI1_MUX_INIT()
{
	RCC_AHB1ENR |=(0X1);
	GPIOA_MODER &=~(0XFF<<8); //PA4_5, PA6-PA7,
	GPIOA_MODER |=(0XAA<<8);  //10,10 ,10,10 ON ALT PINS 8-15
  GPIOA_AFRL |=(0X5555<<16);//ALTERNATE REGISTER
}

/******* SPI1_CONGIG *******************************************************************/

void SPI1_CONFIG()
{
	RCC_APB2ENR |=(0X1<<12);
	SPI1_CR2 |=(0X1<<2);//MSTR BIT MASTER CONFIGARATION BIT ENABLE
	SPI1_CR1 |=(0X1<<6);//SPI ENABLE
	SPI1_CR1 |=(0X1<<2);//SSOE SLAVE OUTPUT ENABLE
	SPI1_CR2 |=(0X1<<7);//TXEIE INTERRUPT ENABLE
	SPI1_CR2 |=(0X1<<6);//RXNEIE INTERRUPT ENABLE
	NVIC_ISER1 |=(0X1<<3);//NVIC  35 bit for SPI1
	
	
}

/**************** SPI_IRQHandler **********************************************************************/

void SPI1_IRQHandler()
{
	if(SPI1_SR & (0X1<<1))//TXE TRANSMITT BUFFER EMPTY
	{
       SPI1_DR = ch;        // send data
			ch++;
	}
	
	if(SPI1_SR & (0X1<<0)) //RXNE RECEIVE BUFFER NOT EMPTY
	{
         s = SPI1_DR;        // read received data
		//s++;
	}
}
