#include "../inc/stm32f401rbt6.h"
#include "../inc/GPIO.h"
#include "../inc/systicktimer.h"
#include "../inc/SPI_1.h"


/*

   NSS  = PA4
   SCK  = PA5
   MISO = PA6
	 MOSI = PA7
	 


*/

/************* SPI1_MUX_INIT *************************************************************/

void SPI1_MUX_INIT()
{
	RCC_AHB1ENR |=(0X1<<0);   //PORT A CLOCK
	GPIOA_MODER &=~(0XFF<<8); //PA4_5, PA6-PA7,
	GPIOA_MODER |=(0X2<<8);   //10 ON 8-9 ALT PINS   PA4
	GPIOA_MODER |=(0X2<<10);  //10 ON 10-11 ALT PINS PA5
	GPIOA_MODER |=(0X2<<12);  //10 ON 12-13 ALT PINS PA6
	GPIOA_MODER |=(0X2<<14);  //10 ON 14-15 ALT PINS PA7

	
  GPIOA_AFRL |=(0X5<<16);//ALTERNATE REGISTER ( 5 IS SPI1 PERIPHERAL)
	GPIOA_AFRL |=(0X5<<20);//ALTERNATE REGISTER   5
  GPIOA_AFRL |=(0X5<<24);//ALTERNATE REGISTER   5
  GPIOA_AFRL |=(0X5<<28);//ALTERNATE REGISTER   5

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
	
	
	RCC_APB2ENR |=(0X1<<12); //CLOCK ENABLE SPI1
	SPI1_CR2 |=(0X1<<2);//MSTR BIT MASTER CONFIGARATION BIT ENABLE
	SPI1_CR1 |=(0X1<<0);//SSOE SLAVE OUTPUT ENABLE
	SPI1_CR1 |=(0X1<<8);//SSI
	SPI1_CR1 |=(0X1<<9);//SSM
	SPI1_CR1 |=(0X1<<6);//SPI ENABLE

	
  //	SPI1_CR2 |=(0X1<<7);//TXEIE INTERRUPT ENABLE
	  SPI1_CR2 |=(0X1<<6);//RXNEIE INTERRUPT ENABLE
	  NVIC_ISER1 |=(0X1<<3);//NVIC  35 bit for SPI1	
}

/******** void SPI1_OUTCHAR() ******************************************************/

void SPI1_OUTCHAR(unsigned char ch)
{
	while(!(SPI1_SR & (0x1<<1)));//TXE TRANSMITT BUFFER EMPTY
	SPI1_DR =ch;
	//ch++;

}

/******** void SPI1_INCHAR() **************************************************************/

void SPI1_INCHAR(unsigned char ch)
{
                while(!(SPI1_SR & (0x1<<0)));//RXNE RECEIVE BUFFER NOT EMPTY
	     ch= SPI1_DR ;
      
}


