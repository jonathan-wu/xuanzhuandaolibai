#include"msp430x54x.h"
#include"LCD12864.h"
#include"UCS.h"
//#include"delay.h"

//�û����ú�����LCD12864_DrawPoint();LCD12864_drawLine();DisplayCgrom();

//��Ҫ���ڿ����ж�֮��
void LCD12864_init()    //��ʼ����������ʼ�����ţ���ʼ���豸
{
    P9DIR |= BIT0+BIT1+BIT2+BIT3+BIT4;
    P10SEL = 0x00;
    DataOut;
    PSB_SET;
    delay_ms(5);
    DataOut;
    OutData = 0;
    RST_SET;
    //�������ų�ʼ��
    LCD12864_WriteCmd(FUN_MODE);   //��ʾģʽ����
    delay_ms(5);  
    LCD12864_WriteCmd(FUN_MODE);   //��ʾģʽ����
    delay_ms(5); 
    LCD12864_WriteCmd(DISPLAY_ON);   //��ʾ��
    delay_ms(5);
    LCD12864_WriteCmd(CLEAR_SCREEN);   //����
    delay_ms(5); 
}
void LCD12864_CheckBusy()       //����Ƿ�æ������ȴ�
{
  unsigned char read;
  DataIn;
  do{
   RS_CLR;
   RW_SET;
   EN_SET;
   _NOP();
   read=InData;
   EN_CLR;
  }while((read&0x80)!=0);
}
void LCD12864_WriteCmd(char cmd)  //д����
{
  LCD12864_CheckBusy();
  RS_CLR;
  RW_CLR;
  EN_SET;
  DataOut;  
  OutData = cmd;
  //delay_ms(5);
  EN_CLR;
}
void LCD12864_WriteData(char dat) //д����
{
  LCD12864_CheckBusy();
  RS_SET;
  RW_CLR;
  EN_SET;
  DataOut;
  OutData = dat;
  //delay_ms(5);
  EN_CLR;
}
char LCD12864_ReadData(void) //������
{
  char dat;
  LCD12864_CheckBusy();
  RS_SET;
  RW_SET;
  EN_SET;
  DataIn; 
  dat = InData;
  EN_CLR;
  return dat;
}
void LCD12864_DisplayStr(unsigned char x,unsigned char y,unsigned char *c)  //���x(0~3)�У�y(0~7)��д�ַ���,ÿ�п���ʾ1���ֻ�2�����ַ�
{
  LCD12864_WriteCmd(0x30);//�ر�����ָ�
  switch(x)
  {
  case 0:DisplayCgrom(0x80+y,c);break;
  case 1:DisplayCgrom(0x90+y,c);break;
  case 2:DisplayCgrom(0x88+y,c);break;
  case 3:DisplayCgrom(0x98+y,c);break;
  default:break;
  }
}

