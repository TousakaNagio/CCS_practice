#include <msp430.h> 


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// Setup URAR A1
	UCA0CTLW0 |= UCSWRST;       // put A1 into SW Reset

	UCA0CTL1 |= UCSSEL__SMCLK; // BRCLK=SMCLK (want 115200 baud)
	UCA0BRW = 8;                // Prescalar = 8
	UCA0MCTLW = 0xD600;        // set modulation & low-freq


	// setup ports
	P2SEL0 &= ~(BIT0+BIT1);            // P2.1 set function to UART A1 Rx(01)
	P2SEL1 |= (BIT0+BIT1);

	PJDIR |= BIT0;              // set PJ.0 as output
	PJOUT &= ~BIT0;             // turn off LED initially

	PM5CTL0 &= ~LOCKLPM5;

	UCA0CTLW0 &= ~UCSWRST;      // take UART A1 out of SW Reset

	// setup IPQ
	UCA0IE |= UCRXIE;           // local enable for A1 RXIFG
	__enable_interrupt();       // global enable for maskables...(GIE bit in SR)

	while(1){}

	return 0;
}

// ISRs
#pragma vector = USCI_A0_VECTOR
__interrupt void USCI_A0_RX_ISR(void)
{
    if(UCA0RXBUF == 'a')
    {
        PJOUT ^= BIT0;          // toggle LED1
    }
}
