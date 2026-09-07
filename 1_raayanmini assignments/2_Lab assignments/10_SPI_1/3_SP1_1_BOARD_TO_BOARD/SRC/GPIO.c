

#include "../inc/stm32f401rbt6.h"
#include "../inc/GPIO.h"
#


/************************************************************************************
*          							gpio_port_init()
************************************************************************************
*DESCRIPTION : This functions initialize the GPIO'S ports 
*ARGUMENTS : int port  (GPIOA,GPIOB,GPIOC)
*RETURN TYPE : void (no return type) 
*NOTES : Enable Clock to GPIOA,GPIOB,GPIOC
********************************************************/
void KM_GPIO_PORT_INIT(int port)
{
	switch(port)
	{
		case GPIOA :
			RCC_AHB1ENR |= (0X01<<0);  //set 0th pin in
		  break;
		case GPIOB :
			RCC_AHB1ENR |= (0X01<<1);
			break;
		case GPIOC :
			RCC_AHB1ENR |= (0X01<<2);
			break;			
	}
}
/****************************************************************************************
*          						gpio_port_confir()
*****************************************************************************************
*DESCRIPTION : This Function configure GPIO ports
*ARGUMENTS   :int port  (GPIOA,GPIOB,GPIOC)
*						 :int mode  (IN,OUT,ANALOG,ALT)
*						 :int pin 
*RETURN TYPE :void (no return type)
*NOTES : Configures GPIO'S pin to OUTPUT/INPUT/ALTERNATE/ANALOG
********************************************************/

void  KM_GPIO_PORT_CONFIG(int port, int mode, int pin)//MODE REGESTER SET
	
{
	
	switch(port)
      	{
	    case GPIOA ://START
		    {
		    switch (mode)
			          {
			   	       case IN :
				             	break;
				         case OUT :
				            	break;
								 case ANALOG :
									              break;
								 case ALT : GPIOB_MODER |= (0X02 << (pin *2));//10

									          break;
		       	     }
			           break;
		     }//END
							 
				case GPIOB :
				 {
				 switch (mode)//START
					       {
					       case IN :
										      	break;
					       case OUT :
			
										        GPIOB_MODER |= (0X01 << (pin *2));
								 case ANALOG :
									              break;
							    }
									break;
				 }//END
						 
				case GPIOC :
				{
			  switch (mode)
			         {
				       case IN : GPIOC_MODER |= (0X1 << (pin *2));//01

				                	  break;
				       case OUT :
					                 break;
							 case ANALOG : 
                 							 GPIOC_MODER |= (0X3 << (pin *2));//10
							               break;

			          }
			          break;
		      }
		
				}
}
void  KM_GPIO_WRITE_PIN(int port, int pin, int data)//
{
	switch(port)
	{
		case GPIOB :
	          	case RED_LED : if(data)
			                         {
									              GPIOB_ODR |=(0x1<<13);
							                  	 }
								                  else
								                   {
									              GPIOB_ODR &=~(0x1<<13);
								                     }
		case GREEN_LED : if(data)
			           {
									 GPIOB_ODR |=(0x1<<13);
								 }
								 else
								 {
									 GPIOB_ODR &=~(0x1<<13);
								 }
		}
}
void  KM_GPIO_TOGGLE(int port, int pin)//TOGGLE THE LEDs
{
		GPIOB_ODR ^=(0x1<<13);
	       //  KM_mdelay_IT(100);
		GPIOB_ODR ^=(0x1<<14);


}
