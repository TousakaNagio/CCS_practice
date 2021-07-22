//#include <stdio.h>
//#include <msp430.h>
//
//
///**
// * hello.c
// */
//int main(void)
//{
//    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
//    PM5CTL0 &= ~LOCKLPM5;
//    // Enable LEDs
//    P3OUT &= ~(BIT6+BIT7+BIT5+BIT4);
//    P3DIR |= BIT6+BIT7+BIT5+BIT4;
////    PJOUT &= ~(BIT0+BIT1+BIT2+BIT3);
////    PJDIR |= BIT0 +BIT1+BIT2+BIT3;
//    PJOUT &= ~(0x01);
//    PJDIR |= 0x01;
//
////    unsigned char LED1 = 0x01;
//    unsigned int count = 0,i;
//
//    while(1)
//    {
//        PJOUT = 0x01;
//        i = 10000;                          // SW Delay
//        do i--;
//        while(i != 0);
////        __no_operation();
//        PJOUT &= ~(0x01);
//        i = 10000;                          // SW Delay
//        do i--;
//        while(i != 0);
//
//    }
////    return 0;
//}
//***************************************************************************************
//  MSP430 Blink the LED Demo - Software Toggle P1.0
//
//  Description; Toggle P1.0 by xor'ing P1.0 inside of a software loop.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430x5xx
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  Texas Instruments, Inc
//  July 2013
//***************************************************************************************

#include <msp430.h>

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings
    PJDIR |= 0x01;                          // Set P1.0 to output direction
    PJOUT &= ~(0x01);

    for(;;) {
        volatile unsigned int i;            // volatile to prevent optimization+

        PJOUT = 0x01;                       // Toggle P1.0 using exclusive-OR

        i = 10000;                          // SW Delay
        do i--;
        while(i != 0);

        PJOUT &= ~(0x01);
        i = 10000;                          // SW Delay
        do i--;
        while(i != 0);

    }
}
