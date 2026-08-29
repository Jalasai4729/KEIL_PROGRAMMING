#define RCC_AHB1ENR  (*(volatile unsigned int*)0x40023830)
#define RCC_APB2ENR  (*(volatile unsigned int*)0x40023844)

#define GPIOC_MODER  (*(volatile unsigned int*)0x40020800)
#define GPIOB_MODER  (*(volatile unsigned int*)0x40020400)
#define GPIOB_ODR    (*(volatile unsigned int*)0x40020414)
	
#define ADC1_SR      (*(volatile unsigned int*)0x40012000)
#define ADC1_CR1     (*(volatile unsigned int*)0x40012004)
#define ADC1_CR2     (*(volatile unsigned int*)0x40012008)
#define ADC1_SQR1    (*(volatile unsigned int*)0x4001202C)
#define ADC1_SQR2    (*(volatile unsigned int*)0x40012030)
#define ADC1_SQR3    (*(volatile unsigned int*)0x40012034)
#define ADC1_DR      (*(volatile unsigned int*)0x4001204C)
#define ADC1_HTR     (*(volatile unsigned int*)0x40012024)
#define ADC1_LTR     (*(volatile unsigned int*)0x40012028)
#define HTR   3000 //Higest Threshold Value
#define LTR		2000 //Lowest Threshold Value
#define NVIC_ISER0   (*(volatile unsigned int*)0xE000E100)

volatile unsigned int pot = 0;
volatile unsigned int Count = 0;
volatile unsigned int WatchDog = 0;

/******************** Delay Function ********************/
void Delay (int t)
{
    int i;
    for(i = 0; i < (1600 * t); i++);
}
/*********************************************************/

int main()
{
    /*************** Initialization Phase ****************/
    
    RCC_AHB1ENR |= (1 << 2);      // Enable GPIOC clock
    RCC_APB2ENR |= (1 << 8);      // Enable ADC1 clock
    RCC_AHB1ENR |= (1 << 1);      // Enable GPIOB clock

    /*************** Configuration Phase ****************/
    
	   GPIOB_MODER &= ~(3 << 26);    
     GPIOB_MODER |=  (0X1 << 26);  // PB13 OUTPUT
     GPIOB_ODR |= (0X1 << 13);    //RED_LED OFF
	
	
    // Set PC1 to Analog mode
    GPIOC_MODER &= ~(3 << 2);
    GPIOC_MODER |=  (3 << 2);     // PC1 Analog
	
   
	    ADC1_SQR3 |= (0xb);   // 1st conversion Channel 11 (PC1)
	
	

    // Scan mode enable
  //  ADC1_CR1 |= (1 << 8);

    // EOCIE interrupt enable
    ADC1_CR1 |= (1 << 5);

    // EOCs after each conversion
 //   ADC1_CR2 |= (1 << 10);

    // Clear SQR3 and configure channels
    
		
    ADC1_CR1 |= (0xb);//		//Load the AWDCH Value watchdog channel

		
		//Set the AWDIE bit
		ADC1_CR1 |= (1 << 6);
		
		ADC1_CR1 |= (1 << 9);		//Set the AWDSGL single set 1 multiple 0

		
		// Load the HTR 
		ADC1_HTR &= ~ (0XFFF << 0);
		ADC1_HTR = 3000;

		// Load the LTR 
		ADC1_LTR &= ~ (0XFFF << 0);
		ADC1_LTR = 2000;
		
       ADC1_CR1 |= (0x1 << 23);    // SET AWDEN bit REGULAR CHANNEL ENABLE--+AA


    ADC1_CR2 |= (0X1 << 0);    // Enable AD ON


    // Enable ADC interrupt in NVIC
    NVIC_ISER0 |= (0X1 << 18);

    /*************** Operation Phase ****************/
    
    while(1)
    {
			        Delay(500);

        ADC1_CR2 |= (0X1 << 30);   // Start conversion (SWSTART)
    }
}

/******************** ADC Interrupt Handler ********************/
void ADC_IRQHandler(void)
{
    if(ADC1_SR & (0x1 << 1))   // Check EOC flag
    {
            pot = ADC1_DR & (0xFFF);   
		//	ADC1_SR &= ~(0x1 << 1); //Clear the EOC bit
     }
		
		 
			if(ADC1_SR & (1<<0)) // Check AWD flag
			{
				
				GPIOB_ODR ^= (0X1 << 13);				//Toggle the RED_LED
				Delay(100);
				WatchDog = ADC1_DR & (0XFFF);
				//ADC1_SR &= ~(1 << 0); //Clear the AWD bit

			}
			else
			{
						GPIOB_ODR |= (0X1 << 13);
			}
			
}

/**********************Problems Faced*****************/
/*
1. Forgot to Enable the  AWDEN  bit in ADC_CR1

*/

