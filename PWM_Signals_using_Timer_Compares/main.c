#include <msp430.h> 


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// setup ports
	PJDIR |= BIT0;              //set P1.0 as output
    PJOUT |= BIT0;
    PM5CTL0 &= ~LOCKLPM5;

    // setup timer
    TB0CTL |= TBCLR;            //RESET TB0
    TB0CTL |= MC__UP;           //PUT IN UP MODE FOR CCR0
    TB0CTL |= TBSSEL__ACLK;     //CHOOSE ACLK(32kHz)
    TB0CCR0 = 32768;            //SET CCR0 = 16384
    TB0CCR1 = 1638;             //SET PWM DUTY CYCLE

    // SETUP COMPARE IRQS
    TB0CCTL0 |= CCIE;           //LOCAL ENABLE FOR CCR0
    TB0CCTL1 |= CCIE;           //LOCAL ENABLE FOR CCR1
    __enable_interrupt();       //enable maskable interrupts
    TB0CCTL0 &= ~CCIFG;         //CLEAR FLAG FOR CCR0
    TB0CCTL1 &= ~CCIFG;         //CLEAR FLAG FOR CCR1

    while(1){}

	return 0;
}

#pragma vector = TIMER0_B0_VECTOR //ISR for period
__interrupt void ISR_TB0CCR0(void)
{
    PJOUT |= BIT0;              //turn LED ON
    TB0CCTL0 &= ~CCIFG;         //CLEAR FLAG FOR CCR0
}

#pragma vector = TIMER0_B1_VECTOR
__interrupt void ISR_TB0CCR1(void)
{
    PJOUT &= ~CCIFG;
    TB0CCTL1 &= ~CCIFG;         //CLEAR FLAG FOR CCR1
}
