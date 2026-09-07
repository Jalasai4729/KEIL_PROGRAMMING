#define RCC_AHB1ENR (*(volatile int*)0x40023830)
	
#define GPIOA_MODER  (*(volatile int*)0x40020000)
	
//SP1_1
#define RCC_APB2ENR  (*(volatile int*)0x40023844)	
#define GPIOA_AFRL   (*(volatile int*)0x40020020)
	
#define SPI1_CR1      (*(volatile int*)0x40013000)  
#define SPI1_CR2      (*(volatile int*)0x40013004)  
#define SPI1_SR       (*(volatile int*)0x40013008)  
#define SPI1_DR       (*(volatile int*)0x4001300C)   	

void SPI1_MUX_INIT();
void SPI1_CONGIG();
void SPI1_OUTCHAR();
void SPI1_INCHAR();
char ch='A';
char s;
int main()
{
/***** SPI_1 MUX INIT *******************************************/
	
	SPI1_MUX_INIT();
	
/**** SPI_1 CONFIG *************************************************/
	
	SPI1_CONGIG();

/***** OPERATION PHASE ***********************************************/
	
	while(1)
	{
		SPI1_OUTCHAR();
		SPI1_INCHAR();
	}
	
}

/************************************************************************************************/

void SPI1_MUX_INIT()
{
	RCC_AHB1ENR |=(0X1); //PORT A CLOCK
	GPIOA_MODER &=~(0XFF<<8);//PA4-5,PA6-7
	GPIOA_MODER |=(0XAA<<8);  //10,10 ,10,10 ON ALT PINS 8-15
  GPIOA_AFRL |=(0X5555<<16);//ALTERNATE REGISTER SPI 
}

/******************************************************************************************************/

void SPI1_CONGIG()
{
	RCC_APB2ENR |=(0X1<<12); //CLOCK FOR SPI
	SPI1_CR2 |=(0X1<<2);//MSTR BIT MASTER CONFIGARATION BIT ENABLE
	SPI1_CR1 |=(0X1<<6);//SPI ENABLE
	SPI1_CR1 |=(0X1<<2);//SSOE SLAVE OUTPUT ENABLE
}


/******************************************************************************************************/

void SPI1_OUTCHAR()
{
	while(!(SPI1_SR & (0x1<<1)));//TXE TRANSMITT BUFFER EMPTY
	SPI1_DR =ch;
	ch++;
}
/*******************************************************************************************************/

void SPI1_INCHAR(void)
{
	         while(!(SPI1_SR & (0x1<<0)));//RXNE RECEIVE BUFFER NOT EMPTY
	     s= SPI1_DR ;
	  //return ch;
}



