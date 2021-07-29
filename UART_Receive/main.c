#include <msp430.h> 


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	UCA0CTLW0 |= UCSWRST;
//	UCA0CTL1 = UCSSEL__ACLK;                      // Set ACLK = 32768 as UCBRCLK
//	UCA0BR0 = 3;                              // 9600 baud
//	UCA0BR1 = 0;
//	UCA0MCTLW |= 0x9200;                      // 32768/9600 - INT(32768/9600)=0.41
//                                            // UCBRSx value = 0x53 (See UG)
//	UCA0CTL1 &= ~UCSWRST;                     // release from reset
//	UCA0IE |= UCRXIE;                         // Enable RX interrupt

	UCA0CTLW0 = UCSSEL__SMCLK; // BRCLK=SMCLK (want 115200 baud)
	UCA0BRW = 8;                // Prescalar = 8
	UCA0MCTLW |= 0xD600;        // set modulation & low-freq

	// setup ports
    P2SEL1 &= ~BIT1;
    P2SEL0 |= (BIT1);

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
__interrupt void USCI_A0_ISR(void)
{
    if(UCA0RXBUF == 'a')
    {
        PJOUT ^= BIT0;          // toggle LED1
    }
}
