#include"msp430f5438.h"
#include"Global.h"
#include"UCS.h"
#include"WDT.h"
#include"TimerA1.h"
#include"TimerB0.h"
#include"UART.h"

#include"RotaryEncoder.h"
#include"GUI.h"
#include"TFT_Menu.h"
#include"keyboard.h"
#include"Motor.h"
#include"PID.h"

unsigned char function=1;
unsigned char function4Flag=0;
unsigned char function6Flag;
signed int function6_speed;
signed long function6_E2_pulseCnt;

unsigned char command;
signed long E1_absPulseCnt;
signed long E1_lastAbsPulseCnt;
unsigned long nowTime,startTime;
signed char speedSign;
signed int speed;
signed long E2_lastPulseCnt;
signed long E1_pulseInMs,E1_pulseInLastMs;

PID_struct RP;

unsigned long abs(signed long n)
{
  if (n>0)
    return n;
  else
    return -n;
}

void timeCycle(void)
{

//计算绝对角度    
    E1_lastAbsPulseCnt=E1_absPulseCnt;
    E1_absPulseCnt=  E1_pulseCnt%4000;
    if (E1_absPulseCnt>2000)
      E1_absPulseCnt-=4000;
    else if(E1_absPulseCnt<-2000)
      E1_absPulseCnt+=4000;    
    
//每毫秒定时任务
    if(nowTime!=TimeBase)
    {
      nowTime = TimeBase;
      E1_pulseInMs = E1_absPulseCnt- E1_pulseInLastMs;
      E1_pulseInLastMs = E1_absPulseCnt;
      E2_interval=E2_pulseCnt-E2_lastPulseCnt;
      E2_lastPulseCnt=E2_pulseCnt;
//      if (nowTime%5==0)
//      {
 //       UART_sendlong(UCA1,E1_pulseCnt+1000000L);
 //       UART_sendstr(UCA1," ");
 //       UART_sendlong(UCA1,E2_pulseCnt+1000000L);
 //       UART_sendstr(UCA1," ");
//      }
      if ((!UCA1_GET_CHAR(&command))||(abs(E2_pulseCnt)>10000))
      {
        Motor_config(0);
        while(1);
      }
    }      
}

//基本任务1
unsigned char function_1(void)
{
  Motor_config(400);  
  
  while(1)
  {
    timeCycle();
   
    if (E2_pulseCnt>48)
    {
      Motor_config(-400);
    }
    else if(E2_pulseCnt<-48)
    {
      Motor_config(400);
    }     
    
    if (abs(E1_absPulseCnt)<1000)
    {
      Motor_config(0);
      return 0;
    }
  }
}

//基本任务2
unsigned char function_2(void)
{
    timeCycle();
    Motor_config(750);
    while(nowTime+100>TimeBase);
    Motor_config(-200);
    while(nowTime+1000>TimeBase)
    {
      timeCycle();
      if (!E1_absPulseCnt)
      {
        Motor_config(0);        
        return 0;
      }
    }
    Motor_config(0);
    return 1;
}

unsigned char function_3(void)
{
  while(1)
  {

//计算绝对角度    
    E1_lastAbsPulseCnt=E1_absPulseCnt;
    E1_absPulseCnt=  E1_pulseCnt%4000;
    if (E1_absPulseCnt>2000)
      E1_absPulseCnt-=4000;
    else if(E1_absPulseCnt<-2000)
      E1_absPulseCnt+=4000;    
    
//每毫秒定时任务
    if(nowTime!=TimeBase)
    {
      nowTime = TimeBase;
      E1_pulseInMs = E1_absPulseCnt- E1_pulseInLastMs;
      E1_pulseInLastMs = E1_absPulseCnt;
      E2_interval=E2_pulseCnt-E2_lastPulseCnt;
      E2_lastPulseCnt=E2_pulseCnt;
//      if (nowTime%5==0)
//      {
 //       UART_sendlong(UCA1,E1_pulseCnt+1000000L);
 //       UART_sendstr(UCA1," ");
 //       UART_sendlong(UCA1,E2_pulseCnt+1000000L);
 //       UART_sendstr(UCA1," ");
//      }
      if ((!UCA1_GET_CHAR(&command))||(abs(E2_pulseCnt)>10000))
      {
        Motor_config(0);
        while(1);
      }
    }      
    if ((abs(E1_absPulseCnt)<500)&&(abs(E1_absPulseCnt)>2))
    {
      RP.inAuto=1;
//      PID_setMode(&RP,AUTOMATIC);
      if(!PID_compute(&RP))
      {
        speed+=RP.myOutput;
        speed-=E2_interval*3;
        if (speed>0)
          speedSign = 1;
        else if (speed<0)
          speedSign = -1;
        else
          speedSign = 0;
        if (abs(speed)>900)
          speed=speedSign*900;
        if (speedSign>0)
        {
          if (E2_pulseCnt<133)
            Motor_config(speedSign*400+speed/3+10);
          else
          {
            Motor_config((speedSign*400+speed/3)+100);
          }
        }
        else
        {
          if (E2_pulseCnt>-133)
            Motor_config(speedSign*400+speed/3+10);
          else
          {
            Motor_config((speedSign*400+speed/3)-100);
          }
        }

        
//        if (RP.myOutput>0)
//          Motor_config(450+RP.myOutput/3-E2_pulseCnt/2);
//        else if (RP.myOutput<-0)
//          Motor_config(-450+RP.myOutput/3-E2_pulseCnt/2);
//        else
//          Motor_config(0);
   
      }
    }
    else
    {
      speed=0;
      speedSign=0;      
      Motor_config(0);
      RP.inAuto=0;
      /*
      if(abs(E1_absPulseCnt)>1000)
      {
        if(abs(E1_pulseInMs) >= 18)
        {
          Motor_config(0);
        }
        else if (abs(E1_absPulseCnt)>1900)
        {
          if(E1_pulseInMs>0)
            Motor_config(700);
          else
            Motor_config(-700);
        }
      }*/
//      PID_setMode(&RP,MANUAL);
    }          
  }
}

