#include <msp430.h> 

unsigned int ADC_Value;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    PJDIR |= BIT0;
    PJDIR |= BIT1;

    P1SEL1 |= BIT2;     // configure P1.2 as Analog function
    P1SEL0 |= BIT2;     // 11

    PM5CTL0 &= ~LOCKLPM5;

    // configure ADC
    ADC10CTL0 &= ~ADC10SHT0;    // conversion cycles = 16 ##©Ç©Ç
    ADC10CTL0 |= ADC10SHT_2;    // ADCSHT = 10
    ADC10CTL0 |= ADC10ON;       // turn on ADC

    ADC10CTL1 |= ADC10SSEL_2;   // set resolution to 12-bit
    ADC10CTL1 |= ADC10RES_L;    // 10 ##©Ç©Ç

    ADC10MCTL0 |= ADC10INCH_2;  // select A2

    // Setup IRQ
    ADC10IE |= ADC10IE0;      // conversion complete IRQ local encable
//    __enable_interrupt();   // enable maskables...

    while(1){
        ADC10CTL0 |= ADC10ENC | ADC10SC;        // start conversion
        __bis_SR_register(GIE | LPM0_bits);     // enabled maskables

    }


    return 0;
}

// ISR
#pragma vector = ADC_VECTOR
__interrupt void ADC_ISR(void){

    __bic_SR_register_on_exit(LPM0_bits);
     ADC_Value = ADC10MEM0;       // Read ADC value

     if(ADC_Value > 3613){
         PJOUT |= BIT0;
         PJOUT &= ~BIT1;
     }
     else{
         PJOUT &= ~ BIT0;
         PJOUT |= BIT1;
     }
}
