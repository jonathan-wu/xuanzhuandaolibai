#include"msp430f5438.h"
#include"Global.h"
#include"TimerA1.h"

#ifdef RotaryEncoder_Used_
volatile unsigned char E1_dir=0;
volatile unsigned long E1_beforeBase,E1_beforeCap,E1_interval;
volatile unsigned long E1_V;
volatile signed long E1_pulseCnt;
volatile unsigned char E2_dir=0;
volatile unsigned long E2_beforeBase,E2_beforeCap;
volatile signed long E2_interval;
volatile unsigned long E2_V;
volatile signed long E2_pulseCnt;

//P4.1,P4.2捕获,P3.6,P3.7IO口判断电平(输入模式，下拉电阻)
//CM_0不捕获，CM_1上升沿,CM_2下降沿,CM_3都捕获
void RotaryEncoder_init()
{  
    P4DIR &= ~(BIT1+ BIT2+ BIT3+ BIT4);
    P4SEL |=  BIT1+ BIT2+ BIT3+ BIT4;
    
    P3DIR &= ~(BIT0+ BIT1+ BIT2+ BIT3);
    P3REN |= BIT0+ BIT1+ BIT2+ BIT3;
    P3OUT &= ~(BIT0+ BIT1+ BIT2+ BIT3);
    
    TB0CCTL1 = CM_3+CCIS_0+CAP+SCS;                    // CCR1 capture mode P4.1
    TB0CCTL2 = CM_3+CCIS_0+CAP+SCS;                    // CCR1 capture mode P4.2
    TB0CCTL3 = CM_3+CCIS_0+CAP+SCS;                    // CCR1 capture mode P4.1
    TB0CCTL4 = CM_3+CCIS_0+CAP+SCS;                    // CCR1 capture mode P4.2    
    
    TB0CCTL1 |= CCIE;
    TB0CCTL2 |= CCIE;
    TB0CCTL3 |= CCIE;
    TB0CCTL4 |= CCIE;    
}

