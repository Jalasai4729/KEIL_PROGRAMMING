/****************************************************
* FILE : GPIO.h
* DESCRIPTION :This file contain function declaration related to GPIO initialization
								and configuration
****************************************************/

/*********** Ports RCC CLOCK **********/
#define GPIOA  0
#define GPIOB	 1
#define GPIOC	 2

/*********** Moders **********/
#define IN 		 0    //00
#define OUT  	 1    //01
#define ALT    2    //10
#define ANALOG 3    //11


/***********OUT-Pins**********/

#define RED_LED   13
#define GREEN_LED 14
#define BUZZER    12

/***********IN-Pins**********/

#define SW_UP  8
#define SW_DN  9
#define SW_ENT 10





void  KM_GPIO_PORT_INIT(int port);//ENABLE CLOCK
void  KM_GPIO_PORT_CONFIG(int port, int pin, int mode);//MODE REGESTER SET
void  KM_GPIO_WRITE_PIN(int port, int pin, int data);//
void  KM_GPIO_TOGGLE(int port, int pin);//TOGGLE THE LEDs
int   KM_GPIO_READ_PIN(int port, int pin);

