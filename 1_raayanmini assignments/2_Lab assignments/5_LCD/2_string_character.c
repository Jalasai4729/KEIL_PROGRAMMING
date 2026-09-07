#define RCC_AHB1ENR *((int*)0x40023830)
#define GPIOB_MODE *((int*)0x40020400)
#define GPIOB_ODR *((int*)0x40020414)
void delay(int t);	//dalay declaration
//LCD 
//command
void km_write_cmd(unsigned char data);//command 
void km_write_data(unsigned char data);//data
void km_write_higher_nibble(unsigned char data);//higher nibble
void km_write_lower_data(unsigned char data);//lower nibble
void km_lcd_write_str(unsigned char str[]);//string declare
void km_LCD_init();//LCD INITIALIZATION
unsigned char name[]="jala sai yadav  kadala sathish";
//unsigned char name1[]="jalasai123456789";

void km_lcd_write_str(unsigned char str[])
{
	int i=0;
	while(str[i])
	{
		km_write_data(str[i]);
		
		if(i>15)
		{
				 km_write_cmd(0xc0);
			while(str[i])
			{
       km_write_data(str[i]);
				i++;
			}
		}
   i++;	
	}
	
}

int main()
{
	//RCC ENABLE
	RCC_AHB1ENR |=(0x1<<1); //set rcc clock to gpio port
	
	
	//MODE SET ON 01
	GPIOB_MODE &=~(0x3ff);//clear mode all bits
	GPIOB_MODE |=(0x00000555);//set PB0-PB5
	GPIOB_MODE &=~(0x3<<16);//CLEAR 8 PIN
	GPIOB_MODE |=(0x1<<16);//set 01 on 17 16

  //ODR SET 
	GPIOB_ODR |=(0x1f);//set 1 output device PB0-PB5
	GPIOB_ODR |=(0x1<<8);//set 1 on PB8
	
	//LCD CONFIGURE
	 km_LCD_init();
	
	//string start position
		km_write_cmd(0x80);
	 
	//  km_write_cmd(0xc0);
	//CALLING STRING
   km_lcd_write_str(name);
	// km_lcd_write_str(name1);
	 

	while(1)
	{
	
		//SHIFT DISPLAY LEFT TO RIGHT
	//	km_write_cmd(0x1c);   //display shift right
	//	delay(200);
		
;
	}
}
void delay(int t)//defination
{
	int i;
	for(i=0;i<1600*t;i++)
	{
		;
	}
}
void km_write_cmd(unsigned char data)
{
					GPIOB_ODR &=~(0x1<<4);//RS=0 command
      km_write_higher_nibble(data);
	   km_write_lower_data(data);//calling
}
void km_write_data(unsigned char data)
{
			GPIOB_ODR |=(0x1<<4);//RS=1 command
     km_write_higher_nibble(data);
	km_write_lower_data(data);//calling
	
}
void km_write_higher_nibble(unsigned char data)
{
		data=(data & (0xf0));
	  data=(data>>4);
	GPIOB_ODR |=(0x1<<8);//EN =1
	GPIOB_ODR &= (0xfffffff0);
	GPIOB_ODR |=(data);
	GPIOB_ODR &=~(0x1<<8);//EN =0
	delay(10);
}
void km_write_lower_data(unsigned char data)
{
		data=(data & (0x0f));
		GPIOB_ODR |=(0x1<<8);//EN =1
   	GPIOB_ODR &= (0xfffffff0);
	  GPIOB_ODR |=(data);

		GPIOB_ODR &=~(0x1<<8);//EN =0

	delay(10);
}

// INITIALIZATION
void km_LCD_init()
{
	 km_write_cmd(0x33);
	 delay(20);
		km_write_cmd(0x32);
	 delay(1);
	km_write_cmd(0x0c);
	km_write_cmd(0x01);
}
