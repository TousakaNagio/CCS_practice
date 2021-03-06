#include <msp430.h> 

//??Timer?p?ɱ???LED?{?{
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// setup ports
	PJDIR |= BIT0;//set P1.0 as output
	PJOUT &= ~BIT0;
	PM5CTL0 &= ~LOCKLPM5;

	// setup timer
	TB0CTL |= TBCLR;// reset timer
	TB0CTL |= TBSSEL__ACLK; // clock = ACLK
	TB0CTL |= MC__CONTINUOUS; // mode = continuous

	// setup TB0 overflow IRQ
	TBCTL |= TBIE; // local enable for TB0 overflow
	__enable_interrupt(); // Enable maskable IRQs
	TB0CTL &= ~ TBIFG;

	// main loop
	while(1){

	}


	return 0;
}
// ISRs
#pragma vector = TIMER0_B1_VECTOR
__interrupt void ISR_TB0_Overflow(void)
{
    PJOUT ^= BIT0; //toggle LED1
    TB0CTL &= ~TBIFG;

}
