// : Whenever SW_ENT Press turn ON BUZZER up to 250msec and Turn OFF BUZZER.

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
	
	//RISING TRIGGER SELECTION REGISTER
#define EXTI_RTSR (*(int*)0x40013C08)
	
	//INTERRUPT MASK REGISTER
#define EXTI_IMR (*(int*)0x40013C00)
	//
#define EXTI_PR (*(int*)0x40013C14)
	//NESTED VECTOR INTERRUPT CONTROLLER
#define NVIC_ISER1 (*(int*)0xE000E104)
	
int counter=0;
int flag=0;
int main()
{
	//phase a initialization
	RCC_AHB1ENR |= (1 << 1);//SET CLOCK port B
	RCC_AHB1ENR |= (1 << 2);//SET CLOCK port C
  RCC_APB2ENR |= (1 << 14);//SET CLOCK FOR SYSCFG 14TH BIT
	// PB13 RED
	GPIOB_MODE &= ~(0x3<<24);//CLAER 25,24 positions 
	GPIOB_MODE |= (0x1<<24);//set 0 1 on 25,24 positions
	
	GPIOB_MODE |= (0x1<<26);//set 0 1 on 25,24 positions


	// Pull-up enable
	GPIOC_PUPDR &= ~(3 << 20);
	GPIOC_PUPDR |=  (1 << 20);

	// BUZZER OFF (active LOW)
	GPIOB_ODR &= ~(1 << 12);
//	GPIOB_ODR &= ~(1 << 13);

	//SYSTEM CONFIGURE

	SYSCFG_EXTICR3 |= (0x2<<8);
	
	EXTI_FTSR |=(0x1<<10);
	//EXTI_RTSR |=(0x1<<10);
	EXTI_IMR |=(0x1<<10);
	
	// NVIC ENABLE
	NVIC_ISER1 |=(0x1<<8);
	while (1)
	{
		if (flag==1)
		{
			GPIOB_ODR ^= (1 << 12);
				GPIOB_ODR &= ~(1 << 13);

				counter++;
						GPIOB_ODR &=~ (0 << 12);
			
			flag=0;
		}
	}
}
		//	EXTI INTERRUPT HANDLER
void EXTI15_10_IRQHandler(void)
{
		if  (EXTI_PR & (1 << 10))
		{ 
			flag=1;
				

		EXTI_PR |=(1<<10);
    }
}
