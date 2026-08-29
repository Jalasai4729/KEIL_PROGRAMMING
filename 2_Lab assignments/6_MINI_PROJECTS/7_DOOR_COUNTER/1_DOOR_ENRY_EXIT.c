//RCC CLCOK ENABLED 
#define RCC_AHB1ENR (*(volatile int*)0x40023830)
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
	//NESTED VECTOR INTERRUPT CONTROLLER
#define NVIC_ISER0 (*(int*)0xE000E100)
#define NVIC_ISER1 (*(int*)0xE000E104)

//LCD DECLARATOINS
void km_Lcd_init(void);
void km_write_cmd(unsigned char data);
void km_write_data(unsigned char data);
void km_higher_nibble(unsigned char data);
void km_lower_nibble(unsigned char data);
void km_write_string(unsigned char str[]);
// operation

//STRINGS DECLARATIONS
unsigned char str[]="WELCOME";
unsigned char str1[]="DOOR EXIT ENTRY";
unsigned char up[]="ENTRY";
unsigned char up1[]="NOT FULL";
unsigned char dn[]="EXIT";
unsigned char dn1[]="OVERFLOW";
unsigned char c1[]="HOUSE FULL";
unsigned char c2[]="NO ENTRY";


int flag=0;
int counter=0;
#define limit 5
void delay(int t)
{
	int i;
	for(i=0;i<1600*t;i++);
}
int main()
{
	
	//phase a initialization
	RCC_AHB1ENR |= (1 << 1);//SET CLOCK port B         
	RCC_AHB1ENR |= (1 << 2);//SET CLOCK port C
  RCC_APB2ENR |= (1 << 14);//SET CLOCK FOR SYSCFG 14TH BIT
	// PB13 RED
	GPIOB_MODE &= ~(0x3<<26);//CLEAR 27,26 positions 
	GPIOB_MODE |= (0x1<<26);//set 0 1 on 27,26 positions
//PB 14 GREEN
	GPIOB_MODE &= ~(0x3<<28);//CLEAR 29,28 positions 
	GPIOB_MODE |= (0x1<<28);//set 0 1 on 29,28 positions

	//PB 12 BUZZER
		GPIOB_MODE &= ~(0x3<<24);//CLEAR 25,24 positions 
	GPIOB_MODE |= (0x1<<24);//set 0 1 on 25,24 positions


	// Pull-up enable switch pc8
	GPIOC_PUPDR &= ~(3 << 16);
	GPIOC_PUPDR |=  (1 << 16);
 
	//pull up enable switch pc9
	GPIOC_PUPDR &= ~(3 << 18);
	GPIOC_PUPDR |=  (1 << 18);
	
	//PULL ENTER SWITCH PC10
	GPIOC_PUPDR &= ~(3 << 20);
	GPIOC_PUPDR |=  (1 << 20);
	
	// RED , GREEN LEDs ,BUZZER OFF (active LOW)
	GPIOB_ODR |= (1 << 13);
	GPIOB_ODR |=(1<<14);
	GPIOB_ODR &=~(1<<12);

	//SYSTEM CONFIGURE PC 9
	SYSCFG_EXTICR3 &= (~(0xf<<4));
	SYSCFG_EXTICR3 |=(0x2<<4);
	// PC 8	
	SYSCFG_EXTICR3 &= (~(0xf<<0));
	SYSCFG_EXTICR3 |=(0x2<<0);
	
	//PC 10
	SYSCFG_EXTICR3 &= (~(0xf<<8));
	SYSCFG_EXTICR3 |=(0x2<<8);
	
	// SET FTSR PC8 PC9
	EXTI_FTSR |=(0x1<<8);
	EXTI_FTSR |=(0x1<<9);
	EXTI_FTSR |=(0x1<<10);

	
	//SER IMR PC8 PC9
	EXTI_IMR |=(0x1<<8);
	EXTI_IMR |=(0x1<<9);
	EXTI_IMR |=(0x1<<10);

	// NVIC ENABLE
	NVIC_ISER0 |=(0x1<<23);
	NVIC_ISER1 |=(0x1<<8);

 //LCD 
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

 km_write_cmd(0x82);
 km_write_string(str);

km_write_cmd(0xc0);
 km_write_string(str1);

	while (1)
	{
		if(flag==1)
		{
			
			if((counter>=0) && (counter<limit))//limit=5
			{
				 km_write_cmd(0x01);

			km_write_cmd(0x80);
      km_write_string(up);
			km_write_cmd(0xc2);
      km_write_string(up1);
			
		  GPIOB_ODR &= ~(1 << 12); // BUZZER OF
			GPIOB_ODR |= (1 << 13); // RED LED OF

  		GPIOB_ODR &= ~(1 << 14); //UP GREEN LED ON
        delay(100);
			counter++;
			GPIOB_ODR |= (1 << 14); //UP GREEN LED OF
       flag=0;
			}
			else
			{
						  GPIOB_ODR |= (1 << 12); // BUZZER ON
		  GPIOB_ODR &= ~(1 << 13); // RED LED ON

								 km_write_cmd(0x01);

				km_write_cmd(0x80);
       km_write_string(up);
				km_write_cmd(0xc2);
        km_write_string(dn1);
				counter++;
				flag=0;
			}
		
			//delay(1740);
		//EXTI_PR |=(1<<8);
		}
		if(flag==2)
		{
			
			if((counter>limit))//limit=5
			{
			GPIOB_ODR |= (1 << 14); //UP GREEN LED OF
				 km_write_cmd(0x01);

			km_write_cmd(0x80);
      km_write_string(dn);
			km_write_cmd(0xc2);
      km_write_string(dn1);
			
		  GPIOB_ODR |= (1 << 12); // BUZZER ON
		  GPIOB_ODR &= ~(1 << 12); // BUZZER OF

  		//GPIOB_ODR |= (1 << 14); //UP GREEN LED OF
        //delay(1740);
			counter--;
			//GPIOB_ODR |= (1 << 14); //UP GREEN LED OF
       flag=0;
			}
			else
			{
								 km_write_cmd(0x01);

				GPIOB_ODR &= ~(1 << 12); // BUZZER OFF
			  GPIOB_ODR |=(1 << 13); // RED LED OFF
				km_write_cmd(0x80);
       km_write_string(c1);
				km_write_cmd(0xc2);
        km_write_string(c2);
				flag=0;
			}
     }

  }
}
		//	EXTI INTERRUPT HANDLER
void EXTI9_5_IRQHandler(void)
{
    if  (EXTI_PR & (1 << 8))
		{
			flag=1;
			EXTI_PR |=(1<<8);
		}
		
		else if  (EXTI_PR & (1 << 9))
			{
				flag=2;
		   EXTI_PR |=(1<<9);
      }
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