#pragma vector = TIMER0_B1_VECTOR
__interrupt void RotaryEncoder_ISR()
{
  unsigned char PhaseA1,PhaseB1,PhaseA2,PhaseB2;
  PhaseA1  = P3IN & BIT0;
  PhaseB1  = P3IN & BIT1;
  PhaseA2  = P3IN & BIT2;
  PhaseB2  = P3IN & BIT3;
  
  switch(TB0IV)
  {
    case  0: break;                          // No interrupt
    case  2:                                 // CCR1 used
      if ((PhaseA1 && PhaseB1)|((!PhaseA1)&&(!PhaseB1)))
      {        
//        if(E1_dir)
//        {
//          E1_beforeBase=TimeBase;
//        E1_beforeCap =TB0CCR1;               
//          E1_V=0;
//        }
//        else
//        {
//          E1_interval=(TimeBase-E1_beforeBase)*4000+TB0CCR1-E1_beforeCap;
//          E1_beforeBase=TimeBase;
//          E1_beforeCap =TB0CCR1;
//          E1_V=360000/E1_interval;
//        } 
        E1_pulseCnt++;
//        E1_dir=0;
      }
      else
      {
//        if(!E1_dir)
//        {
//          E1_beforeBase=TimeBase;
//          E1_beforeCap =TB0CCR1;               
//          E1_V=0;
//        }
//        else
//        {
//          E1_interval=(TimeBase-E1_beforeBase)*4000+TB0CCR1-E1_beforeCap;
//          E1_beforeBase=TimeBase;
//          E1_beforeCap =TB0CCR1;
//          E1_V=360000/E1_interval;
//        }        
        E1_pulseCnt--;
//        E1_dir=1;        
      }
      break;
    case  4:                                 // CCR2 used
      if ((PhaseA1&&PhaseB1)|((!PhaseA1)&&(!PhaseB1)))
      {
//        if(!E1_dir)
//        {
 //         E1_beforeBase=TimeBase;
 //        E1_beforeCap =TB0CCR2;               
//          E1_V=0;
//        }        
//        else
//        {
//          E1_interval=(TimeBase-E1_beforeBase)*4000+TB0CCR1-E1_beforeCap;
//          E1_beforeBase=TimeBase;
//          E1_beforeCap =TB0CCR2;
//          E1_V=360000/E1_interval;
//        }           
        E1_pulseCnt--;
 //       E1_dir=0;        
      }
      else
      {
//        if(E1_dir)
//        {
//          E1_beforeBase=TimeBase;
//          E1_beforeCap =TB0CCR2;               
//          E1_V=0;
//        }   
//        else
//        {
//          E1_interval=(TimeBase-E1_beforeBase)*4000+TB0CCR1-E1_beforeCap;
//          E1_beforeBase=TimeBase;
//          E1_beforeCap =TB0CCR2;
//          E1_V=360000/E1_interval;
//        }           
        E1_pulseCnt++;      
//        E1_dir=0;        
      }
      break;
    case  6:                                 // CCR3 used
      if ((PhaseA2 && PhaseB2)|((!PhaseA2)&&(!PhaseB2)))
      {        
//        if(E2_dir)
//        {
//          E2_beforeBase=TimeBase;
//          E2_beforeCap =TB0CCR3;               
//          E2_V=0;
//        }
//        else
//        {
//          E2_interval=(TimeBase-E2_beforeBase)*4000+TB0CCR1-E2_beforeCap;
//          E2_beforeBase=TimeBase;
//          E2_beforeCap =TB0CCR3;
//          E2_V=360000/E2_interval;
//        }
        E2_pulseCnt++;
//        E2_dir=0;
      }
      else
      {
//        if(!E2_dir)
//        {
//          E2_beforeBase=TimeBase;
//          E2_beforeCap =TB0CCR3;               
//          E2_V=0;
//        }
//        else
//        {
//          E2_interval=(TimeBase-E2_beforeBase)*4000+TB0CCR1-E2_beforeCap;
//          E2_beforeBase=TimeBase;
//          E2_beforeCap =TB0CCR3;
//          E2_V=360000/E2_interval;
//        }        
        E2_pulseCnt--;
//        E2_dir=1;        
      }
      break;
    case  8:                                 // CCR4 used
      if ((PhaseA2&&PhaseB2)|((!PhaseA2)&&(!PhaseB2)))
      {
//        if(!E2_dir)
//        {
//          E2_beforeBase=TimeBase;
 //         E2_beforeCap =TB0CCR4;               
//          E2_V=0;
//        }        
//        else
//        {
//          E2_interval=(TimeBase-E2_beforeBase)*4000+TB0CCR1-E2_beforeCap;
//          E2_beforeBase=TimeBase;
//          E2_beforeCap =TB0CCR4;
//          E2_V=360000/E2_interval;
//        }           
        E2_pulseCnt--;
//        E2_dir=0;        
      }
      else
      {
//        if(E2_dir)
//        {
//          E2_beforeBase=TimeBase;
//          E2_beforeCap =TB0CCR4;               
//          E2_V=0;
//        }   
//        else
//        {
//          E2_interval=(TimeBase-E2_beforeBase)*4000+TB0CCR1-E2_beforeCap;
//          E2_beforeBase=TimeBase;
//          E2_beforeCap =TB0CCR4;
//          E2_V=360000/E2_interval;
//        }           
        E2_pulseCnt++;
//        E2_dir=0;        
      }
      break;      
    case 10: break;                          // reserved
    case 12: break;                          // reserved
    case 14: break;                          // overflow
         
    default: break;     
  }
}
/*
#pragma vector = TIMER0_B0_VECTOR
__interrupt void TimerB0_ISR()
{
  L_interval++;
  if (L_interval  > 200)
    L_T=0;
  R_interval++;
  if (R_interval  > 200)
    R_T=0;  
}*/

#endif