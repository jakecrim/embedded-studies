#include <stdint.h>

#include "tm4c_cmsis.h"
#include "delay.h"

#define LED_RED     (1U << 1)
#define LED_BLUE    (1U << 2)
#define LED_GREEN   (1U << 3)

/* Initializing vars syntax */
int16_t x = -1;
uint16_t y = LED_RED | LED_GREEN;

// init an array (dont have to previde array size, can be inferred, can also make it larger than the provided initializers)
int16_t testArr[4] = 
{
    1*1,
    2*2,
    3*3,
    4*4
};

// init a struct (SEE BELOW POINT P1)

typedef struct
{
    uint8_t y;
    uint16_t x;
} point; 

typedef struct
{
   point top_left;
   point bottom_right; 
} window; 

typedef struct
{
    point corners[3]; 
} triangle; 


/* DEFINES */

/* GLOBALS*/
point p1 = 
{
    567U,
    0x5678U
};

point p2;

window w = 
{
    {567U, 0x5678U},
    {789U, 0x789U}
};

window w2;
triangle t;

int main()
{        
    // WORKING WITH STRUCTS
    point * pp;
    window * wp;

    p1.x = sizeof(point);
    p1.y = 0x15U;

    // examples of accessing these struct configurations
    w.top_left.x = 1U;
    w.bottom_right.y = 2U;

    t.corners[0].x = 1U;
    t.corners[2].x = 2U;

    p2 = p1;
    w2 = w;

    // pointers to structs and access
    pp = &p1;
    wp = &w2;

    (*pp).x = 1U;
    (*wp).bottom_right = *pp;

    // OR... (these are effectively the same as the above statements)
    pp->x = 1U;
    wp->bottom_right = *pp;


    /* REPLACEMENT TO THE RAW REGISTER ACCESS VIA HARD CODED ADDRESSES, NOW USING CMSIS STRUCT ACCESS */
    /* THIS WILL BLINK THE RED LED */

    // enabling clock, setting pin direction, data enable (ONLY WORKS IF THE REGISTERS HAVE R/W PERMISSIONS)
    SYSCTL->RCGC2 = (1U << 5);                       // set bit 5, was -> SYSCTL_RCGCGPIO_R = 0x20U;
    SYSCTL->GPIOHSCTL |= (1U << 5);
    GPIOF_HS->DIR |= (LED_RED | LED_BLUE | LED_GREEN); // pins 1->3 as output, was -> GPIO_PORTF_DIR_R = 0x0EU; 
    GPIOF_HS->DEN = (LED_RED | LED_BLUE | LED_GREEN); // was -> GPIO_PORTF_DEN_R = 0x0EU; 

    GPIOF_HS->DATA_Bits[LED_BLUE] = LED_BLUE;

    while(1)
    {
        GPIOF_HS->DATA_Bits[LED_RED] = LED_RED;
        delay(500000);
        GPIOF_HS->DATA_Bits[LED_RED] = 0;
        delay(500000);
    }
    
    //return 0;
}
