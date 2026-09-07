#define RCC_AHB1ENR (*(volatile int*)0x40023830)
#define RCC_APB2ENR (*(volatile int*)0x40023844)
#define GPIOC_MODER  (*(volatile int*)0x40020800)
	
//ADC1 REGESTER ADDRESS
#define ADC1_SQR1    *(volatile int*)0x4001202C
#define ADC1_SQR2    *(volatile int*)0x40012030
#define ADC1_SQR3    *(volatile int*)0x40012034
#define ADC1_CR1     *(volatile int*)0x40012004
#define ADC1_CR2      *(volatile int*)0x40012008
#define ADC1_SR      *(volatile int*)0x40012000
#define ADC1_DR      *(volatile int*)0x4001204C

//INTERRUPT
#define NVIC_ISER0   (*(volatile int*)0xE000E100)
	
//RCC CLCOK ENABLED 
#define RCC_AHB1ENR (*(volatile int*)0x40023830)
	
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
#define NVIC_ISER1 (*(int*)0xE000E104)
	
int pot = 0;
int temp=0;
int count=0;

void Delay (int t )
{
	int i;	
	for(i=0;i<(1600*t);i++);
}

 
   int main()
{
/*********** Initialization Phase *************************/
	
	  RCC_AHB1ENR |= (1 << 2);   // GPIOC clock
	   RCC_APB2ENR |=(1<<14);    //ADC1
	
/************* CONFIGARATION PHASE ******************************/

	  GPIOC_PUPDR &=~(0x3<<22);
    GPIOC_PUPDR |=(0x01<<22);     //PC01 TO ADC1 11
  	SYSCFG_EXTICR3 &= (~(0xf<<12));
	  SYSCFG_EXTICR3 |=(0x2<<12);//11
	
		  

	
   	GPIOC_MODER &= ~(0x3 << 2); // clear2112331"
    GPIOC_MODER |= (0x3 << 2); // set 11 PC1 in Analog mode
	

	 	RCC_APB2ENR |= (0X1 << 8);   // Clock to ADC1
   	ADC1_SQR3 |= ( 0XB);   // Loading 01011 5-9 the  VALUE Channe2 Number 11 potrntiometer
	
	  //ADC1_SQR1 &= ~(0xf<<20);   // LOAD LENGTH	1 ON SQR1 REGESTER 20-23 POSITIONS
	//  ADC1_CR1 |=(0x1<<8);//SET 1 ON SCAN MODE

	//INTERRUPT
	NVIC_ISER0 |=(0x1<<18); //SET 18TH BIT NVIC
  ADC1_CR1 |= (0X1 << 5);//SET EOICE BIT POSITION  
	 ADC1_CR2 |= (0X1 << 10);//SET EOCS BIT POSITION  not enable
	 
		ADC1_CR2 |= ( 0X1);    // ADON 
	   ADC1_CR2 |=(0xF<<24); // EXTSEL
		ADC1_CR2 |=(0x2<<28);//EXTEN FTSR



	 
/************* OPERATION PHASE ************************************/
	while(1)
	{
		
	 // PC11 pin connected to ground using jumper wire 
		;
   }
}
	void ADC_IRQHandler(void)
	{
		pot =  ADC1_DR & 0xfff;
	}  
