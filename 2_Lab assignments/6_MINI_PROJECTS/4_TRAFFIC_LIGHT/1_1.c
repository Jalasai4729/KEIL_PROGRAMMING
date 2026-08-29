// define the physical address using macros
#define RCC_AHB1ENR *((volatile int *)0X40023830)
#define RCC_APB2ENR *((volatile int *)0X40023844)
#define GPIOB_ODR *((volatile int *)0X40020414)
#define GPIOB_MODER *((volatile int *)0X40020400)
#define GPIOC_PUPDR *((volatile int *)0X4002080C)
#define GPIOC_IDR *((volatile int *)0X40020810)
#define SYSCFG_EXTICR3 *((volatile int *)0X40013810)
#define EXTI_FTSR *((volatile int *)0X40013C0C)
#define EXTI_IMR *((volatile int *)0X40013C00)
#define EXTI_PR *((volatile int *)0X40013C14)
#define NVIC_ISER0 *((volatile int *)0XE000E100)
#define NVIC_ISER1 *((volatile int *)0XE000E104)
#define STK_CTRL *((volatile int*)0xE000E010)
#define STK_LOAD *((volatile int*)0xE000E014)
#define STK_VAL  *((volatile int*)0xE000E018)
	
// DECLERATION	
//void EXTI9_5_IRQHandler(void);
//void EXTI15_10_IRQHandler(void);

void KM_LCD_Write_Data(unsigned char data);
void KM_LCD_Init(void);
void KM_LCD_Write_Cmd(unsigned char data);
//void KM_LCD_Write_Data(unsigned char data);
void KM_LCD_Write_Str(unsigned char str[]);
void write_high_nibble(unsigned char data);
void write_low_nibble(unsigned char data);

//unsigned char current_lights;
//unsigned char mode[16]= "MANUAL";


// GLOBAL VARIABLES DECLERATION
int Enter_flag=0; // ENTER FLAG RESET
int Up_flag=0;     // UP FLAG REST
int Dw_flag=0;// DW FLAG RESET

int i=0;

void KM_Systick_Init(void)
{
STK_CTRL    |= (0X1<<2);
STK_LOAD    =  0X123;
STK_VAL = 0X7;  

}

void KM_Mdelay(int n)
{
	STK_LOAD  = (16000*n)-1;	
	STK_VAL   = 0X1;
	STK_CTRL  = (0X5);
	while(!(STK_CTRL & (0x1<<16)));
}


// LCD command
void KM_LCD_Write_Cmd(unsigned char data)
{
	//GPIOB_ODR &= ~(0X1<<5);
	GPIOB_ODR &= ~(0X1<<4);//RS
	write_high_nibble(data);
	write_low_nibble(data);
}
// LCD Data (Multiple characters)
void KM_LCD_Write_Data(unsigned char data)
{
//	GPIOB_ODR &= ~(0X1<<5);
	GPIOB_ODR |= (0X1<<4);//RS
	write_high_nibble(data);
	write_low_nibble(data);
}
// Higher Nibble data in to LCD.
void write_high_nibble( unsigned char data)
{
	data =(data & (0xf0));
		data=(data>>4);

	GPIOB_ODR &= (~(0x0F));
	GPIOB_ODR |= data;
	GPIOB_ODR |= (0x1<<8);
	KM_Mdelay(10);
	GPIOB_ODR &= (~(0x1<<8));
}
//Lower Nibble data in to LCD.
void write_low_nibble(unsigned char data)
{
		data =(data & (0x0f));

	GPIOB_ODR &= (~(0x0F));
	GPIOB_ODR |= data;
	GPIOB_ODR |= (0x1<<8);
	KM_Mdelay(20);
	GPIOB_ODR &= (~(0x1<<8));
}

// LCD Initialization
void KM_LCD_Init(void)
{
	KM_Mdelay(20);
	KM_LCD_Write_Cmd(0X33);
	KM_Mdelay(1);
	KM_LCD_Write_Cmd(0X32);
	KM_LCD_Write_Cmd(0X0C);
	KM_LCD_Write_Cmd(0X01);
	//KM_LCD_Write_Cmd(0X80);		
}
	void KM_LCD_Write_Str(unsigned char str[])
{
	int i=0;
	while(str[i]!='\0')
	{
		KM_LCD_Write_Data(str[i]);
		
		i++;
	}
}
unsigned	char str4[16]="TRAFFIC LIGHTS";

unsigned char str1[16]="STOP IT'S RED";
unsigned	char str2[16]="NOW YOU CAN GO";
unsigned	char str3[16]=" AUTO";
	
//int i=0;

