/****************************************************
*   FILE : km_lcd.h
* DESCRIPTION :This file contain function declaration related to 16*2 monochrome LCD initialization
								and configuration
****************************************************/


void KM_Lcd_Pin_Init(int port, int , int , int , int, int, int, int);  //initializing Port B pins associated to LCD
//Example: KM_Lcd_Pin_Init(LCD_PORT, LCD_D4, LCD_D5, LCD_D6, LCD_D7, LCD_RS, LCD_RW, LCD_EN);
void KM_LCD_INIT(void);  //Flow chart
void KM_LCD_WRITE_DATA(unsigned char );
void KM_LCD_WRITE_CMD(unsigned char );
void KM_WRITE_LOWER_NIBBLE(unsigned char );
void KM_WRITE_HIGHER_NIBBLE(unsigned char  );
void KM_LCD_WRITE_STR( char str[]);

void KM_ITOA_STR(int);
void KM_PIN_LCD_INIT(void);  //Flow chart
 
//Add the below MACROS for portability.
#define LCD_D4 0
#define LCD_D5 1
#define LCD_D6 2
#define LCD_D7 3
#define LCD_RS 4
#define LCD_RW 5 
#define LCD_EN 8
