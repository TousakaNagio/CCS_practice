#include <msp430.h>

void SystemInit(void);
void StartUpSequence(void);
void LongDelay(void);
/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	SystemInit();
	StartUpSequence();
	return 0;
}
void StartUpSequence(void)
{
  unsigned char flag=4,up=1,counter = 0;
  unsigned char LED_ArrayPJ[] = {0x01,0x02,0x04,0x08};
  unsigned char LED_ArrayP3[] = {0x80,0x40,0x20,0x10};

  while (counter <30)
    {
      counter++;
      PJOUT &= ~(BIT0 +BIT1+BIT2+BIT3);
      P3OUT &= ~(BIT4 +BIT5+BIT6+BIT7);
      if(up)// from the outside - in
        {
          while(flag)
            {
              P3OUT = LED_ArrayP3[flag-1];
              PJOUT = LED_ArrayPJ[flag-1];
              LongDelay();
              flag--;
            }
            up=0;
        }
      else
        {
          while(flag<4)
            {
              P3OUT = LED_ArrayP3[flag];
              PJOUT = LED_ArrayPJ[flag];
              LongDelay();
              flag++;
            }
            up = 1;
          }
    }

  // Exit Loop, Clear LEDs
  PJOUT &= ~(BIT0 +BIT1+BIT2+BIT3);
  P3OUT &= ~(BIT4 +BIT5+BIT6+BIT7);
}

void LongDelay(void)
{
  __delay_cycles(250000);
  __no_operation();
}

void SystemInit(void)
{
  // Startup clock system in max. DCO setting ~8MHz
  // This value is closer to 10MHz on untrimmed parts
  CSCTL0_H = 0xA5;                          // Unlock register
  CSCTL1 |= DCOFSEL0 + DCOFSEL1;            // Set max. DCO setting
  CSCTL2 = SELA_1 + SELS_3 + SELM_3;        // set ACLK = vlo; MCLK = DCO
  CSCTL3 = DIVA_0 + DIVS_0 + DIVM_0;        // set all dividers
  CSCTL0_H = 0x01;                          // Lock Register

  // Turn off temp.
  REFCTL0 |= REFTCOFF;
  REFCTL0 &= ~REFON;

  // Enable switches
  // P4.0 and P4.1 are configured as switches
  // Port 4 has only two pins
  P4OUT |= BIT0 +BIT1;                      // Configure pullup resistor
  P4DIR &= ~(BIT0 + BIT1);                  // Direction = input
  P4REN |= BIT0 + BIT1;                     // Enable pullup resistor
  P4IES &= ~(BIT0+BIT1);                    // P4.0 Lo/Hi edge interrupt
  P4IE = BIT0+BIT1;                         // P4.0 interrupt enabled
  P4IFG = 0;                                // P4 IFG cleared

  // Enable LEDs
  P3OUT &= ~(BIT6+BIT7+BIT5+BIT4);
  P3DIR |= BIT6+BIT7+BIT5+BIT4;
  PJOUT &= ~(BIT0+BIT1+BIT2+BIT3);
  PJDIR |= BIT0 +BIT1+BIT2+BIT3;

  // Terminate Unused GPIOs
  // P1.0 - P1.6 is unused
  P1OUT &= ~(BIT0 + BIT1 + BIT2 + BIT3 + BIT5 + BIT6 + BIT7);
  P1DIR &= ~(BIT0 + BIT1 + BIT2 + BIT3 + BIT5 + BIT6 + BIT7);
  P1REN |= (BIT0 + BIT1 + BIT2 + BIT3 + BIT5 + BIT6 + BIT7);

  // P1.4 is used as input from NTC voltage divider
  // Set it to output low
  P1OUT &= ~BIT4;
  P1DIR |= BIT4;

  // P2.2 - P2.6 is unused
  P2OUT &= ~(BIT2 + BIT3 + BIT4 + BIT5 + BIT6);
  P2DIR &= ~(BIT2 + BIT3 + BIT4 + BIT5 + BIT6);
  P2REN |= (BIT2 + BIT3 + BIT4 + BIT5 + BIT6);

  // Configure UART pins P2.0 & P2.1
  P2SEL1 |= BIT0 + BIT1;
  P2SEL0 &= ~(BIT0 + BIT1);

  // P2.7 is used to power the voltage divider for the NTC thermistor
  P2OUT &= ~BIT7;
  P2DIR |= BIT7;

  // P3.0,P3.1 and P3.2 are accelerometer inputs
  P3OUT &= ~(BIT0 + BIT1 + BIT2);
  P3DIR &= ~(BIT0 + BIT1 + BIT2);
  P3REN |= BIT0 + BIT1 + BIT2;

  // PJ.0,1,2,3 are used as LEDs
  // crystal pins for XT1 are unused
  PJOUT &= ~(BIT4+BIT5);
  PJDIR &= ~(BIT4+BIT5);
  PJREN |= BIT4 + BIT5;
}
