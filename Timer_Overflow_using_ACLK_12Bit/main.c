#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// setup ports
	PJDIR |= BIT0; // set PJ.0 as output
	PJOUT &= ~BIT0;
	PM5CTL0 &= ~LOCKLPM5;

	// setup timer TB0
	TB0CTL |= TBCLR;
	TB0CTL |= TBSSEL__ACLK;
	TB0CTL |= MC__CONTINUOUS;
	TB0CTL |= CNTL_1; // 12-bit length

	// SETUP TIMER IRQ
	TB0CTL |= TBIE;
	__enable_interrupt();
	TB0CTL &= ~TBIFG;

	while(1){}

	return 0;
}

// ISRs
#pragma vector = TIMER0_B1_VECTOR
__interrupt void ISR_TB0_Overflow(void)
{
    PJOUT ^= BIT0;
    TB0CTL &= ~TBIFG;
}
