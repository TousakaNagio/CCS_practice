#include <msp430.h> 


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// Setup URAR A1
	UCA1CTLW0 |= UCSWRST;       // put A1 into SW Reset

	UCA1CTLW0 |= UCSSEL__SMCLK; // BRCLK=SMCLK (want 115200 baud)
	UCA1BRW = 8;                // Prescalar = 8
	UCA1MCTLW = 0xD600;        // set modulation & low-freq

	// setup ports
	P2SEL0 &= ~BIT6;            // P2.6 set function to UART A1 Rx(01)
	P2SEL1 |= BIT6;

	PJDIR |= BIT0;              // set PJ.0 as output
	PJOUT &= ~BIT0;             // turn off LED initially

	PM5CTL0 &= ~LOCKLPM5;

	UCA1CTLW0 &= ~UCSWRST;      // take UART A1 out of SW Reset

	// setup IPQ
	UCA1IE |= UCRXIE;           // local enable for A1 RXIFG
	__enable_interrupt();       // global enable for maskables...(GIE bit in SR)

	while(1){}

	return 0;
}

// ISRs
#pragma vector = EUSCI_A1_VECTOR
__interrupt void EUSCI_A1_RX_ISR(void)
{
    if(UCA1RXBUF == 'a')
    {
        PJOUT ^= BIT0;          // toggle LED1
    }
}