// RCC AHB1 ENABLE REGISTER
#define RCC_AHB1ENR      (*(volatile int*)0x40023830)

// RCC APB2 ENABLE REGISTER
#define RCC_APB2ENR      (*(volatile int*)0x40023844)

// GPIOB MODE REGISTER
#define GPIOB_MODE       (*(volatile int*)0x40020400)

// GPIOB OUTPUT DATA REGISTER
#define GPIOB_ODR        (*(volatile int*)0x40020414)


// ---------------- TIM1 REGISTERS ----------------

// TIM1 CONTROL REGISTER
#define TIM1_CR1         (*(volatile int*)0x40010000)

// TIM1 DMA/INTERRUPT ENABLE REGISTER
#define TIM1_DIER        (*(volatile int*)0x4001000C)

// TIM1 STATUS REGISTER
#define TIM1_SR          (*(volatile int*)0x40010010)

// TIM1 COUNTER REGISTER
#define TIM1_CNT         (*(volatile int*)0x40010024)

// TIM1 PRESCALER REGISTER
#define TIM1_PSC         (*(volatile int*)0x40010028)

// TIM1 AUTO-RELOAD REGISTER
#define TIM1_ARR         (*(volatile int*)0x4001002C)


// ---------------- NVIC REGISTER ----------------

// NVIC INTERRUPT SET ENABLE REGISTER
#define NVIC_ISER0       (*(volatile int*)0xE000E100)


// GLOBAL FLAG VARIABLE
volatile int timer_flag = 0;


// FUNCTION DECLARATIONS
void GPIO_Init(void);
void TIM1_Init(void);


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
        // CHECK TIMER FLAG
        if (timer_flag == 1)
        {
            // CLEAR FLAG
            timer_flag = 0;

            // TOGGLE RED LED
            GPIOB_ODR ^= (1 << 13);
        }
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

    // CLEAR COUNTER
    TIM1_CNT = 0;

    // ENABLE UPDATE INTERRUPT
    TIM1_DIER |= (1 << 0);

    // ENABLE TIM1 INTERRUPT IN NVIC
    NVIC_ISER0 |= (1 << 25);

    // START TIMER
    TIM1_CR1 |= (1 << 0);
}


// TIMER1 INTERRUPT HANDLER
void TIM1_UP_TIM10_IRQHandler(void)
{
    // CHECK UPDATE INTERRUPT FLAG
    if (TIM1_SR & (1 << 0))
    {
        // CLEAR UPDATE FLAG
        TIM1_SR &= ~(1 << 0);

        // SET SOFTWARE FLAG
        timer_flag = 1;
    }
}
