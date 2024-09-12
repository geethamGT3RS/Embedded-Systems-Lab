#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

#define STCTRL *((volatile long *)0xE000E010)    // control and status
#define STRELOAD *((volatile long *)0xE000E014)  // reload value
#define STCURRENT *((volatile long *)0xE000E018) // current value

#define COUNT_FLAG (1 << 16) // bit 16 of CSR automatically set to 1
#define ENABLE (1 << 0)      // bit 0 of CSR to enable the timer
#define CLKINT (1 << 2)      // bit 2 of CSR to specify CPU clock
#define INTERRUPT (1 << 1)   // bit 2 of CSR to specify CPU clock
#define CLOCK_MHZ 16

void GPIO_INIT(void)
{
    SYSCTL_RCGC2_R |= 0x00000020;   /* enable clock to GPIOF */
    GPIO_PORTF_LOCK_R = 0x4C4F434B; /* unlock commit register */
    GPIO_PORTF_CR_R = 0x1F;         /* make PORTF0 configurable */
    GPIO_PORTF_DEN_R = 0x1E;        /* set PORTF pins 4 pin */
    GPIO_PORTF_DIR_R = 0x0E;        /* set PORTF4 pin as input user switch pin */
    GPIO_PORTF_PUR_R = 0x10;        /* PORTF4 is pulled up */
}

void SysTickHandler()
{
    GPIO_PORTF_DATA_R ^= 0x4;
    return;
}

int main(void)
{
    GPIO_INIT();
    STCURRENT = 0;
    STRELOAD = 500 * 16000;                  // reload value for 'ms' milliseconds
    STCTRL |= (CLKINT | ENABLE | INTERRUPT); // set internal clock, enable the timer
    int mask = 1 << 1;

// LAB-2 PART-1
#if 1
    int clicked = 0;
    while (1)
    {
        clicked = GPIO_PORTF_DATA_R & 0x10;
        if (clicked == 0x0)
            GPIO_PORTF_DATA_R |= mask;
        else
            GPIO_PORTF_DATA_R &= ~mask;
    }
    return 0;
#endif
}