#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

#define COUNTER 700000

int main(void)
{
    SYSCTL_RCGC2_R |= 0x00000020;       /* enable clock to GPIOF */
    GPIO_PORTF_LOCK_R = 0x4C4F434B;     /* unlock commit register */
    GPIO_PORTF_CR_R = 0x1F;             /* make PORTF0 configurable */
    GPIO_PORTF_DEN_R = 0x1E;            /* set PORTF pins 4 pin */
    GPIO_PORTF_DIR_R = 0x0E;            /* set PORTF4 pin as input user switch pin */
    GPIO_PORTF_PUR_R = 0x10;            /* PORTF4 is pulled up */

//LAB1-Q2
#if 1
    int current=0;
    int i=0;
    while(1)
    {

        if(current%3==0)
            {GPIO_PORTF_DATA_R = 0x02;}
        if(current%3==1)
            {GPIO_PORTF_DATA_R = 0x04;}
        if(current%3==2)
            {GPIO_PORTF_DATA_R = 0x08;}
        for(i=0; i<COUNTER; i++)
            continue;
        GPIO_PORTF_DATA_R = 0x00;
        for(i=0; i<COUNTER; i++)
            continue;
        current++;
    }
#endif

}