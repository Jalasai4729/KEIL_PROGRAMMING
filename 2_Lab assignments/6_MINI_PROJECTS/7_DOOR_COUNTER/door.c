// RCC CLOCK ENABLE
#define RCC_AHB1ENR (*(volatile int*)0x40023830)
#define RCC_APB2ENR (*(volatile int*)0x40023844)

// GPIO
#define GPIOB_MODE  (*(volatile int*)0x40020400)
#define GPIOB_ODR   (*(volatile int*)0x40020414)
#define GPIOC_PUPDR (*(volatile int*)0x4002080C)

// SYSCFG + EXTI
#define SYSCFG_EXTICR3 (*(volatile int*)0x40013810)
#define EXTI_FTSR (*(volatile int*)0x40013C0C)
#define EXTI_IMR  (*(volatile int*)0x40013C00)
#define EXTI_PR   (*(volatile int*)0x40013C14)

// NVIC
#define NVIC_ISER0 (*(volatile int*)0xE000E100)

// LCD prototypes
void km_Lcd_init(void);
void km_write_cmd(unsigned char data);
void km_write_data(unsigned char data);
void km_higher_nibble(unsigned char data);
void km_lower_nibble(unsigned char data);
void km_write_string(unsigned char str[]);

// LCD strings
unsigned char s1[]="DOOR ENTRY EXIT";
unsigned char s2[]="ENTRY";
unsigned char s3[]="NOT FULL";
unsigned char s4[]="EXIT";
unsigned char s5[]="OVERFLOW";
unsigned char s6[]="THANK YOU";

int limit=5;
int count=0;
int flaag=0;

void delay(int t)
{
	int i;
	for(i=0;i<1600*t;i++);
}

int main()
{
	// CLOCKS
	RCC_AHB1ENR |= (1<<1)|(1<<2);
	RCC_APB2ENR |= (1<<14);

	// LED & BUZZER
	GPIOB_MODE |= (1<<24)|(1<<26)|(1<<28);

	// LCD PINS PB0–PB4, PB8 OUTPUT
	GPIOB_MODE &=~(0x000003FF);
	GPIOB_MODE |= (0x00000555);

	// SWITCH PULLUPS
	GPIOC_PUPDR &=~(0x3F<<16);
	GPIOC_PUPDR |= (0x15<<16);

	// LEDs OFF, BUZZER OFF
	GPIOB_ODR |= (3<<13);
	GPIOB_ODR &=~(1<<12);

	// SYSCFG EXTI PC8, PC9
	SYSCFG_EXTICR3 &=~(0xFF);
	SYSCFG_EXTICR3 |= (0x22);

	// FALLING EDGE PC8, PC9
	EXTI_FTSR |= (1<<8)|(1<<9);
	EXTI_IMR  |= (1<<8)|(1<<9);

	// NVIC
	NVIC_ISER0 |= (1<<23);

	// LCD INIT
	km_Lcd_init();
	km_write_cmd(0x80);
	km_write_string(s1);

	while(1)
	{
		if(flaag==1)        // ENTRY
		{
			km_write_cmd(0xC0);
			km_write_string(s2);

			GPIOB_ODR &=~(1<<14);
			delay(100);
			count++;
			GPIOB_ODR |=(1<<14);

			GPIOB_ODR |= (1<<13);
			GPIOB_ODR &=~(1<<12);

			km_write_cmd(0xC0);
			km_write_string(s3);

			flaag=0;
		}

		else if(flaag==2)   // EXIT
		{
			if(count>=limit)
			{
				km_write_cmd(0xC0);
				km_write_string(s4);

				GPIOB_ODR &=~(1<<13);
				GPIOB_ODR |=(1<<14);
				count--;

				km_write_cmd(0xC0);
				km_write_string(s5);
			}
			else if(count>0)
			{
				km_write_cmd(0xC0);
				km_write_string(s6);

				GPIOB_ODR |=(1<<13)|(1<<14);
			}
			flaag=0;
		}
	}
}

// EXTI HANDLER
void EXTI9_5_IRQHandler(void)
{
	if(EXTI_PR & (1<<8))
	{
		flaag=1;
		EXTI_PR |= (1<<8);
	}
	if(EXTI_PR & (1<<9))
	{
		flaag=2;
		EXTI_PR |= (1<<9);
	}
}

// LCD FUNCTIONS
void km_Lcd_init(void)
{
	delay(40);
	km_write_cmd(0x33);
	km_write_cmd(0x32);
	km_write_cmd(0x28);
	km_write_cmd(0x0C);
	km_write_cmd(0x06);
	km_write_cmd(0x01);
	delay(2);
}

void km_write_cmd(unsigned char data)
{
	GPIOB_ODR &=~(1<<4);
	km_higher_nibble(data);
	km_lower_nibble(data);
}

void km_write_data(unsigned char data)
{
	GPIOB_ODR |=(1<<4);
	km_higher_nibble(data);
	km_lower_nibble(data);
}

void km_higher_nibble(unsigned char data)
{
	data=(data>>4)&0x0F;
	GPIOB_ODR &=~0x0F;
	GPIOB_ODR |=data;
	GPIOB_ODR |=(1<<8);
	delay(1);
	GPIOB_ODR &=~(1<<8);
}

void km_lower_nibble(unsigned char data)
{
	data=data&0x0F;
	GPIOB_ODR &=~0x0F;
	GPIOB_ODR |=data;
	GPIOB_ODR |=(1<<8);
	delay(1);
	GPIOB_ODR &=~(1<<8);
}

void km_write_string(unsigned char str[])
{
	while(*str)
		km_write_data(*str++);
}
