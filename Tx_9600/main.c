#include <msp430.h> 


// ¥ÎUART Tx 9600

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    // setup UART
    UCA1CTLW0 |= UCSWRST;   //PUT UART A1 INTO SW RESET

    UCA1CTLW0 |= UCSSEL__ACLK; //CHOOSE ACLK FOR UART A1
    UCA1BRW = 3;    //SET PRESCALAR TO 3
    UCA1MCTLW = 0X9200; //setup modulation

    P4SEL1 &= ~BIT3;    //P4SEL1.3: P4SSEL0.3 = 01
    P4SEL0 |= BIT3;     //puts UART A1 Tx on P4.3

    PM5CTL0 &= ~LOCKLPM5;

    UCA1CTLW0 &= ~UCSWRST;      //put UART A1 into SW reset

    while(1){
        UCA1TXBUF = 0x55;       //send 0x55 out over UART A1 Tx
        for(i=0; i<10000; i++){}        //delay between frames
    }


    return 0;
}
