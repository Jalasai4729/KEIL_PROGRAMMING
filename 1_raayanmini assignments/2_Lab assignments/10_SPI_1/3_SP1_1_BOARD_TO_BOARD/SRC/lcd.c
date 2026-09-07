#include "../inc/lcd.h"
#include "../inc/stm32f401rbt6.h"
 #include "../inc/systicktimer.h"
 #include "../inc/GPIO.h"
  #include "../inc/SYSCFG.h"
 #include "../inc/USART2.h"

 void KM_PIN_LCD_INIT(void)//PINS CONFIGURE
 {
	 GPIOB_MODER &= ~(0XFFFF);
	 	  KM_GPIO_PORT_CONFIG(GPIOB,OUT,0);//PA0 MODE REGESTER SET
	 	  KM_GPIO_PORT_CONFIG(GPIOB,OUT,1);//PA1 MODE REGESTER SET
	 	  KM_GPIO_PORT_CONFIG(GPIOB,OUT,2);//PA2 MODE REGESTER SET
	 	  KM_GPIO_PORT_CONFIG(GPIOB,OUT,3);//PA3 MODE REGESTER SET
	 	  KM_GPIO_PORT_CONFIG(GPIOB,OUT,4);//PA4 MODE REGESTER SET
	 	  KM_GPIO_PORT_CONFIG(GPIOB,OUT,5);//PA5 MODE REGESTER SET
	 	  KM_GPIO_PORT_CONFIG(GPIOB,OUT,8);//PA08 MODE REGESTER SET


 }


void KM_LCD_WRITE_CMD(unsigned char data)
{
	GPIOB_ODR &= ~(0x01<<4);   //to clear 4th bit in GPIOB_ODR to configure RS to instruction register
	KM_WRITE_HIGHER_NIBBLE(data);  //extract high nibble
	KM_WRITE_LOWER_NIBBLE(data); //extract low nibble
}
void KM_LCD_WRITE_DATA(unsigned char data)
{
	GPIOB_ODR |= (0x01<<4);  //to set 4th bit in GPIOB_ODR to configure RS to data register
	KM_WRITE_HIGHER_NIBBLE(data); //extract high nibble
	KM_WRITE_LOWER_NIBBLE(data); //extract low nibble
}


void KM_WRITE_HIGHER_NIBBLE(unsigned char data) //to extract the high nibble of data send to LCD
{
	data = data>>4;          // to extract high nibble from data 
	GPIOB_ODR &= (0XFFFFFFF0); //to clear Least nibble  to load High nibble
	GPIOB_ODR |= data;          //high nibble is Loaded in GPIOB_ODR into PB0,PB1,PB2 and PB3
	GPIOB_ODR |= (0X01<<8);    //PB0,PB1,PB2 and PB3 transfer into LCD data pins
	KM_mdelay_IT(10) ;
	GPIOB_ODR &= ~(0X01<<8);    //clear 8th bit in GPIOB_ODR 
}

void KM_WRITE_LOWER_NIBBLE(unsigned char data) //to extract the low nibble of data send to LCD
{
	data = data&0x0f; // to extract low nibble from data 
	GPIOB_ODR &= (0XFFFFFFF0); //to clear Least nibble to load low nibble
	GPIOB_ODR |= data; //low nibble is Loaded in GPIOB_ODR into PB0,PB1,PB2 and PB3
	GPIOB_ODR |= (0X01<<8); //low nibble is Loaded in GPIOB_ODR into PB0,PB1,PB2 and PB3
	KM_mdelay_IT(10);	
	GPIOB_ODR &= ~(0X01<<8); //clear 8th bit in GPIOB_ODR 
}


void KM_LCD_INIT()
{
  KM_mdelay_IT(20);
	KM_LCD_WRITE_CMD(0x33);
  KM_mdelay_IT(1);
	KM_LCD_WRITE_CMD(0x32);
  KM_LCD_WRITE_CMD(0x0C);
	KM_LCD_WRITE_CMD(0x01);
}
void KM_LCD_WRITE_STR(char str[])
{
    int i;
    for(i = 0; str[i] != '\0'; i++)
    {
       // if(i == 16)
        //    KM_LCD_WRITE_CMD(0xC0); // move to second line

        KM_LCD_WRITE_DATA(str[i]);
    }
}

void KM_ITOA_STR(int num)
{
   	int reminder=0,sum=0;
	  int i=0;
    char string[50];
	
	  while(num)  // REVERSE THE NUMBERS
	  {
	  	sum =(sum*10) +(num % 10);
		  num =num/10;
  	}
	
    while(sum)  //CONVERTED TO STRING
  	{
	    reminder  = (sum%10);
	  	string[i] =(reminder + '0');
	   	 sum= (sum/10);
	   	i++;
   	}
	   string[i]='\0';
	KM_LCD_WRITE_STR(string); //CALLING STRING

}

