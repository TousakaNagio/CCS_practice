#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// setup ports
    PJDIR |= BIT0;              //set P1.0 as output
    PJOUT &= ~BIT0;
    PM5CTL0 &= ~LOCKLPM5;

    // setup timer
    TB0CTL |= TBCLR;            //RESET TB0
    TB0CTL |= MC__UP;           //PUT IN UP MODE FOR CCR0
    TB0CTL |= TBSSEL__ACLK;     //CHOOSE ACLK
    TB0CCR0 = 16384;            //SET CCR0 = 16384

    // SETUP TIMER COMPARE IRQ
    TB0CCTL0 |= CCIE;           //LOCAL ENABLE FOR CCR0
    __enable_interrupt();
    TB0CCTL0 &= ~CCIFG;

    while(1){}

	return 0;
}

#pragma vector = TIMER0_B0_VECTOR
__interrupt void ISR_TB0_CCR0(void)
{
    PJOUT ^= BIT0;
    TB0CCTL0 &= ~CCIFG;

}
