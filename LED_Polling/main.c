#include <msp430.h> 



int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PJDIR |= BIT0;
	PJOUT &= ~BIT0;

	P4DIR &= ~BIT0;
	P4REN |= BIT0;
	P4OUT |= BIT0;

	PM5CTL0 &= ~LOCKLPM5;

	int SW1,i;

	while(1){
	    SW1 = P4IN;
	    SW1 &= BIT0;

	    if(SW1 == 0){
	        PJOUT ^= BIT0;
	    }
//	    else{
//	        PJOUT &= ~BIT0;
//	    }
	    for(i=0;i<10000;i++){

	    }
	}
	return 0;
}
