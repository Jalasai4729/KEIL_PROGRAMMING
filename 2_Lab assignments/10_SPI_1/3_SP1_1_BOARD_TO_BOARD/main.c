/* QUESTION :
 * USART2
 * Microcontroller : STM32F401RBT6
 * RaayanMini      : 
 * Author : JALA SAI
 * Date : 18-02-2026
 * STLink Debugger : 
 * Hardware        : USART2 BOARD TO BOARD COMMUNICATION
 *
 *			PA2--->USART2 -PA2
 *			PA3--->USART2 -PA3
 */
 #include "../inc/stm32f401rbt6.h"
 #include "../inc/GPIO.h"
 #include "../inc/systicktimer.h"
 #include "../inc/SPI_1.h"
 #include "../inc/SYSCFG.h"
 #include "../inc/lcd.h"
 
 unsigned char str1[]="BOARD TO BOARD";
unsigned char str2[]="COMMUNICATION";
unsigned int Temp=0;
unsigned char ch=0;
unsigned char r='R';
unsigned char g='G';

int flag=0;
//extern int temp;
//extern char arr[16];
//extern int lm35;

int main()
{
 /********* Phase 1: Device Initialization *******************/
	 
   KM_GPIO_PORT_INIT(GPIOB);
	 KM_GPIO_PORT_INIT(GPIOC);


/********* Phase 2: Device configuration *********************/
	
  //SYSTICK  FUNCTION
	
	 //GPIOB_MODER REGISTERS
	 GPIOB_MODER &=(~(0x3f000000));//CLEAR 24-29 POSITIONS PB12-13-14
	 GPIOB_MODER |=(0x15000000);//SRT 01 ON 24-29 POSITIONS PB 12-13-14
	
  //GPIOB_ RED GREEN LED BOUZZER OFF
	GPIOB_ODR |=(0x3<<13);

               KM_STK_INIT();
	
	
	         KM_PIN_LCD_INIT();  //Flow chart
           KM_LCD_INIT();  //Flow chart
           KM_LCD_WRITE_CMD(0x80);
           KM_LCD_WRITE_STR(str1);
	         KM_LCD_WRITE_CMD(0xC0);
           KM_LCD_WRITE_STR(str2);

	         KM_SYSCFG_CONFIG();


 //SPI_1 CONFIGURE
	    
	
	           SPI1_MUX_INIT();
           	SPI1_CONFIG();
						
/************* OPERATION PHASE ************************************/
	

  while(1)
  {
        if(flag==1)
		     {
		       // SPI1_DR=r;
					 SPI1_OUTCHAR(r);
					 flag=0;
	       	}
		
	      	else if(flag==2)
		      {
           SPI1_DR=g;
						flag=0;
	       	}
		
	     	else if( (ch=='R') || (ch=='r') )
			   {
            GPIOB_ODR &=~(0x1<<13);//RED LED ON
					 KM_mdelay_IT(200);
					GPIOB_ODR |=(0x1<<13);//RED LED OFF

			    }
			
			   else if( (ch=='G') || (ch=='g') )
			    {
				
				   GPIOB_ODR &=~(0x1<<14);//GREEN LED ON
						KM_mdelay_IT(200);
					 GPIOB_ODR |=(0x1<<14);//GREEN LED OFF
	
			    }

		}			
}
	
/******** SPI_1 HANDLEDR ************************************************************************************/
void SPI1_IRQHandler()
{
   // RX interrupt
         ch = SPI1_DR;        // read received data

}

/************** HANDLER MODE ON PB 8-9 ***************************************************/

void EXTI9_5_IRQHandler(void)
{
	   if(EXTI_PR & (0x1 << 8))
	   {
		  flag=1;
		  EXTI_PR |=(0x1 << 8);//CLEAR PR PENDING STATUS REGESTER
	    }
	   else if(EXTI_PR &(0x1 << 9))
	   {
		  flag=2;
		  EXTI_PR |=(0x1 << 9);//CLEAR PR PENDING STATUS REGESTER
	   }
}

/**************************************************************************************************/

