/*
3. Input Switch Polling

Problem Statement:
Whenever SW_UP is pressed, the RED LED should turn ON.

Whenever SW_DN is pressed, the GREEN LED should turn ON.

Assign breakpoints after each if condition and run the program in the debugger window.
Whenever SW1 / SW2 is pressed, the program should stop at the corresponding breakpoint.

Prerequisites:
Students must have knowledge of:

Basics of GPIO configuration (input/output mode) in STM32.

Interfacing switches and LEDs with microcontroller GPIO pins.

Using polling method to detect switch status.

Configuring and using the debugger in STM32CubeIDE / Keil µVision:

Setting breakpoints

Running code in debug mode

Observing program execution halts

Bit manipulation concepts for GPIO registers (MODER, IDR, ODR).

BOARD NO= STM32F401RBT6

*/

#define RCC_AHB1ENR (*(volatile int*)0x40023830)
#define GPIOB_MODE  (*(volatile int*)0x40020400)
#define GPIOB_ODR   (*(volatile int*)0x40020414)
#define GPIOC_IDR   (*(volatile int*)0x40020810)
#define GPIOC_PUPDR (*(volatile int*)0x4002080C)

volatile int counter1=0;
volatile int counter2=0;

void delay(int t)
{
	volatile int i;
	for (i = 0; i < 200000*t; i++);   // debounce delay
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

	// Pull-up enable
	GPIOC_PUPDR &= ~((3 << 16) | (3 << 18));
	GPIOC_PUPDR |=  ((1 << 16) | (1 << 18));

	// LEDs OFF (active LOW)
	GPIOB_ODR |= (1 << 13);
	GPIOB_ODR |= (1 << 14);

	while (1)
	{
		// SW_UP ? toggle RED LED
		if (!(GPIOC_IDR & (1 << 8)))
		{
				GPIOB_ODR &= ~(1 << 13);
			counter1++;
		}

		delay(100); // debounce

		// SW_DN ? toggle GREEN LED
		if (!(GPIOC_IDR & (1 << 9)))
		{
				GPIOB_ODR &= ~(1 << 14);
			  counter2++;
		}
				delay(100); // debounce

	}
	
}
