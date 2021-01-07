#define RCC_GPIO    (*((unsigned int *)0x400FE608U))
#define GPIOF_BASE  0x40025000U
#define GPIOF_DIRECTION (*((unsigned int *)(GPIOF_BASE + 400U)))
#define GPIOF_DEN   (*((unsigned int *)(GPIOF_BASE + 0x51CU)))
#define GPIOF_DATA  (*((unsigned int *)(GPIOF_BASE + 0x3FCU)))

int main()
{
    // enabling clock, setting pin direction, data enable
    RCC_GPIO = 0x20U;
    GPIOF_DIRECTION = 0x0EU;
    GPIOF_DEN = 0x0EU;
    
    while(1)
    {
        int counter = 0;

        // led on
        GPIOF_DATA = 0x02U;
        // slight delay
        while (counter < 1000000)
        {
            ++counter;
        }        

        counter = 0;

        // off
        GPIOF_DATA = 0x00U;
        while (counter < 1000000)
        {
            ++counter;
        }
    }
    
    return 0;
}
