#include "../inc/STM32F401RBT6.h"
#include "../inc/systicktimer.h"
 
int jiffie=0;

void KM_STK_INIT(void)
{
	//	STK_LOAD = 16000;  		//Load 1600000 into STK_LOAD to configure 1msec delay
	//	STK_VAL = 123;		 		//Load some value into STK_VAL to clear field to 0and COUNTFLG bit in STK_CTRL register to 0
		STK_CTRL |= 0X04;  		//Select clock source as 16MHZ
		STK_CTRL |= 0X01;  		//enable the stktick timer
		STK_CTRL |= 0X01<<1; 	//to interrupt method
	//STK_CTRL |=(0X7<<0);
		
}
//SysTick Interrupt Handler 
void SysTick_Handler(void)
{
    jiffie++;                          // Increment every 1 ms
}

// MILLISECOND DELAY 
void KM_mdelay_IT(int ms)
{
    int count=0;	
		STK_LOAD = 16000-1;  		//Load 1600000 into STK_LOAD to configure 1msec delay
		STK_VAL = 123;		
    count=(jiffie+ms);
    while (count > jiffie);
	
		//STK_CTRL &= (~(0x1));//Turn off enable of SYStick timer

}
