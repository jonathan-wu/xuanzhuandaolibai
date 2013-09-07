#include "msp430x54x.h"
#include "keyboard.h"
unsigned char read_key(void)  //解码键盘值,返回字符
{
  if(readed) return '?';
  readed=1;
  switch(tem)
  {
  case 0x11:return 'D';break;
  case 0x12:return '#';break;
  case 0x14:return '0';break;
  case 0x18:return '*';break;
  case 0x21:return 'C';break;
  case 0x22:return '9';break;
  case 0x24:return '8';break;
  case 0x28:return '7';break;
  case 0x41:return 'B';break;
  case 0x42:return '6';break;
  case 0x44:return '5';break;
  case 0x48:return '4';break;
  case 0x81:return 'A';break;
  case 0x82:return '3';break;
  case 0x84:return '2';break;
  case 0x88:return '1';break;
  default:return '?';break;
  }
}
void scan_key(void)           //扫描键盘，读取按键行列值
{
  tem=0x00;                         //默认为0-0
  P6DIR |= BIT0+BIT1+BIT2+BIT3;     //行输出低，检索列
  P6OUT &=~(BIT0+BIT1+BIT2+BIT3);
  P6DIR &=~(BIT4+BIT5+BIT6+BIT7);
  if((P6IN&BIT7)==0) tem |=0x01;    //列1为低，表示该列中有按键被按下，记录列号0001b
  if((P6IN&BIT6)==0) tem |=0x02;    //列号0010b
  if((P6IN&BIT5)==0) tem |=0x04;    //列号0100b
  if((P6IN&BIT4)==0) tem |=0x08;    //列号1000b
  P6DIR |= BIT4+BIT5+BIT6+BIT7;     //列输出低，检索行
  P6OUT &=~(BIT4+BIT5+BIT6+BIT7);
  P6OUT |=BIT0+BIT1+BIT2+BIT3;     //使行上拉，开路时为高，若被按下则为低
  P6REN |= BIT0+BIT1+BIT2+BIT3;
  P6DIR &=~(BIT0+BIT1+BIT2+BIT3);
  if((P6IN&BIT3)==0) tem |=0x10;    //行号0001b
  if((P6IN&BIT2)==0) tem |=0x20;    //行号0010b
  if((P6IN&BIT1)==0) tem |=0x40;    //行号0100b
  if((P6IN&BIT0)==0) tem |=0x80;    //行号1000b
  readed=0;     //有新数据产生
}
void keyboard_init(void)            //初始化键盘引脚
{
  P6DIR |= BIT0+BIT1+BIT2+BIT3;     //行输出低
  P6OUT &=~(BIT0+BIT1+BIT2+BIT3);
  P2OUT |= BIT1;                    //使中断口上拉
  P2REN |= BIT1;
  P2DIR &=~BIT1;
  P2IFG &=~BIT1;        //清中断标志
  P2IES |= BIT1;        //触发方式：负跳变
  P2IE  |= BIT1;        //使能中断
   _EINT();             //开总中断
}
void keyboard_clear(void)
{
  tem=0x00;
}
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
  switch(P2IV)
  {
  case 0x04:          //P2.1脚中断发生
    {
      P2IFG &=~BIT1;     //清中断标志
      P2IE &=~ BIT1;     //边缘不稳定，为防止连续触发中断，按键防抖前关中断，
      long int t=160000;  //延时防抖，16MHz，延时约10ms
      while(t--);
      if((P2IN&BIT1)==0)  //确实按下时，执行键盘扫描
      {
        scan_key();
      }
      P6DIR |= BIT0+BIT1+BIT2+BIT3;   //准备下一次触发，行重新输出低
      P6OUT &=~(BIT0+BIT1+BIT2+BIT3);
      P6DIR |= BIT4+BIT5+BIT6+BIT7;   //列上拉
      P6OUT |=BIT4+BIT5+BIT6+BIT7;
      P6DIR &=~ (BIT4+BIT5+BIT6+BIT7);
      P2OUT |= BIT1;                  //再次配置外部中断口P2.1
      P2REN |= BIT1;
      P2DIR &=~BIT1;
      P2IFG &=~BIT1;
      P2IES |= BIT1;
      P2IE  |= BIT1;
    }break;
  default:break;
  }
}