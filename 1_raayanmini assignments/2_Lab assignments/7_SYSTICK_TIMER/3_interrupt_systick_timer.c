#define RCC_AHB1ENR   (*(volatile unsigned int*)0x40023830)
#define GPIOB_MODE    (*(volatile unsigned int*)0x40020400)
#define GPIOB_ODR     (*(volatile unsigned int*)0x40020414)

#define STK_CTRL      (*(volatile unsigned int*)0xE000E010)
#define STK_LOAD      (*(volatile unsigned int*)0xE000E014)
#define STK_VAL       (*(volatile unsigned int*)0xE000E018)

// Global timer variable
volatile unsigned int jiffie = 0;

// Function declarations
 void systick_init();

void KM_mdelay_IT(int ms);
void KM_udelay_IT(int us);

//MAIN FUNCTION
int main(void)
{
    /* Enable GPIOB clock */
    RCC_AHB1ENR |= (1 << 1);

    //Configure PB13 as output 
    GPIOB_MODE &= ~(0x3 << 26);
    GPIOB_MODE |=  (0x1 << 26);

    // LED OFF initially (active-low) 
    GPIOB_ODR |= (1 << 13);

    //SysTick Configuration 
    systick_init();
    while (1)
    {
            GPIOB_ODR ^= (1 << 13);    // Toggle RED LED
						KM_mdelay_IT(250);
			                // 	GPIOB_ODR ^= (1 << 13);    // Toggle RED LED
				        	   //		KM_udelay_IT(1);
		}
 }

 void systick_init()
 { 
	 		  //STK_CTRL =0;
			STK_CTRL |=(0x7<<0);
	    STK_LOAD = 16000 - 1; 
      STK_VAL  = 0;	// Clear current value
	 		  

 }

//SysTick Interrupt Handler 
void SysTick_Handler(void)
{
    jiffie++;                          // Increment every 1 ms
}

// MILLISECOND DELAY 
void KM_mdelay_IT(int ms)
{
		int count =0;    	// Reset SysTick
	   count=jiffie+ms;

    while (jiffie < count);
	//  	STK_CTRL &= (~(0x1));
}

