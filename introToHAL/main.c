/* In the end this will be configured using the Advanced Peripheral Bus (APB), at the bottom of this page 
    it is demonstrated how to use the Advanced high speed peripheral bus (AHB) instead, and what would need changed */
#include "lm4f120h5qr.h"

#define LED_RED     (1U << 1)
#define LED_BLUE    (1U << 2)
#define LED_GREEN   (1U << 3)


int main()
{        
    // enabling clock, setting pin direction, data enable (ONLY WORKS IF THE REGISTERS HAVE R/W PERMISSIONS)
    SYSCTL_RCGCGPIO_R = (1U << 5);                       // set bit 5, was -> SYSCTL_RCGCGPIO_R = 0x20U;
    GPIO_PORTF_DIR_R = (LED_RED | LED_BLUE | LED_GREEN); // pins 1->3 as output, was -> GPIO_PORTF_DIR_R = 0x0EU; 
    GPIO_PORTF_DEN_R = (LED_RED | LED_BLUE | LED_GREEN); // was -> GPIO_PORTF_DEN_R = 0x0EU; 

    
    while(1)
    {
        // volatile to avoid the compiler optimizing out the while loops since
        // all they do is delay the system so the led blinking is visable to the human eye
        int volatile counter = 0;

        /* LEDs red and blue on (both options individually can blink the LED)*/
        // method 1: ASM (LOAD, OR, STORE)
        GPIO_PORTF_DATA_R |= (LED_BLUE | LED_RED);
        // method 2: using interrupt safe method : ASM (MOVE, STORE)
        // this uses the pointer GPIO_PORTF_DATA_BITS_R like an array and indexes it to get the desired bits set
        GPIO_PORTF_DATA_BITS_R[LED_BLUE] = LED_BLUE; 
        GPIO_PORTF_DATA_BITS_R[LED_RED] = LED_RED; 
        
        // slight delay
        while (counter < 1000000)
        {
            ++counter;
        }        

        counter = 0;

        /* LEDs red and blue off (both options individually can blink the LED)*/
        // method 1: ASM (LOAD, OR, STORE)
        GPIO_PORTF_DATA_R &= ~(LED_BLUE | LED_RED);
        // method 2: using interrupt safe method : ASM (MOVE, STORE)
        GPIO_PORTF_DATA_BITS_R[LED_BLUE] = 0; 
        GPIO_PORTF_DATA_BITS_R[LED_RED] = 0; 

        // slight delay
        while (counter < 1000000)
        {
            ++counter;
        }
    }
    
    return 0;
}

// AHB Method (Advanced High Peripheral Bus)
/*
int main()
{
    SYSCTL_GPIOHBCTL_R |= (1U << 5);
    GPIO_PORTF_AHB_DIR_R = (LED_RED | LED_BLUE | LED_GREEN); // pins 1->3 as output, was -> GPIO_PORTF_DIR_R = 0x0EU; 
    GPIO_PORTF_AHB_DEN_R = (LED_RED | LED_BLUE | LED_GREEN); // was -> GPIO_PORTF_DEN_R = 0x0EU; 

    ****NOTE**** 
    // To set the LEDs on and off, it needs a slightly different name as well, as seen below
    while(1)
    {
        ...
        // on
        GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE;
        ...
        // off
        GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = 0; 
        ...
    }

    ...
}

*/