void delay(int volatile cycles)
{
    while(cycles > 0)
    {
        --cycles;
    }

}