int main()
{
	
	RCC_AHB1ENR |= (0x01<<1); //clock for port b
	RCC_AHB1ENR |= (0x01<<2); // clock for port c
	RCC_APB2ENR |= (0x1<<14); //clock for syscfg exticr3

		//configuration phase for  SWITCH UP PC8,PC9,PC10
	GPIOC_PUPDR &= (~(0X003F0000)); //CLEAR THE 21,20,19,18,17,16 BIT POSITION 
	GPIOC_PUPDR |=  (0X00150000);   // LOAD THE "01" 21,20,19,18,17,16 BIT POSITION IN PULL UP DIRECTION
	
		//configuration phase for SYSCFG
	SYSCFG_EXTICR3 |=(0X00000222); // load the "0010" BIT POSITION OF "11,10,9,8" "7,6,5,4"  "3,2,1,0"
	
	//CONFIG FOR MODER AS OUTPUT
	
	GPIOB_MODER &= ~(0X3F000000);  //CLEAR THE 24-25, 2-27, 28-29 BIT POSITION 
	GPIOB_MODER |= (0X15000000);// LOAD THE "01" IN 24-25, 2-27, 28-29  BIT POSITION 
	
	GPIOB_ODR |=  (0x01<<13); //set the RED LED OFF
	GPIOB_ODR |=  (0x01<<14); //set the GREEN LED OFF
	GPIOB_ODR  &= ~(0X01<<12); //BUZZER OFF
	
	EXTI_FTSR |= (0x01<<8); 
	EXTI_FTSR |= (0x01<<9);
	EXTI_FTSR |= (0x01<<10);
	
	EXTI_IMR |= (0x1<<8);
	EXTI_IMR |= (0x1<<9);
	EXTI_IMR |= (0x1<<10);
	
	// configuration NVIC_ISER0
	NVIC_ISER0 |=(0X1<<23);     // SET THE BIT 23TH BIT IN NVIC_ISER0 
	NVIC_ISER1 |=(0X00000100);  //SET THE BIT 40TH BIT IN NVIC_ISER1 
		KM_Systick_Init();
		
		 //LCD
	 
 GPIOB_MODER &=~(0x000003ff);
 GPIOB_MODER |=(0x00000555);
 GPIOB_MODER &=~(0x3<<16);
 GPIOB_MODER |=(0x1<<16);
 
//pins
GPIOB_ODR &=~(0x1f);
GPIOB_ODR |=(0x0f);
 GPIOB_ODR |=(0x1<<8);

		KM_LCD_Init();
		KM_LCD_Write_Cmd(0X80);		
		KM_LCD_Write_Str(str4);

	while(1)
	{
		
		if(Up_flag==1)        // Up_flag=1 THE CONDITION TRUE RED LED IS ON GREEN LED OFF
		{
			KM_LCD_Write_Cmd(0X01);
			GPIOB_ODR  |= (0x1<<14); //set GREEN LED OFF
			GPIOB_ODR &= ~(0x1<<13); //set RED LED ON
			GPIOB_ODR |= (0x1<<12); //BUZZER ON
			KM_Mdelay(50);
			GPIOB_ODR &=~ (0x1<<12); //BUZZER off
			Enter_flag=0;
	  	Up_flag=0;
				KM_LCD_Write_Cmd(0X01);

			 	KM_LCD_Write_Str(str1);
		}
		if(Dw_flag==1)          //Dw_flag=1 THE CONDITION TRUE RED LED IS OFF GREEN LED ON
		{
			GPIOB_ODR |= (0x1<<13); //set RED LED OFF
				//KM_LCD_Write_Cmd(0X01);
			GPIOB_ODR &= ~(0x1<<14); //set GREEN LED ON
			
			GPIOB_ODR |= (0x1<<12); //BUZZER ON
			KM_Mdelay(50);
			GPIOB_ODR &= ~(0x1<<12); //BUZZER OFF
			
				Dw_flag=0;
				KM_LCD_Write_Cmd(0X01);

					KM_LCD_Write_Str(str2);
		
		}
		if(Enter_flag==1)      //Enter_flag=1 THE CONDITION TRUE RED LED IS ON GREEN LED WILL BE TOGGLE
		{
			KM_LCD_Write_Cmd(0X01);
			GPIOB_ODR ^= (0x1<<13); //toggle RED
			KM_Mdelay(1000);
			GPIOB_ODR ^= (0x1<<14); //toggle RED
			KM_Mdelay(1000);
			GPIOB_ODR &= ~(0x1<<12); //BUZZER OFF
			
				KM_LCD_Write_Cmd(0X01);

					KM_LCD_Write_Str(str3);
			Enter_flag=0.;
			Dw_flag=0;	
		}
	}
}

	
	// handler mode
void EXTI9_5_IRQHandler(void) 
{
	if(EXTI_PR & (0x01<<8))
	{
		Up_flag=1;
		//Dw_flag=0;
		//Enter_flag=0;
		EXTI_PR |= (0x01<<8);
	}
	if(EXTI_PR & (0x01<<9))
	{
		Dw_flag=1;
		//Up_flag=0;
		//Enter_flag=0;
		EXTI_PR |= (0x01<<9);
	}
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_PR & (0X01<<10)) 
	{
		Enter_flag=1;
		//Up_flag=0;
		//Dw_flag=0;
		EXTI_PR |= (0x01<<10); //CLEAR PR
	}
}



/*PROBLEM FACED

--GPIOB_MODER DIDN'T SET BY USING LEFTSHIFT.

*/