void LCD12864_ClearGRAM(void)
{
    char i,j;
    LCD12864_WriteCmd(0x34); //������ָ�
    for (i=0;i<32;i++)
    {
      LCD12864_WriteCmd(0x80+i);//��дY��ַ(����)
      LCD12864_WriteCmd(0x80); //��дX��ַ(����)
      for (j=0;j<32;j++)
        LCD12864_WriteData(0x00);
    }
    LCD12864_WriteCmd(0x30);//�ر�����ָ�
}
void LCD12864_ClearScreen(void) 
{
  LCD12864_WriteCmd(CLEAR_SCREEN);
  delay_ms(5);
}
void DisplayCgrom(unsigned char addr,unsigned char *hz)   //����ʼ��ַaddrд�����ַ�����ָ��hz
{
  LCD12864_WriteCmd(addr);
  delay_ms(5);  
  while(*hz != '\0')
  {
    LCD12864_WriteData(*hz);
    hz++;
    delay_ms(5); 
  }
}
void LCD12864_DisplayChar(unsigned char addr,unsigned char hz)   //���ַaddrд�����ַ�hz
{
  LCD12864_WriteCmd(addr);
  delay_ms(5);  
  LCD12864_WriteData(hz);
  delay_ms(5); 
}
void LCD12864_DisplayNum(unsigned char addr,int num)
{
  unsigned char str[7]={0};
  int i,t=0;
  if(num<0) t=1,num=-num;
  for(i=5;num>0;i--)
  {
    str[i]=num%10+'0';
    num/=10;
  }
  if(t) str[i]='-',DisplayCgrom(addr,str+i);
  else DisplayCgrom(addr,str+i+1);
}
void LCD12864_DrawPoint(unsigned char x,unsigned char y,unsigned char type)//���㵽�Դ�,x(0~127),y(0~63)��0Ϊ��ɫ��1 Ϊ��ɫ��2Ϊȡ��
{
 unsigned char X,Y,k;  //X�洢�е�ַ��Y�洢�е�ַ��k�洢�������е�λ�ô�������Ϊ0~15
 unsigned char DH,DL;  //��Ŷ������ݵĸ��ֽں͵��ֽ�
  if(y<64 && x<128)
  { 
    if(y < 32)     //ȷ��������ĵ�ַ�����е�ַ
    {
     X = 0x80 + (x >> 4);
     Y = 0x80 + y; 
    }
    else
    {
     X = 0x88 + (x >> 4);
     Y = 0x80 + (y - 32);
    }     
    LCD12864_WriteCmd(0x36);  //������չָ��رջ�ͼ��ʾ
    LCD12864_WriteCmd(Y);  //д����ȷ���ĵ����λ��ַ  
    LCD12864_WriteCmd(X);   //д����ȷ���ĵ�����ֵ�ַ
    DH = LCD12864_ReadData(); //�ٶ�
    DH = LCD12864_ReadData();    //�����ֽ�
    DL = LCD12864_ReadData(); //�����ֽ�
    k = x % 16;          //����Ϊ�������е�λ��
    //����
    switch(type){     //�������ͣ�1�ڻ�0�׻�2ȡ��
     case 0:
      if(k<8)DH &= ~(0x01 << (7 - k));  //���ڸ��ֽ�
      else DL &= ~(0x01 << (7 - (k % 8)));  //���ڵ��ֽ�
      break;
     case 1:
      if(k < 8)DH |= (0x01 << (7 - k));  //�޸ĸõ�ͬʱ��������λ����
      else DL |= (0x01 << (7 - (k % 8))); //�޸ĸõ�ͬʱ��������λ����
      break;
     case 2:
      if(k < 8)DH ^= (0x01 << (7 - k));  //�޸ĸõ�ͬʱ��������λ����
      else DL ^= (0x01 << (7 - (k % 8)));   //�޸ĸõ�ͬʱ��������λ����
      break;
     default:
       break;  
    }
    LCD12864_WriteCmd(Y);     //д��λ��ַ
    LCD12864_WriteCmd(X);     //д���ֵ�ַ
    LCD12864_WriteData(DH);  //�����ֽ�����д��
    LCD12864_WriteData(DL);  //�����ֽ�����д��
    LCD12864_WriteCmd(0x30);  //ת����ָͨ��
  }
}
void LCD12864_DrawLine(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char type)
{
  signed int temp;
  signed int dx,dy;               //������㵽�յ�ĺᡢ����������ֵ
  signed char s1,s2,status,i;
  signed int Dx,Dy,sub;
  dx=x2-x1;
  if(dx>=0)s1=1;              //X�ķ��������ӵ�
  else s1=-1;                //X�ķ����ǽ��͵�
  dy=y2-y1;                 //�ж�Y�ķ��������ӻ��ǽ�����
  if(dy>=0)s2=1;
  else s2=-1;
  Dx=(x2-x1)*s1;             //����ᡢ�ݱ�־����ֵ�ľ���ֵ
  Dy=(y2-y1)*s2;
  if(Dy>Dx)                                
  {                         //��45�Ƚ�Ϊ�ֽ��ߣ�����Y����status=1,����X����status=0 
    temp=Dx;
    Dx=Dy;
    Dy=temp;
    status=1;
  } 
  else status=0;
  if(dx==0)                   //������û����������һ����ֱ��
  {
    for(i=y1;i!=y2;i+=s2) LCD12864_DrawPoint(x1, i, type);
    return;
  }
  if(dy==0)                   //������û����������һ��ˮƽ��
  {
    for(i=x1;i!=x2;i+=s1)
    LCD12864_DrawPoint(i, y1, type);
    return;
  }
  sub=(Dy<<1)-Dx;                 //��1���ж��¸����λ��
  for(i=0;i<Dx;i++)
  { 
    LCD12864_DrawPoint(x1, y1, type);           //���� 
    if(sub>=0)                               
    { 
      if(status==1)x1+=s1;             //�ڿ���Y������xֵ��1 
      else y1+=s2;                    //�ڿ���X������yֵ��1                
      sub-=Dx<<1;                 //�ж����¸����λ�� 
    } 
    if(status==1)y1+=s2; 
    else x1+=s1; 
    sub+=Dy<<1; 
  } 
  LCD12864_DrawPoint(x2,y2,type);
}
void LCD12864_DrawRectangle(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char type)
{
  LCD12864_DrawLine(x1,y1,x2,y1,type);
  LCD12864_DrawLine(x1,y1,x1,y2,type);
  LCD12864_DrawLine(x2,y1,x2,y2,type);
  LCD12864_DrawLine(x1,y2,x2,y2,type);
}
void LCD12864_DrawCircle(unsigned char x0,unsigned char y0,unsigned char r, unsigned char type)
{
  int x=0,y=r,f=0;  
  while(x<=y)   
  {    
    LCD12864_DrawPoint(x0+x,y0+y,type);    
    LCD12864_DrawPoint(x0+x,y0-y,type);    
    LCD12864_DrawPoint(x0-x,y0+y,type);    
    LCD12864_DrawPoint(x0-x,y0-y,type);    
    LCD12864_DrawPoint(x0+y,y0+x,type);    
    LCD12864_DrawPoint(x0+y,y0-x,type);    
    LCD12864_DrawPoint(x0-y,y0+x,type);    
    LCD12864_DrawPoint(x0-y,y0-x,type);    
    if(f<=0)     
    {      
      f=f+2*x+1;      
      x++;     
    }     
    else      
    {       
      f=f-2*y+1;       
      y--;      
    }   
  }
}