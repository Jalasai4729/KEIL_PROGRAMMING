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


//SYSTICK TIMER
#define STK_CTRL (*(volatile int *)0xE000E010)
#define STK_LOAD (*(volatile int *)0xE000E014)
#define STK_VAL (*(volatile int *)0xE000E018)


//LCD DECLARATOINS
void km_Lcd_init(void);
void km_write_cmd(unsigned char data);
void km_write_data(unsigned char data);
void km_higher_nibble(unsigned char data);
void km_lower_nibble(unsigned char data);
void km_write_string(unsigned char str[]);

void KM_ITOA_STR();

void stk_init(void);
void KM_mdelay_IT();

// operation

unsigned char str1[]=" STOP WATCH";
unsigned char str3[]="STATUS";
unsigned char str4[]="START TIMER";
unsigned char str5[]="PAUSE TIMER";
unsigned char str6[]="RESET TIMER";
//unsigned char str7[]="00";


unsigned char string[50];

//unsigned char str9[]="* k s s s j *";

volatile int jiffie=0;

int x=0;
int stop_watch_in_mins=00;	
int stop_watch_in_seconds=00;
int seconds=00;
int flaag=0;


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
	
	stk_init();


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
 km_write_string(str1);

//km_write_cmd(0xc1);
//km_write_string(str2);

	while (1)
	{
		if(flaag==1)
		{
			//LCD DISPLAY
			if(x==0)
			{
			km_write_cmd(0x01);
      km_write_cmd(0x80);
      km_write_string(str4);
			km_write_cmd(0xc0);
      km_write_string(str3);
				
				         stop_watch_in_mins=stop_watch_in_seconds/60;
                  km_write_cmd(0xc8);
		         	    KM_ITOA_STR(stop_watch_in_mins);//DISPLAY MINUTES
				
				          	km_write_cmd(0xcD);
                   seconds=(stop_watch_in_seconds % 60);
			          		KM_ITOA_STR(seconds);//DISPLAY MINUTES
 
      			      
				x++;
			}
      //LED DISPLAY
			GPIOB_ODR &= ~(1 << 12); // BUZZER OF
			GPIOB_ODR |= (1 << 13); // RED LED OF
      GPIOB_ODR &= ~(1 << 14); //UP GREEN LED ON
      			      
			
      KM_mdelay_IT(1000);
  		stop_watch_in_seconds++;
			            stop_watch_in_mins=stop_watch_in_seconds/60;
                  km_write_cmd(0xc8);
		         	    KM_ITOA_STR(stop_watch_in_mins);//DISPLAY MINUTES
			
			            	km_write_cmd(0xcD);
                    seconds=(stop_watch_in_seconds % 60);
			          		KM_ITOA_STR(seconds);//DISPLAY MINUTES
 
      			      
			
			GPIOB_ODR |= (1 << 14); //UP GREEN LED OF
			KM_mdelay_IT(1000);
			
			//SECONDS,MINUTES,COUNT
			stop_watch_in_seconds++;
                   stop_watch_in_mins=stop_watch_in_seconds/60;
			             km_write_cmd(0xc8);
		   	           KM_ITOA_STR(stop_watch_in_mins);//DISPLAY MINUTES
      			      
			km_write_cmd(0xcB);
			km_write_data(':');
			
						km_write_cmd(0xcD);
           seconds=(stop_watch_in_seconds % 60);
					KM_ITOA_STR(seconds);//DISPLAY MINUTES
 

		}
		else if(flaag==2)
		{	
			//LCD DISPLAY
			km_write_cmd(0x01);
			km_write_cmd(0x80);
      km_write_string(str5);
			km_write_cmd(0xc0);
		 km_write_string(str3);
			
			
			//TIME PAUSED
			  	km_write_cmd(0xc8);
		   	  KM_ITOA_STR(stop_watch_in_mins);//DISPLAY MINUTES
      			      
			    km_write_cmd(0xcB);
			    km_write_data(':');
			
					km_write_cmd(0xcD);
          seconds=(stop_watch_in_seconds % 60);
					KM_ITOA_STR(seconds);//DISPLAY MINUTES

			
			//LED DISPALY
    	GPIOB_ODR &= ~(1 << 12); // BUZZER OF
			GPIOB_ODR &= ~(1 << 13); // RED LED ON
      GPIOB_ODR |= (1 << 14); //UP GREEN LED OFF
			flaag=0;
			x=0;
		}
		else if(flaag==3)
		{
			//LCD DISPLAY
			km_write_cmd(0x01);
      km_write_cmd(0x80);
      km_write_string(str5);
			km_write_cmd(0xc0);
      km_write_string(str3);
			
			//LDE DISPLAY
			GPIOB_ODR |=(1 << 13); // RED LED OFF
      GPIOB_ODR |= (1 << 14); //UP GREEN LED OFF
		  GPIOB_ODR |= (1 << 12); // BUZZER ON
			KM_mdelay_IT(100);
		  GPIOB_ODR &= ~(1 << 12); // BUZZER OFF

			stop_watch_in_seconds=0;
			stop_watch_in_mins=0;
			seconds=0;
			
			//RESET  TIMER
			  	km_write_cmd(0xc8);
			    // km_write_string(str7);
  

		   	  KM_ITOA_STR(stop_watch_in_mins);//DISPLAY MINUTES
	      
			    km_write_cmd(0xcB);
			    km_write_data(':');
			
					km_write_cmd(0xcD);
          seconds=(stop_watch_in_seconds % 60);
					    //  km_write_string(str7);


					KM_ITOA_STR(stop_watch_in_seconds);//DISPLAY MINUTES
       
			 flaag=0;
			x=0;
		}
  }
}

		//	EXTI INTERRUPT HANDLER
