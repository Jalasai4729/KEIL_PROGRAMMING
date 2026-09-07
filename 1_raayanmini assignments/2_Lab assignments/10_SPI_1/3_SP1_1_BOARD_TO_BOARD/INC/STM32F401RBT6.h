/****************************************************
* FILE : stm32f401rbt6.h
* DESCRIPTION :This file contain all BASE ADDRESSES and  PHYSICAL ADDRESSES of STM32 peripherals and MACROS used

****************************************************/

 /***********************************************BASE ADDRESSES OF STM32**********************************/
 
 //RCC
 
#define RCC_BASEADDR 0X40023800

//GPIO

#define GPIOA_BASEADDR 0x40020000
#define GPIOB_BASEADDR 0x40020400
#define GPIOC_BASEADDR 0x40020800
//SYSCFG

#define SYSCFG_BASEADDR 0x40013800

//EXTI

#define EXTI_BASEADDR 0x40013C00

//ADC1

//ADC1.......ANALOG TO DIGITAL CONVERTER
#define ADC1_BASEADDR 0x40012000


//USART2
#define USART2_BASEADDR 0x40004400


//USART6
#define USART6_BASEADDR 0x40011400


//SPI_1
#define USART2_BASEADDR 0x40013000






/*******************************************************/

 /***********************************************BASE ADDRESSES OF ARM CORTEX M4**********************************/

//NVIC
#define NVIC_BASEADDR  0xE000E100
//STK
#define STK_BASEADDR 0XE000E010

/*****************************************************************************************************************
*                              PHYSICAL ADDRESSES OF STM32 
*****************************************************************************************************************/

//RCC

#define  RCC_AHB1ENR  *((int *)(RCC_BASEADDR + 0x30))
#define  RCC_AHB2ENR  *((int *)(RCC_BASEADDR + 0x34))
#define  RCC_APB1ENR  *((int *)(RCC_BASEADDR + 0x40))
#define  RCC_APB2ENR  *((int *)(RCC_BASEADDR + 0x44))
/*************************************************************************************************************/

//GPIOA
#define GPIOA_MODER     *((int *)(GPIOA_BASEADDR + 0x00))
#define GPIOA_ODR 			*((int *)(GPIOA_BASEADDR + 0x14))
#define GPIOA_PUPDR     *((int *)(GPIOA_BASEADDR + 0x0C))
#define GPIOA_IDR       *((int *)(GPIOA_BASEADDR + 0x10))
#define GPIOA_AFRL      *(volatile unsigned int*)(GPIOA_BASEADDR+0X20)


//GPIOB
#define GPIOB_MODER    *((int *)(GPIOB_BASEADDR + 0x00))
#define GPIOB_ODR      *((int *)(GPIOB_BASEADDR + 0x14))
#define GPIOB_PUPDR    *((int *)(GPIOB_BASEADDR + 0x0C))
#define GPIOB_IDR      *((int *)(GPIOB_BASEADDR + 0x10))

//GPIOC
#define GPIOC_MODER    *((int *)(GPIOC_BASEADDR + 0x00))
#define GPIOC_ODR      *((int *)(GPIOC_BASEADDR + 0x14))
#define GPIOC_PUPDR    *((int *)(GPIOC_BASEADDR + 0x0C))
#define GPIOC_IDR      *((int *)(GPIOC_BASEADDR + 0x10))

/***********************************************************************************************************/

//STSCFG
#define SYSCFG_EXTICR1 *((int *)(SYSCFG_BASEADDR + 0x08))
#define SYSCFG_EXTICR2 *((int *)(SYSCFG_BASEADDR + 0x0C))
#define SYSCFG_EXTICR3 *((int *)(SYSCFG_BASEADDR + 0x10))
#define SYSCFG_EXTICR4 *((int *)(SYSCFG_BASEADDR + 0x14))


/************************************************************************************************/

//EXTI
#define EXTI_IMR *((int *)(EXTI_BASEADDR + 0x00))
#define EXTI_FTSR *((int *)(EXTI_BASEADDR + 0x0C))
#define EXTI_PR *((int *)(EXTI_BASEADDR + 0x14))
	
/************************************************************************************************/
	
//ADC1

#define ADC1_SR      *(volatile unsigned int*)(ADC1_BASEADDR+0X00)
#define ADC1_CR1     *(volatile unsigned int*)(ADC1_BASEADDR+0X04)
#define ADC1_CR2     *(volatile unsigned int*)(ADC1_BASEADDR+0X08)
#define ADC1_SQR1    *(volatile unsigned int*)(ADC1_BASEADDR+0X2C)
#define ADC1_SQR2    *(volatile unsigned int*)(ADC1_BASEADDR+0x30)
#define ADC1_SQR3    *(volatile unsigned int*)(ADC1_BASEADDR+0x34)
#define ADC1_DR      *(volatile unsigned int*)(ADC1_BASEADDR+0x4C)
#define ADC1_HTR     *(volatile unsigned int*)(ADC1_BASEADDR+0x24)
#define ADC1_LTR     *(volatile unsigned int*)(ADC1_BASEADDR+0x28)


/******************************************************************************************************/

//USART2

#define USART2_SR    *(volatile unsigned int*)(USART2_BASEADDR+0X00)
#define USART2_DR    *(volatile unsigned int*)(USART2_BASEADDR+0X04)
#define USART2_BRR   *(volatile unsigned int*)(USART2_BASEADDR+0X08)
#define USART2_CR1   *(volatile unsigned int*)(USART2_BASEADDR+0X0C)
#define USART2_CR2   *(volatile unsigned int*)(USART2_BASEADDR+0X10)
#define USART2_CR3   *(volatile unsigned int*)(USART2_BASEADDR+0X14)
	
		
//USART6

#define USART6_SR    *(volatile unsigned int*)(USART6_BASEADDR+0X00)
#define USART6_DR    *(volatile unsigned int*)(USART6_BASEADDR+0X04)
#define USART6_BRR   *(volatile unsigned int*)(USART6_BASEADDR+0X08)
#define USART6_CR1   *(volatile unsigned int*)(USART6_BASEADDR+0X0C)
#define USART6_CR2   *(volatile unsigned int*)(USART6_BASEADDR+0X10)
#define USART6_CR3   *(volatile unsigned int*)(USART6_BASEADDR+0X14)

	
//SPI_1
		
	
#define SPI1_CR1      (*(volatile int*)0x40013000)  
#define SPI1_CR2      (*(volatile int*)0x40013004)  
#define SPI1_SR       (*(volatile int*)0x40013008)  
#define SPI1_DR       (*(volatile int*)0x4001300C)   


/*****************************************************************************************************************
*                              PHYSICAL ADDRESSES OF ARM CORTEX M4 
*****************************************************************************************************************/

//NVIC
#define NVIC_ISER0 *((int *)(NVIC_BASEADDR + 0x00))
#define NVIC_ISER1 *((int *)(NVIC_BASEADDR + 0x04))

/*********************************************************************************************/

//STK
#define STK_CTRL 		*((int *)(STK_BASEADDR + 0X00))
#define STK_LOAD 		*((int *)(STK_BASEADDR + 0X04))
#define STK_VAL		  *((int *)(STK_BASEADDR + 0X08))


/*************************************************************************************************/





