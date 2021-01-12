#include "lm4f120h5qr.h"
#include "delay.h"

#define LED_RED     (1U << 1)
#define LED_BLUE    (1U << 2)
#define LED_GREEN   (1U << 3)

int * swap(int * x, int * y);

int * swap(int * x, int * y)
{
    // not necesarily a proper fix, but demonstrates using static to 
    // keep the variable alive at the beginning of memory through the static keyword
    static int temp[2];
    *x = *y;
    *y = temp;

    return temp;
}

int main()
{        
    /* Simple Pointer / Swap Excercise */
    int x = 1;
    int y = 3;

    // swap!
    swap(&x,&y);


    // enabling clock, setting pin direction, data enable (ONLY WORKS IF THE REGISTERS HAVE R/W PERMISSIONS)
    SYSCTL_RCGCGPIO_R = (1U << 5);                       // set bit 5, was -> SYSCTL_RCGCGPIO_R = 0x20U;
    GPIO_PORTF_DIR_R = (LED_RED | LED_BLUE | LED_GREEN); // pins 1->3 as output, was -> GPIO_PORTF_DIR_R = 0x0EU; 
    GPIO_PORTF_DEN_R = (LED_RED | LED_BLUE | LED_GREEN); // was -> GPIO_PORTF_DEN_R = 0x0EU; 

    
    while(1)
    {
        // You can see in the IAR debug window, that the value of 'x' does not change
        // as it is decremented over in the 'delay' function, demonstrating the call by value
        int x = 1000000;

        /* LEDs red and blue on (both options individually can blink the LED)*/
        // method 1: ASM (LOAD, OR, STORE)
        GPIO_PORTF_DATA_R |= (LED_BLUE | LED_RED); 
        
        // slight delay
        delay(x);

        /* LEDs red and blue off (both options individually can blink the LED)*/
        // method 1: ASM (LOAD, OR, STORE)
        GPIO_PORTF_DATA_R &= ~(LED_BLUE | LED_RED);
 
        // slight delay
        delay(x);
    }
    
    //return 0;
}

