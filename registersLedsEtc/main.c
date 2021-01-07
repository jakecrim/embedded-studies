#include <stdint.h>
#include "stm32f303xc.h"


//#define RCC_BASE (*((volatile uint32_t *)0x40021014))

//#define GPIOE_BASE  (*((volatile unsigned int *)0x48001000U))


// defining the correct bits for each led color, (ex: 1U << 15 is 
//												binary:00000000000000001000000000000000
//												hex: 0x00008000)

#define LED_GREEN (1U << 15)
#define LED_ORANGE (1U << 14)
#define LED_RED (1U << 13)
#define LED_BLUE (1U << 12)
#define LED_GREEN2 (1U << 11)
#define LED_ORANGE2 (1U << 10)
#define LED_RED2 (1U << 9)
#define LED_BLUE2 (1U << 8)

#define GPIOE_DATA_OUT (*((volatile unsigned int *)0x48001014U))

int main()
{

	// 'OR'-ing the bits together corresponding to the correct pins for each LED color that we want
	// unsigned int LED_SET  =  LED_GREEN | LED_ORANGE | LED_RED | LED_BLUE | LED_GREEN2 | LED_ORANGE2 | LED_RED2 | LED_BLUE2 ;
	unsigned int LED_SET  =  LED_GREEN | LED_RED | LED_GREEN2 | LED_RED2; 
         
    // enables clock for GPIOE
    RCC_BASE = 0x00200014U;
	// store into the base adress which pins you will be setting OUT 
	GPIOE_BASE = 0x55555555U;

	//LED_SET = 0x0000FF00;
	//LED_SET = LED_SET >> 2;

    while(1){
        //GREEN ON (putting the value into the GPIOE data out register)
		GPIOE_DATA_OUT = LED_SET;

        //GREEN OFF (set all bits to 0)
        GPIOE_DATA_OUT = 0x00000000U;
    }


    return 0;
}
