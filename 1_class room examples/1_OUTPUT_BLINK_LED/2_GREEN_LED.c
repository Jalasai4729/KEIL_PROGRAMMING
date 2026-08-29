
#define RCC_AHB1ENR *(int*)0x40023830
#define GPIOB_MODE *(int*)0x40020400
#define GPIOB_ODR *(int*)0x40020414
void delay(int t);	//dalay declaration
int main()
{
	RCC_AHB1ENR |=(0x1<<1); //set rcc clock to gpio port
	GPIOB_MODE &=~(0x3fffffff);//clear mode 29 28 bits
	GPIOB_MODE |=(0x10000000);//ser 01 on mode 29 28 positions
	GPIOB_ODR |=(0x1<<14);//set 1 output device 
	while(1)
	{
		GPIOB_ODR &= ~(0x1<<14);// set 13th positions with 0 red led on
		delay(100);//calling functions
		GPIOB_ODR |=(0x1<<14);//set 1 red led off
		delay(100);
	}
}
void delay(int t)//defination
{
	int i;
	for(i=0;i<=1600*t;i++)
	{
		;
	}
}