void EXTI9_5_IRQHandler(void)
{
       if  (EXTI_PR & (1 << 8))
		   {
			   flaag=1;
			   EXTI_PR |=(1<<8);
		   }
		   else if  (EXTI_PR & (1 << 9))
			  {
			  	flaag=2;
		      EXTI_PR |=(1<<9);
        }
}
void EXTI15_10_IRQHandler(void)
{
	  if (EXTI_PR & (1<<10))
   	{
		  flaag=3;
	  	EXTI_PR |=(1<<10);
	   }
	
}
void km_Lcd_init(void)
{
    
	  km_write_cmd(0x33);
	  KM_mdelay_IT(1);
	  km_write_cmd(0x32);
    KM_mdelay_IT(2);
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
	KM_mdelay_IT(10);
	GPIOB_ODR &=~(0x1<<8);//EN=0
}
void km_lower_nibble(unsigned char data)
{
	data = (data & (0x0f));
	GPIOB_ODR &=~(0x0f);
	GPIOB_ODR |=(data);
	GPIOB_ODR |=(0x1<<8);//EN=1
	KM_mdelay_IT(100);
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

void KM_ITOA_STR(int num)
{
   	int reminder=0,temp=0;
	  int i=0;
	 int j=0;
	
    while(num)  //CONVERTED TO STRING
  	{
	    reminder  = (num%10);
	  	string[i] =(reminder + '0');
	   	 num= (num/10);
	   	i++;
   	}
		string[i]='\0';
		
		for (j=0;j<i/2;j++)
		{
			temp = string[j];
			string[j]=string[i-1-j];
			string[i-1-j]=temp;
			
		}
	   km_write_string(string); //CALLING STRING

}



void stk_init(void)
{
	//	STK_LOAD = 16000-1;  		//Load 1600000 into STK_LOAD to configure 1msec delay
	//	STK_VAL = 0;		 		//Load some value into STK_VAL to clear field to 0and COUNTFLG bit in STK_CTRL register to 0
	  STK_CTRL |=(0X7<<0);
		
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
		STK_VAL =0;		
    count=(jiffie+ms);
    while (jiffie < count);
	
		//STK_CTRL &= (~(0x1));//Turn off enable of SYStick timer
}

