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
//LCD DECLARATIONS
void km_Lcd_init(void);
void km_write_cmd(unsigned char data);
void km_write_data(unsigned char data);
void km_write_higher_nibble(unsigned char data);
void km_write_lower_nibble(unsigned char data);
void km_write_string(unsigned char str[]);

unsigned char str1[]="DIRECTION ";
unsigned char str2[]="CONTROLLER";
unsigned char str3[]="FORWARD";
unsigned char str4[]="REVERSE";
unsigned char str5[]="NEUTAL";


void delay(int t)
{
	int i;
	for(i=0;i<1600*t;i++)
	{
		;
	}
}

int flag=0;
int main()
{
	//phase a initialization
	RCC_AHB1ENR |= ((1 << 1) | (1<<2));//SET CLOCK PORRT B & PORT C        
	//RCC_AHB1ENR |= (1 << 2);//SET CLOCK port C
  RCC_APB2ENR |= (1 << 14);//SET CLOCK FOR SYSCFG 14TH BIT

	
  //PHASE B CONFIFARATIONS
	       //GPIOB_MODER REGISTERS
	       GPIOB_MODE &=(~(0x3f000000));//CLEAR 24-29 POSITIONS PB12-13-14
	       GPIOB_MODE |=(0x15000000);//SRT 01 ON 24-29 POSITIONS PB 12-13-14

	       //GPIOC_PUPDR REGISTERS
	        GPIOC_PUPDR &=~(0x003f0000);//CLEAR 16-21 POSITIONS PB 8_9_10
	        GPIOC_PUPDR |=(0x00150000);//SET 01 ON 16_21 POSITIONS PB 8_9_10
 
         //GPIOB_ RED GREEN LED BOUZZER OFF
	        GPIOB_ODR |=(0x3<<13);
	
         //SYSTEM CONFIGURARTIN PC 8-9-10
	       SYSCFG_EXTICR3 &=~(0x0fff);//CLEAR
		     SYSCFG_EXTICR3 |=(0x0222);//SET ON 0010 PC 8-9-10 BITS POSITIONS

	     	// SET FTSR PC 8-9-10
	         EXTI_FTSR |=((0x7<<8));
	
 	      //SER IMR PC8 PC9
      	  EXTI_IMR |=(0x7<<8);

	      // NVIC ENABLE
	        NVIC_ISER0 |=(0x1<<23); //BASED ON VRCTRO TABLE SET 23 BIT
	        NVIC_ISER1 |=(0x1<<8);//BASED ON VECTROR TABLE SET 8 BIT
				//LCD INITIALIZATION
	        //LCD MODER REGISTERS PINS CONFIGARATINS
	        GPIOB_MODE &=~(0x00030fff); //CLEAR 0-11 16-17 POSITIONS PB 0-5 ,8 PINS 
          GPIOB_MODE |=(0x00010555);//SET 01 ON 0-11 16-17 POSITIONS PB 0-5 ,8 PINS
 
         //LCD INITILIAZATION
            km_Lcd_init();

          km_write_cmd(0x80);//CURSOR ON 1st ROW STARTING POSITION
          km_write_string(str1);//DORECTION
          km_write_cmd(0xc0);//CURSOR ON 1st ROW STARTING POSITION
          km_write_string(str2);//DORECTION

//OPERATION PHASE
	while (1)
	{
		if(flag==1)
		{
		     //LCD DISPLAY	
	        km_write_cmd(0x01);//CLEAR LCD DISPLAY		
			    km_write_cmd(0x80);//CURSOR ON 1st ROW STARTING POSITION
          km_write_string(str3);//DORECTION
   			  km_write_cmd(0xc0);//CURSOR ON 1st ROW STARTING POSITION
          km_write_string(str1);//DORECTION
         
			      GPIOB_ODR &=~(0x1<<14);//GREEN LED ON
            GPIOB_ODR |=(0x1<<13);//RED LED OFF
				    GPIOB_ODR |=(0x1<<12);//BUZZER LED ON
		        delay(100);
		        GPIOB_ODR &=~(0x1<<12);//BUZZER LED OFF
			      flag=0;

		}
		else if(flag==2)
		{
          km_write_cmd(0x01);//CLEAR LCD DISPLAY		
			    km_write_cmd(0x80);//CURSOR ON 1st ROW STARTING POSITION
          km_write_string(str4);//DORECTION
   			  km_write_cmd(0xc0);//CURSOR ON 1st ROW STARTING POSITION
          km_write_string(str1);//DORECTION
			
		      	GPIOB_ODR |=(0x1<<14);//GREEN LED FF
            GPIOB_ODR &=~(0x1<<13);//RED LED ON
				    GPIOB_ODR |=(0x1<<12);//BUZZER LED ON
		        delay(100);
					 GPIOB_ODR &=~(0x1<<12);//BUZZER LED ON
            flag=0;
		}			
		else if(flag==3)
		{
			   km_write_cmd(0x01);//CLEAR LCD DISPLAY		
			    km_write_cmd(0x80);//CURSOR ON 1st ROW STARTING POSITION
          km_write_string(str5);//DORECTION
   			  km_write_cmd(0xc0);//CURSOR ON 1st ROW STARTING POSITION
          km_write_string(str1);//DORECTION
			
			      GPIOB_ODR =(0x1<<14);//GREEN LED OFF
            GPIOB_ODR |=(0x1<<13);//RED LED OFF
				    GPIOB_ODR |=(0x1<<12);//BUZZER LED ON
		        delay(100);
						GPIOB_ODR &=~(0x1<<12);//BUZZER LED ON
             flag=0;
		}
	}
}
//HANDLER MODE ON PB 8-9
void EXTI9_5_IRQHandler(void)
{
	   if(EXTI_PR & (0x1 << 8))
	   {
		  flag=1;
		  EXTI_PR |=(0x1 << 8);//CLEAR PR PENDING STATUS REGESTER
	    }
	   else if(EXTI_PR &(0x1 << 9))
	   {
		  flag=2;
		  EXTI_PR |=(0x1 << 9);//CLEAR PR PENDING STATUS REGESTER
	   }
}