unsigned char function_4(void)
{
  while(1)
  {
//计算绝对角度    
    E1_lastAbsPulseCnt=E1_absPulseCnt;
    E1_absPulseCnt=  E1_pulseCnt%4000;
    if (E1_absPulseCnt>2000)
      E1_absPulseCnt-=4000;
    else if(E1_absPulseCnt<-2000)
      E1_absPulseCnt+=4000;    
    
//每毫秒定时任务
    if(nowTime!=TimeBase)
    {
      nowTime = TimeBase;
      E1_pulseInMs = E1_absPulseCnt- E1_pulseInLastMs;
      E1_pulseInLastMs = E1_absPulseCnt;
      E2_interval=E2_pulseCnt-E2_lastPulseCnt;
      E2_lastPulseCnt=E2_pulseCnt;
//      if (nowTime%5==0)
//      {
 //       UART_sendlong(UCA1,E1_pulseCnt+1000000L);
 //       UART_sendstr(UCA1," ");
 //       UART_sendlong(UCA1,E2_pulseCnt+1000000L);
 //       UART_sendstr(UCA1," ");
//      }
      if ((!UCA1_GET_CHAR(&command))||(abs(E2_pulseCnt)>10000))
      {
        Motor_config(0);
        while(1);
      }
    }      
    
    if (!function4Flag)
    {
      Motor_config(770);
      while(nowTime+60>TimeBase);
      Motor_config(0);      
      function4Flag=1;
      timeCycle();      
    }

    if ((abs(E1_absPulseCnt)<500)&&(abs(E1_absPulseCnt)>2))
    {
      RP.inAuto=1;
//      PID_setMode(&RP,AUTOMATIC);
      if(!PID_compute(&RP))
      {
        speed+=RP.myOutput;
        speed-=E2_interval;
        if (speed>0)
          speedSign = 1;
        else if (speed<0)
          speedSign = -1;
        else
          speedSign = 0;
        if (abs(speed)>900)
          speed=speedSign*900;
        if (speedSign>0)
          Motor_config(speedSign*400+speed/3);
        else
          Motor_config(speedSign*400+speed/3);

        
//        if (RP.myOutput>0)
//          Motor_config(450+RP.myOutput/3-E2_pulseCnt/2);
//        else if (RP.myOutput<-0)
//          Motor_config(-450+RP.myOutput/3-E2_pulseCnt/2);
//        else
//          Motor_config(0);
   
      }
    }
    else
    {
      speed=0;
      speedSign=0;      
      Motor_config(0);
      RP.inAuto=0;
//      PID_setMode(&RP,MANUAL);
    }        
  }
}

