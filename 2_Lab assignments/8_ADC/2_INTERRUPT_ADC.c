#define RCC_AHB1ENR (*(volatile int*)0x40023830)
#define RCC_APB2ENR (*(volatile int*)0x40023844)
#define GPIOC_MODER  (*(volatile int*)0x40020800)
	
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
	
int pot = 0;

void Delay (int t )
{
	int i;	for(i=0;i<(1600*t);i++);
}

int main()
{
/*********** Initialization Phase *************************/
	
  RCC_AHB1ENR |= (1 << 2);   // GPIOC clock
 	RCC_APB2ENR |= (0X1 << 8);   // Clock to ADC1
	
/************* CONFIGARATION PHASE ******************************/

	  GPIOC_MODER &= ~(3 << 2); // clear
		GPIOC_MODER |= (3 << 2); // set 11 in Analog mode
	
   	ADC1_SQR3 |= ( 0XB << 0);   // Loading 01011  the  VALUE Channel Number 11
		ADC1_CR2 |= ( 0X1 << 0);    // ADON 
	
	//INTERRUPT
	NVIC_ISER0 |=(0x1<<18); //SET 18TH BIT NVIC
  ADC1_CR1 |= (0X1 << 5);//SET EOICE BIT POSITION 
/************* OPERATION PHASE ************************************/
	while(1)
	{
		
		ADC1_CR2 |= (0x1 << 30); // Set 1 ON SWSTART 
		
	
		Delay (500);
	}  
}
	void ADC_IRQHandler()
	{
						pot = (ADC1_DR); // Store the Dout value in pot
	
	}


