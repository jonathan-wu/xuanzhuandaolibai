#include "msp430x54x.h"
#include "keyboard.h"
unsigned char read_key(void)  //�������ֵ,�����ַ�
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
void scan_key(void)           //ɨ����̣���ȡ��������ֵ
{
  tem=0x00;                         //Ĭ��Ϊ0-0
  P6DIR |= BIT0+BIT1+BIT2+BIT3;     //������ͣ�������
  P6OUT &=~(BIT0+BIT1+BIT2+BIT3);
  P6DIR &=~(BIT4+BIT5+BIT6+BIT7);
  if((P6IN&BIT7)==0) tem |=0x01;    //��1Ϊ�ͣ���ʾ�������а��������£���¼�к�0001b
  if((P6IN&BIT6)==0) tem |=0x02;    //�к�0010b
  if((P6IN&BIT5)==0) tem |=0x04;    //�к�0100b
  if((P6IN&BIT4)==0) tem |=0x08;    //�к�1000b
  P6DIR |= BIT4+BIT5+BIT6+BIT7;     //������ͣ�������
  P6OUT &=~(BIT4+BIT5+BIT6+BIT7);
  P6OUT |=BIT0+BIT1+BIT2+BIT3;     //ʹ����������·ʱΪ�ߣ�����������Ϊ��
  P6REN |= BIT0+BIT1+BIT2+BIT3;
  P6DIR &=~(BIT0+BIT1+BIT2+BIT3);
  if((P6IN&BIT3)==0) tem |=0x10;    //�к�0001b
  if((P6IN&BIT2)==0) tem |=0x20;    //�к�0010b
  if((P6IN&BIT1)==0) tem |=0x40;    //�к�0100b
  if((P6IN&BIT0)==0) tem |=0x80;    //�к�1000b
  readed=0;     //�������ݲ���
}
void keyboard_init(void)            //��ʼ����������
{
  P6DIR |= BIT0+BIT1+BIT2+BIT3;     //�������
  P6OUT &=~(BIT0+BIT1+BIT2+BIT3);
  P2OUT |= BIT1;                    //ʹ�жϿ�����
  P2REN |= BIT1;
  P2DIR &=~BIT1;
  P2IFG &=~BIT1;        //���жϱ�־
  P2IES |= BIT1;        //������ʽ��������
  P2IE  |= BIT1;        //ʹ���ж�
   _EINT();             //�����ж�
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
  case 0x04:          //P2.1���жϷ���
    {
      P2IFG &=~BIT1;     //���жϱ�־
      P2IE &=~ BIT1;     //��Ե���ȶ���Ϊ��ֹ���������жϣ���������ǰ���жϣ�
      long int t=160000;  //��ʱ������16MHz����ʱԼ10ms
      while(t--);
      if((P2IN&BIT1)==0)  //ȷʵ����ʱ��ִ�м���ɨ��
      {
        scan_key();
      }
      P6DIR |= BIT0+BIT1+BIT2+BIT3;   //׼����һ�δ����������������
      P6OUT &=~(BIT0+BIT1+BIT2+BIT3);
      P6DIR |= BIT4+BIT5+BIT6+BIT7;   //������
      P6OUT |=BIT4+BIT5+BIT6+BIT7;
      P6DIR &=~ (BIT4+BIT5+BIT6+BIT7);
      P2OUT |= BIT1;                  //�ٴ������ⲿ�жϿ�P2.1
      P2REN |= BIT1;
      P2DIR &=~BIT1;
      P2IFG &=~BIT1;
      P2IES |= BIT1;
      P2IE  |= BIT1;
    }break;
  default:break;
  }
}