#define RCC_AHB1ENR (*(volatile int*)0x40023830)
#define RCC_APB2ENR (*(volatile int*)0x40023844)
#define GPIOC_MODER  (*(volatile int*)0x40020800)
#define GPIOB_MODER  (*(volatile int*)0x40020400)
#define GPIOB_ODR (*(volatile int*)0x40020414)
//ADC1 REGESTER ADDRESS
#define ADC1_SQR1    (*(volatile int*)0x4001202C)
#define ADC1_SQR2    (*(volatile int*)0x40012030)
#define ADC1_SQR3    (*(volatile int*)0x40012034)
#define ADC1_CR1     (*(volatile int*)0x40012004)
#define ADC1_CR2     (*(volatile int*)0x40012008)
#define ADC1_SR      (*(volatile int*)0x40012000)
#define ADC1_DR      (*(volatile int*)0x4001204C)

//INTERRUPT
#define NVIC_ISER0   (*(volatile int*)0xE000E100)
#define HTD 3000
#define LTD 2000
int pot = 0;
int temp=0;
int count=0;
int flag=0;
void Delay (int t )
{
	int i;	for(i=0;i<(1600*t);i++);
}

int main()
{
/*********** Initialization Phase *************************/
	
	  RCC_AHB1ENR |= (1 << 2);   // GPIOC clock
	  RCC_AHB1ENR |= (1 << 1);   // GPIOB clock
	
 	RCC_APB2ENR |= (0X1 << 8);   // Clock to ADC1
	
/************* CONFIGARATION PHASE ******************************/

	  GPIOC_MODER &= ~(3 << 0); // clear
		GPIOC_MODER |= (3 << 0); // set 11 PC0 in Analog mode
			GPIOC_MODER |= (3 << 2); // set 11 PC1 in Analog mode
  			GPIOB_MODER |= (0x1 << 26); // MODER LED CONFIGURE
				GPIOB_ODR |=(0x1<<13);//RED LED OFF

	
	//  ADC1_SQR3 |= ( 0XA << 0);   // Loading 01010 0-4 the  VALUE Channel Number 10 POTENTIOMETER
   	ADC1_SQR3 |= ( 0XB << 5);   // Loading 01011 5-9 the  VALUE Channe2 Number 11 LM35 SENSOR
	
		  ADC1_SQR1 |= (2<<20);   // LOAD LENGTH	2 ON SQR1 REGESTER 20-23 POSITIONS
		ADC1_CR2 |= ( 0X1 << 0);    // ADON 
	 ADC1_CR1 |=(0x1<<8);//SET 1 ON SCAN MODE

	//INTERRUPT
	NVIC_ISER0 |=(0x1<<18); //SET 18TH BIT NVIC
  ADC1_CR1 |= (0X1 << 5);//SET EOICE BIT POSITION 
	//  ADC1_CR2 |= (0X1 << 10);//SET EOCS BIT POSITION 
		
	  ADC1_CR1 |= (0X1 << 23);//SET AWDEN BIT POSITION 
	

	 
	 
/************* OPERATION PHASE ************************************/
	while(1)
	{
		
		ADC1_CR2 |= (0x1 << 30); // Set 1 ON SWSTART 
		if(flag==1)
		{
			if(HTD>=pot && LTD<=pot )
			{
				GPIOB_ODR |=(0x1<<13);
				Delay(100);
			}
			else
			{
								GPIOB_ODR &=~(0x1<<13);
			         Delay(100);
			}

		}
	}
}
	void ADC_IRQHandler()
	{
		if(ADC1_SR & (0x1<<1))
		{
			flag=1;
						pot= (ADC1_DR); // Store the Dout value in pot
		//count=2;
		}
	/*	else if(count==2)
		{
			pot=(ADC1_DR);
			count=0;
		}*/
	}


