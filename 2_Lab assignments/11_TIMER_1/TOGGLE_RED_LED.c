// RCC AHB1 ENABLE REGISTER
#define RCC_AHB1ENR   (*(volatile int*)0x40023830)

// RCC APB2 ENABLE REGISTER
#define RCC_APB2ENR   (*(volatile int*)0x40023844)

// GPIOB MODE REGISTER
#define GPIOB_MODE    (*(volatile int*)0x40020400)

// GPIOB OUTPUT DATA REGISTER
#define GPIOB_ODR     (*(volatile int*)0x40020414)

// TIM1 CONTROL REGISTER
#define TIM1_CR1      (*(volatile int*)0x40010000)

// TIM1 STATUS REGISTER
#define TIM1_SR       (*(volatile int*)0x40010010)

// TIM1 COUNTER REGISTER
#define TIM1_CNT      (*(volatile int*)0x40010024)

// TIM1 PRESCALER REGISTER
#define TIM1_PSC      (*(volatile int*)0x40010028)

// TIM1 AUTO-RELOAD REGISTER
#define TIM1_ARR      (*(volatile int*)0x4001002C)


// FUNCTION DECLARATIONS
void GPIO_Init(void);
void TIM1_Init(void);
void delay_1sec(void);


// MAIN FUNCTION
int main()
{
    // INITIALIZE GPIO
    GPIO_Init();

    // INITIALIZE TIMER1
    TIM1_Init();

    // INFINITE LOOP
    while (1)
    {
        // TOGGLE RED LED ON PB13
        GPIOB_ODR ^= (1 << 13);

        // 1 SECOND DELAY
        delay_1sec();
    }
}


// GPIO INITIALIZATION FUNCTION
void GPIO_Init(void)
{
    // ENABLE CLOCK FOR GPIO PORT B
    RCC_AHB1ENR |= (1 << 1);

    // CLEAR PB13 MODE BITS
    GPIOB_MODE &= ~(0x3 << 26);

    // SET PB13 AS OUTPUT MODE
    GPIOB_MODE |= (0x1 << 26);

    // TURN LED OFF INITIALLY
    GPIOB_ODR |= (1 << 13);
}


// TIMER1 INITIALIZATION FUNCTION
void TIM1_Init(void)
{
    // ENABLE CLOCK FOR TIMER1
    RCC_APB2ENR |= (1 << 0);

    // SET PRESCALER VALUE
    // 16MHz / 16000 = 1000Hz
    // TIMER TICK = 1ms
    TIM1_PSC = 15999;

    // SET AUTO-RELOAD VALUE
    // 1000 COUNTS = 1 SECOND
    TIM1_ARR = 999;

    // CLEAR COUNTER VALUE
    TIM1_CNT = 0;
}


// 1 SECOND DELAY FUNCTION
void delay_1sec(void)
{
    // CLEAR COUNTER
    TIM1_CNT = 0;

    // CLEAR UPDATE INTERRUPT FLAG
    TIM1_SR &= ~(1 << 0);

    // START TIMER
    TIM1_CR1 |= (1 << 0);

    // WAIT UNTIL OVERFLOW OCCURS
    while (!(TIM1_SR & (1 << 0)));

    // STOP TIMER
    TIM1_CR1 &= ~(1 << 0);
}
