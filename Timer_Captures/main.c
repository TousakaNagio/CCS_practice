#include <msp430.h> 

int WhatICaptured = 0;

// 利用Timer capture可實現計時功能
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	// setup ports
    PJDIR |= BIT0;              //set PJ.0 as output
    PJOUT &= ~BIT0;             //clear PJ.0 initially

    P4DIR &= ~BIT1;             //SET P4.1 AS INPUT
    P4REN |= BIT1;              //ENABLE RESISTOR ON P4.1
    P4OUT |= BIT1;              //MAKE RESISTOR A PULL-UP
    P4IES |= BIT1;              //SET IRQ SENSITIVITY TO H-TO-l

    PM5CTL0 &= ~LOCKLPM5;       //TURN ON DIGITAL I/O

    // SETUP PORT IRQ
    P4IE |= BIT1;               //LOCAL ENABLE FOR P4.1
    __enable_interrupt();       // ENABLE MASLABLE IRQS
    P4IFG &= ~BIT1;             //CLEAR FLAG

    // SETUP TIMER
    TB0CTL |= TBCLR;
    TB0CTL |= MC__CONTINUOUS;
    TB0CTL |= TBSSEL__ACLK;
    TB0CTL |= ID__8;            //DIVID BY 8

    // SETUP CAPTURE
    TB0CCTL0 |= CAP;            //PUT CCR0 INTO CAPTURE MODE
    TB0CCTL0 |= CM_3;       //SENSITIVE TO BOTH EDGES
    TB0CCTL0 |= CCIS_2;      //PUT CAPTURE INPUT LEVEL AT GND




    while(1){}

	return 0;
}

#pragma vector = PORT4_VECTOR
__interrupt void ISR_Port4_SW1(void)
{
        PJOUT ^= BIT0;
        TB0CCTL0 ^= CCIS0;      //SWITCH BACK AND FORTH BETWEEN GND & VCC
        WhatICaptured = TB0CCR0;//STORE FOR CAPTURE VALUE
        P4IFG &= ~BIT1;             //CLEAR FLAG
}