unsigned char function_6(void)
{
  while(1)
  {
//计算绝对角度    
    E1_lastAbsPulseCnt=E1_absPulseCnt;
    E1_absPulseCnt=  E1_pulseCnt%4000;
    if (E1_absPulseCnt>2000)
      E1_absPulseCnt-=4000;
    else if(E1_absPulseCnt<-2000)
      E1_absPulseCnt+=4000;    
    
//每毫秒定时任务
    if(nowTime!=TimeBase)
    {
      nowTime = TimeBase;
      E1_pulseInMs = E1_absPulseCnt- E1_pulseInLastMs;
      E1_pulseInLastMs = E1_absPulseCnt;
      E2_interval=E2_pulseCnt-E2_lastPulseCnt;
      E2_lastPulseCnt=E2_pulseCnt;
//      if (nowTime%5==0)
//      {
 //       UART_sendlong(UCA1,E1_pulseCnt+1000000L);
 //       UART_sendstr(UCA1," ");
 //       UART_sendlong(UCA1,E2_pulseCnt+1000000L);
 //       UART_sendstr(UCA1," ");
//      }
      if ((!UCA1_GET_CHAR(&command))||(abs(E2_pulseCnt)>10000))
      {
        Motor_config(0);
        while(1);
      }
    }      

    if ((abs(E1_absPulseCnt)<500)&&(abs(E1_absPulseCnt)>2))
    {
      RP.inAuto=1;
//      PID_setMode(&RP,AUTOMATIC);
      if(!PID_compute(&RP))
      {
        speed+=RP.myOutput;
        speed-=E2_interval;
        if (speed>0)
          speedSign = 1;
        else if (speed<0)
          speedSign = -1;
        else
          speedSign = 0;
        if (abs(speed)>900)
          speed=speedSign*900;
        if (speedSign>0)
          Motor_config(speedSign*400+speed/3+10);
        else
          Motor_config(speedSign*400+speed/3+10);

        
//        if (RP.myOutput>0)
//          Motor_config(450+RP.myOutput/3-E2_pulseCnt/2);
//        else if (RP.myOutput<-0)
//          Motor_config(-450+RP.myOutput/3-E2_pulseCnt/2);
//        else
//          Motor_config(0);
   
      }
    }
    else
    {
      speed=0;
      speedSign=0;      
      Motor_config(0);
      RP.inAuto=0;
//      PID_setMode(&RP,MANUAL);
    }        
  }
}

void main( void )
{
  WDT_init();
  UCS_init();
  TimerA1_init();
  TimerB0_init();
  UART_init(UCA1,115200);
  RotaryEncoder_init();
  
  keyboard_init();
//  GUI_init();
  
  Motor_init();
  
  {  
    RP.myOutput = 0;
    RP.myInput = &E1_absPulseCnt;
    RP.mySetpoint = 0;
    RP.inAuto = 1;
    PID_setOutputLimits(&RP, (signed long)-100, (signed long)100);//(加速度)    
//    PID_setOutputLimits(&RP, (signed long)-600, (signed long)600);    
    RP.SampleTime = 5;
    PID_setControllerDirection(&RP, 1);
    PID_setTunings(&RP, 184, 7000, 34);                              //400,0,0 //184,6000,35
    if (TimeBase>RP.SampleTime)
      RP.lastTime = TimeBase-RP.SampleTime;
    else
      RP.lastTime = 0;    
  }
  
  _EINT();
  
//  while(UCA1_GET_CHAR(&command));
  _DINT();
  E1_pulseCnt=2000;
  E2_pulseCnt=0;
  E1_pulseInLastMs=2000;
  _EINT();
  
  startTime = TimeBase;
  
//  Motor_config(362);
  
//  Clear_Screen();
//  TFT_Menu_StartMenu();  
  
  while(function_3());
  
  /*
  
  while(1)
  {
    
//主要任务
    switch(function)
    {
      
    case 1:
      break;
      
    case 2:
      break;
      
    case 3:


      break;
      
    case 4:

      
      break;
    case 5:
      break;
    case 6:
      if (E1_absPulseCnt==0)
      {
        function6Flag=1;
        function6_E2_pulseCnt=E2_pulseCnt;
        function6_speed=400;
      }
      if (function6Flag)
      {
//          if((!PID_compute(&RP))&&(abs(E2_pulseCnt-function6_E2_pulseCnt)<2000))
          {
            speed+=RP.myOutput;
            speed-=E2_interval;
            if (speed>0)
              speedSign = 1;
            else if (speed<0)
              speedSign = -1;
            else
              speedSign = 0;
            if (abs(speed)>900)
              speed=speedSign*900;
            if (speedSign>0)
              Motor_config(speedSign*400+speed/3+5);
            else
              Motor_config(speedSign*400+speed/3+5);
//          }
  
        if ((abs(E1_absPulseCnt)<500)&&(abs(E1_absPulseCnt)>2))
        {
          RP.inAuto=1;
    //      PID_setMode(&RP,AUTOMATIC);
          if(!PID_compute(&RP))
          {
            speed+=RP.myOutput;
            speed-=E2_interval*3;
            if (speed>0)
              speedSign = 1;
            else if (speed<0)
              speedSign = -1;
            else
              speedSign = 0;
            if (abs(speed)>900)
              speed=speedSign*900;
            if (speedSign>0)
            {
                Motor_config(speedSign*400+speed/3+5);
            }
            else
            {
                Motor_config(speedSign*400+speed/3+5);
            }
          }
          if(abs(E2_pulseCnt-function6_E2_pulseCnt)>2000)
          {
            function6Flag=0;
            Motor_config(0);
          }          
        }
      }
      else
      {
        Motor_config(0);
        if ((abs(E1_absPulseCnt)>1990)&&(function6Flag))
        {
          function6Flag=0;
        }
      }
      break;
    default:
      break;
    }
    

    
  }*/
}
