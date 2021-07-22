#include <msp430.h>
#include <Module.h>


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P4DIR = CLR(P4DIR, BIT0);
	P4REN = SET(P4REN, BIT0);
	P4OUT = SET(P4OUT, BIT0);

	PJDIR = SET(PJDIR, BIT0);
	PJOUT = CLR(PJOUT, BIT0);

//	PJDIR &= ~BIT0;
//	PJREN |= BIT0;
//	PJOUT |= BIT0;
//
//	PJDIR |= BIT0;
//	PJOUT &= ~BIT0;

	while(1){
	    if((P4IN & BIT0) == 0)
	        PJOUT = SET(PJOUT, BIT0);
//	        PJOUT |= BIT0;
	    else
	        PJOUT = CLR(PJOUT, BIT0);
//	        PJOUT &= ~BIT0;
	}
	
	return 0;
}
