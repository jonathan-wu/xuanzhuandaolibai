#include "msp430f5438.h"
#include "PWM.h"
#ifdef BTS7960_Used_
void Motor_init()
{
  PWM_init();  
}

void Motor_config(signed int rate)
{
  if (rate>0)
  {
    PWM_1(rate);
    PWM_2(0);
    P8SEL |= BIT1;
    P8OUT &= BIT2;
    P8SEL &=~BIT2;
  }
  else if (rate<0)
  {
    PWM_1(0);
    PWM_2((unsigned)-rate);
    P8SEL |= BIT2;
    P8OUT &= BIT1;
    P8SEL &=~BIT1;    
  }
  else
  {
    P8OUT &=~(BIT1+BIT2);
    P8SEL &=~(BIT1+BIT2);
    PWM_1(0);
    PWM_2(0);
  }
}
#else
void Motor_init()
{
  PWM_init();
  P5DIR |= BIT4+ BIT5;
  P5OUT |= BIT4;
  P5OUT &=~BIT5;
}
void Motor_config(signed int rate)
{
  if (rate>0)
  {
    P5OUT |= BIT4;
    P5OUT &=~BIT5;
    PWM_1(rate);    
  }
  else if (rate<0)
  {
    P5OUT |= BIT5;
    P5OUT &=~BIT4;
    PWM_1(-rate);
  }
  else
  {
    P5OUT |= BIT4+ BIT5;
    PWM_1(0);
  }
}

#endif
