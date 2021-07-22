#include <msp430.h> 


// ¥ÎUART Tx ¶Ç¦r

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    // setup UART
    UCA1CTLW0 |= UCSWRST;   //PUT UART A1 INTO SW RESET

    UCA1CTLW0 |= UCSSEL__SMCLK; //CHOOSE SMCLK FOR UART A1
    UCA1BRW = 8;    //SET PRESCALAR TO 8
    UCA1MCTLW = 0XD600; //setup modulation

    P4SEL1 &= ~BIT3;    //P4SEL1.3: P4SSEL0.3 = 01
    P4SEL0 |= BIT3;     //puts UART A1 Tx on P4.3

    PM5CTL0 &= ~LOCKLPM5;

    UCA1CTLW0 &= ~UCSWRST;      //put UART A1 into SW reset

    while(1){
        UCA1TXBUF = 'A';       //send 'A' out over UART A1 Tx
        for(i=0; i<10000; i++){}        //delay between frames
    }


    return 0;
}
