#define RCC_AHB1ENR (*(volatile int*)0x40023830)
#define GPIOB_MODE  (*(volatile int*)0x40020400)
#define GPIOB_ODR   (*(volatile int*)0x40020414)
#define GPIOC_IDR   (*(volatile int*)0x40020810)
#define GPIOC_PUPDR (*(volatile int*)0x4002080C)

void delay(int t)
{
	volatile int i;
	for (i = 0; i <1600*t; i++);   // debounce delay
}
int counter=0;
int main()
{
	//phase a initialization
	RCC_AHB1ENR |= (1 << 1);//SET CLOCK port B
	RCC_AHB1ENR |= (1 << 2);//SET CLOCK port C

	// PB13 RED
	GPIOB_MODE &= ~(0x3<<26);//CLAER 27,26 positions 
	GPIOB_MODE |= (0x1<<26);//set 0 1 on 27,26 positions


	// Pull-up enable
	GPIOC_PUPDR &= ~(3 << 20);
	GPIOC_PUPDR |=  (1 << 20);

	// RED LED OFF (active LOW)
	GPIOB_ODR |= (1 << 13);

	while (1)
	{
		// SW_UP RED LED ON
		if  (!(GPIOC_IDR & (1 << 10)))
		{
				GPIOB_ODR ^=(1 << 13);
				counter++;
		
		delay(250); // debounce
    }
}
}