#include <msp430.h> 

char message[] = "Hello World";
unsigned int position;
// ¥ÎUART Tx ¶Çstring with interrupt

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    // setup UART
    UCA1CTLW0 |= UCSWRST;   //PUT UART A1 INTO SW RESET

    UCA1CTLW0 |= UCSSEL__SMCLK; //CHOOSE SMCLK FOR UART A1
    UCA1BRW = 8;    //SET PRESCALAR TO 8
    UCA1MCTLW = 0XD600; //setup modulation

    P4DIR &= ~BIT1;     //Make P4.1 as input
    P4REN |= BIT1;      //Enable resistor
    P4OUT |= BIT1;      //Make it a pill UP
    P4IES |= BIT1;      //Make IPQ sent H-to-L

    P4SEL1 &= ~BIT3;    //set P4.3 to use UART A1 Tx function
    P4SEL0 |= BIT3;

    PM5CTL0 &= ~LOCKLPM5;

    UCA1CTLW0 &= ~UCSWRST;      //put UART A1 into SW reset

    //Enable IPQs
    P4IE |= BIT1;           // ENABLE SW1 IRQ
    P4IFG &= ~BIT1;         // CLEARS FLAG
    __enable_interrupt();   // global enable IPQS

    while(1){}

    return 0;
}

// ISRs
#pragma vector = PORT4_VECTOR
__interrupt void ISR_Port4_S1(void)
{
    position = 0;
    UCA1IE |= UCTXCPTIE;            // Turn on Tx complete IRQ
    UCA1IFG &= ~UCTXCPTIFG;         // clear Tx complete flag
    UCA1TXBUF = message[position];  // put first char from message into Tx buf

    P4IFG &= ~BIT1;                 // clear flag for P4.1

}

#pragma vector = EUSCI_A1_VECTOR
__interrupt void ISR_EUSCI_A1(void)
{
    if(position == sizeof(message)){
        UCA1IE &= ~UCTXCPTIE;        // turn off Tx complete IRQ
    }
    else{
        position ++;
        UCA1TXBUF = message[position];  // put next char into Tx buf

    }
    UCA1IFG &= ~UCTXCPTIFG;            // clear Tx complete flag

}