//HANDLER MODE PN PB-10
void EXTI15_10_IRQHandler(void)
{
	   if(EXTI_PR &(0x1 << 10))
	    {
		   flag=3;
		   EXTI_PR |=(0x1 << 10);//CLEAR PR PENDING STATUS REGESTER
	    }
}

void km_Lcd_init()
{
	delay(20);
	km_write_cmd(0x33);
	delay(1);
	km_write_cmd(0x32);
	km_write_cmd(0x0c);
	km_write_cmd(0x01);
	delay(1);

}
void km_write_cmd(unsigned char data)
{
	  GPIOB_ODR &=~(0x1<<4);//CLEAR RS =0 ,PB-4 PIN
    km_write_higher_nibble(data);
    km_write_lower_nibble(data);
}
void km_write_higher_nibble(unsigned char data)
{
	data =(data&(0xf0));//extract higher nibble data
	data=(data>>4);//shift lower bit nibble positions
	GPIOB_ODR &=~(0xf);//CLEAR PB 0-3 PINS
	GPIOB_ODR |=(data);//LOAD DATA PB 0-3 PINS
	GPIOB_ODR |=(0x1<<8);//EN=1 PB 8 PIN
	delay(10);
	GPIOB_ODR &=~(0x1<<8);//EN=0 PB 8 PIN
}
void km_write_lower_nibble(unsigned char data)
{
	data =(data&(0x0f));//extract lower nibble data
	GPIOB_ODR &=~(0xf);//CLEAR PB 0-3 PINS
	GPIOB_ODR |=(data);//LOAD DATA PB 0-3 PINS
	GPIOB_ODR |=(0x1<<8);//EN=1 PB 8 PIN
	delay(10);
	GPIOB_ODR &=~(0x1<<8);//EN=0 PB 8 PIN
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
void km_write_data(unsigned char data)
{
		GPIOB_ODR |=(0x1<<4);//SET 1 RS=1 REGESTER SELECTOR PB-4
	  km_write_higher_nibble(data);
	  km_write_lower_nibble(data);
}
