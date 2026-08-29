#define RCC_AHB1ENR   (*(volatile unsigned int*)0x40023830)
#define GPIOB_MODE    (*(volatile unsigned int*)0x40020400)
#define GPIOB_ODR     (*(volatile unsigned int*)0x40020414)

#define STK_CTRL      (*(volatile unsigned int*)0xE000E010)
#define STK_LOAD      (*(volatile unsigned int*)0xE000E014)
#define STK_VAL       (*(volatile unsigned int*)0xE000E018)

/* Function declarations */
void KM_uDelay(int us);
void KM_mDelay(int ms);

int main(void)
{
    /* ---------------- PHASE A : INITIALIZATION ---------------- */

    /* Enable GPIOB clock */
    RCC_AHB1ENR |= (1 << 1);

    /* Configure PB13 as output */
    GPIOB_MODE &= ~(0x3 << 26);
    GPIOB_MODE |=  (0x1 << 26);

    //Turn LED OFF initially (active-low) 
	
              GPIOB_ODR |= (1 << 13);

             //SysTick configuration (Polling, Processor clock)
              STK_CTRL = 0;              // Reset SysTick
              STK_CTRL = (1 << 2);       // CLKSOURCE = CPU clock, interrupt disabled

    //OPERATION PHASE 
    while (1)
    {
        GPIOB_ODR ^= (1 << 13);   // Toggle LED
        KM_mDelay(10);  			// 1 second delay
			  GPIOB_ODR ^= (1 << 13);   // Toggle LED
         KM_uDelay(1);  			// 1 second delay
 
    }
}

/* ---------------- MICROSECOND DELAY ---------------- */
void KM_uDelay(int us)
{
        STK_LOAD = 16 *us;        // 1 us delay 16 MHz
        STK_VAL  = 0;             // Clear current value
       // STK_CTRL |= (1 << 0);     // Enable SysTick

        while (!(STK_CTRL & (1 << 16)));  // Poll COUNTFLAG
}

//MILLISECOND DELAY 
void KM_mDelay(int ms)
{
   
			  STK_LOAD = 16000 *ms;        // 1 us delay 16 MHz
        STK_VAL  = 0;             // Clear current value
        STK_CTRL |= (1 << 0);     // Enable SysTick

           while(!(STK_CTRL & (0x1<<16)));  // Poll COUNTFLAG
      
}
