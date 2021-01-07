
int main()
{
    // enabling clock, setting pin direction
    *((unsigned int *)0x400FE608U) = 0x20U;
    *((unsigned int *)0x40025400U) = 0x0EU;
    *((unsigned int *)0x4002551CU) = 0x0EU;
    
    while(1)
    {
        int counter = 0;

        // led on
        *((unsigned int *)0x400253FCU) = 0x02U;
        // slight delay
        while (counter < 1000000)
        {
            ++counter;
        }        

        counter = 0;

        // off
        *((unsigned int *)0x400253FCU) = 0x00U;
        while (counter < 1000000)
        {
            ++counter;
        }
    }
    
    return 0;
}
