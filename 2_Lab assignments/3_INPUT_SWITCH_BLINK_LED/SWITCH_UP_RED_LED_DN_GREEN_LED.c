#define RCC_AHB1ENR (*(volatile int*)0x40023830)
#define GPIOB_MODE  (*(volatile int*)0x40020400)
#define GPIOB_ODR   (*(volatile int*)0x40020414)
#define GPIOC_IDR   (*(volatile int*)0x40020810)
#define GPIOC_MODE  (*(volatile int*)0x40020800)
#define GPIOC_PUPDR (*(volatile int*)0x4002080C)

void delay(void)
{
	volatile int i;
	for (i = 0; i < 200000; i++);   // debounce delay
}

int main()
{
	RCC_AHB1ENR |= (1 << 1);
	RCC_AHB1ENR |= (1 << 2);

	// PB13 RED, PB14 GREEN output
	GPIOB_MODE &= 0xF3FFFFFF;
	GPIOB_MODE |= 0x04000000;
	GPIOB_MODE &= 0x3FFFFFFF;
	GPIOB_MODE |= 0x10000000;

	// PC8, PC9 input
	GPIOC_MODE &= ~((3 << 16));
	GPIOC_MODE &= ~((3<<18));

	// Pull-up enable
	GPIOC_PUPDR &= ~((3 << 16) | (3 << 18));
	GPIOC_PUPDR |=  ((1 << 16) | (1 << 18));

	// LEDs OFF (active LOW)
	GPIOB_ODR |= (1 << 13);
	GPIOB_ODR |= (1 << 14);

	while (1)
	{
		// SW_UP ? toggle RED LED
		if ((GPIOC_IDR & (1 << 8)) == 0)
		{
		delay(); // debounce
			if ((GPIOC_IDR & (1 << 8)) == 0)
			{
				GPIOB_ODR ^= (1 << 13);  // TOGGLE
			//while ((GPIOC_IDR & (1 << 8)) == 0); // wait release
		  }
		}

		// SW_DN ? toggle GREEN LED
		if ((GPIOC_IDR & (1 << 9)) == 0)
		{
			delay(); // debounce
			if ((GPIOC_IDR & (1 << 9)) == 0)
		//	{
				GPIOB_ODR ^= (1 << 14);  // TOGGLE
				//while ((GPIOC_IDR & (1 << 9)) == 0); // wait release
			//}
		}
	}
}
