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

int counter1=0;
int counter2=0;
int main()
{
	//phase a initialization
	RCC_AHB1ENR |= (1 << 1);//SET CLOCK port B         
	RCC_AHB1ENR |= (1 << 2);//SET CLOCK port C
  RCC_APB2ENR |= (1 << 14);//SET CLOCK FOR SYSCFG 14TH BIT
	// PB13 RED
	GPIOB_MODE &= ~(0x3<<26);//CLAER 27,26 positions 
	GPIOB_MODE |= (0x1<<26);//set 0 1 on 27,26 positions
//PB 14 GREEN
	GPIOB_MODE &= ~(0x3<<28);//CLAER 29,28 positions 
	GPIOB_MODE |= (0x1<<28);//set 0 1 on 29,28 positions


	// Pull-up enable switch pc8
	GPIOC_PUPDR &= ~(3 << 16);
	GPIOC_PUPDR |=  (1 << 16);
 
	//pull up enable switch pc9
	GPIOC_PUPDR &= ~(3 << 18);
	GPIOC_PUPDR |=  (1 << 18);
	
	// RED , GREEN LEDs OFF (active LOW)
	GPIOB_ODR |= (1 << 13);
	GPIOB_ODR |=(1<<14);

	//SYSTEM CONFIGURE PC 9
	SYSCFG_EXTICR3 &= (~(0xf<<4));
	SYSCFG_EXTICR3 |=(0x2<<4);
	// PC 8	
	SYSCFG_EXTICR3 &= (~(0xf<<0));
	SYSCFG_EXTICR3 |=(0x2<<0);
	
	// SET FTSR PC8 PC9
	EXTI_FTSR |=(0x1<<8);
	EXTI_FTSR |=(0x1<<9);
	
	//SER IMR PC8 PC9
	EXTI_IMR |=(0x1<<8);
	EXTI_IMR |=(0x1<<9);
	
	// NVIC ENABLE
	NVIC_ISER0 |=(0x1<<23);
	while (1)
	{
		;
	}
}
		//	EXTI INTERRUPT HANDLER
void EXTI9_5_IRQHandler(void)
{
    if  (EXTI_PR & (1 << 8))
		{
				GPIOB_ODR ^= (1 << 13);
				counter1++;
		
		EXTI_PR |=(1<<8);
    }
		
		  if  (EXTI_PR & (1 << 9))
		{
				GPIOB_ODR ^= (1 << 14);
				counter2++;
		
		EXTI_PR |=(1<<9);
    }
}
 