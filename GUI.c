#include "msp430x54x.h"
#include "TFT.h"
#include "GUI.h"
#include "zifu8x12.h"
#include "math.h"
#include "CC.h"

void GUI_init(void)
{
  TFT_init();
}
void Fill_Window(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int color)
{
  int i,j,it,jt;
  it=x2-x1;
  jt=y2-y1;
  LCD_CS_0;
  Address_set(x1,y1,x2,y2);
  for(i=0;i<=it;i++)
  {
    for (j=0;j<=jt;j++)
    {
      Lcd_Write_Data(color);
    }
  }
  LCD_CS_1;
}
void Clear_Screen(void)
{
  Fill_Window(0,0,239,319,0xffff);
}
void Draw_Point(unsigned int x,unsigned int y,unsigned int color)
{
  LCD_CS_0;
  Address_set(x,y,x,y);
  Lcd_Write_Data(color);
  LCD_CS_1;
}
void Draw_Vline(unsigned int x,unsigned int y1,unsigned int y2,unsigned int color)
{
  Fill_Window(x,y1,x,y2,color);
}
void Draw_Hline(unsigned int x1,unsigned int x2,unsigned int y,unsigned int color)
{
  Fill_Window(x1,y,x2,y,color);
}
void Draw_Rectangle(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int color)
{
  Draw_Vline(x1,y1,y2,color);
  Draw_Vline(x2,y1,y2,color);
  Draw_Hline(x1,x2,y1,color);
  Draw_Hline(x1,x2,y2,color);
}

/********************************************************
* ���� Draw_Line()
      ���ò���ɭ��ķ(Bresenham)�㷨����
* ���ܣ�����������ֱ�ߡ�����Ӳ���ص㣬ʵ�ּ��١�
* ��ڲ�����x0       ֱ����������е�λ��
*         y0       ֱ����������е�λ��
*         x1     ֱ���յ������е�λ��
'       y1     ֱ���յ������е�λ��
* ���ڲ�����   ��
* ˵��������ʧ��ԭ����ָ����ַ������������Χ��
*********************************************************/
void Draw_Line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int color)
{
  signed int temp;
  signed int dx,dy;               //������㵽�յ�ĺᡢ����������ֵ
  signed int s1,s2,status,i;
  signed int Dx,Dy,sub;

  dx=x1-x0;
  if(dx>=0)                 //X�ķ��������ӵ�
    s1=1;
  else                     //X�ķ����ǽ��͵�
    s1=-1;
  dy=y1-y0;                 //�ж�Y�ķ��������ӻ��ǽ�����
  if(dy>=0)
    s2=1;
  else
    s2=-1;
    
  Dx=(x1-x0)*s1;             //����ᡢ�ݱ�־����ֵ�ľ���ֵ
  Dy=(y1-y0)*s2;
  if(Dy>Dx)                                
  {                         //��45�Ƚ�Ϊ�ֽ��ߣ�����Y����status=1,����X����status=0 
    temp=Dx;
    Dx=Dy;
    Dy=temp;
    status=1;
  } 
  else
    status=0;
  
  /********�жϴ�ֱ�ߺ�ˮƽ��********/
  if(dx==0)                   //������û����������һ����ֱ��
  {
	Draw_Vline(x0,y0,y1,color);
	return;
  }
  if(dy==0)                   //������û����������һ��ˮƽ��
  {
    Draw_Hline(x0,x1,y1,color);
    return;
  }
  
  
  /*********Bresenham�㷨������������ֱ��********/ 
    sub=(Dy<<1)-Dx;                 //��1���ж��¸����λ��
    for(i=0;i<Dx;i++)
    { 
      Draw_Point(x0, y0, color);           //���� 
      if(sub>=0)                               
      { 
        if(status==1)               //�ڿ���Y������xֵ��1
          x0+=s1; 
        else                     //�ڿ���X������yֵ��1               
          y0+=s2; 
        sub-=Dx<<1;                 //�ж����¸����λ�� 
      } 
      if(status==1)
        y0+=s2; 
      else       
        x0+=s1; 
      sub+=Dy<<1; 
    }
    Draw_Point(x1, y1, color);
}
void Draw_Circle(unsigned int x0,unsigned int y0,unsigned int r, unsigned int color)
{
  int x=0,y=r,f=0;  
  while(x<=y)   
  { 
    if ((x0+x<240)&&(x0+x>=0)&&(y0+y<320)&&(y0+y>=0))
        Draw_Point(x0+x,y0+y,color);    
    if ((x0+x<240)&&(x0+x>=0)&&(y0-y<320)&&(y0-y>=0))    	
        Draw_Point(x0+x,y0-y,color);    
    if ((x0-x<240)&&(x0-x>=0)&&(y0+y<320)&&(y0+y>=0))
        Draw_Point(x0-x,y0+y,color);    
    if ((x0-x<240)&&(x0-x>=0)&&(y0-y<320)&&(y0-y>=0))
        Draw_Point(x0-x,y0-y,color);    
    if ((x0+y<240)&&(x0+y>=0)&&(y0+x<320)&&(y0+x>=0))	    
        Draw_Point(x0+y,y0+x,color);    
    if ((x0+y<240)&&(x0+y>=0)&&(y0-x<320)&&(y0-x>=0))	    
        Draw_Point(x0+y,y0-x,color);    
    if ((x0-y<240)&&(x0-y>=0)&&(y0+x<320)&&(y0+x>=0))	    
        Draw_Point(x0-y,y0+x,color);    
    if ((x0-y<240)&&(x0-y>=0)&&(y0-x<320)&&(y0-x>=0))	    
        Draw_Point(x0-y,y0-x,color);    
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
/*
void Draw_Oval(unsigned int x, unsigned int y, unsigned int a, unsigned int b, unsigned int color) //�е��㷨������Բ
{
    unsigned int xc=300,yc=200;
    double d1,d2;
    x=0;y=b;
    d1=b*b+a*a*(-b+0.25);
    Draw_Point(x+300,y+200,color);
    Draw_Point(-x+300,y+200,color);
    Draw_Point(x+300,-y+200,color);
    Draw_Point(-x+300,-y+200,color);
    while(b*b*(x+1)<a*a*(y-0.5))
    {
      if(d1<0)
      {
        d1+=b*b*(2*x+3);
        x++;
      }
      else
      {
        d1+=b*b*(2*x+3)+a*a*(-2*y+2);
        x++;y--;
      }
      Draw_Point(x+xc,y+yc,color);
      Draw_Point(-x+xc,y+yc,color);
      Draw_Point(x+xc,-y+yc,color);
      Draw_Point(-x+xc,-y+yc,color);
    }
    d2=sqrt(b*(x+0.5))+a*(y-1)-a*b;
    while(y>0)
    {
      if(d2<0)
      {
        d2+=b*b*(2*x+2)+a*a*(-2*y+3);
        x++;
        y--;
      }
      else
      {
        d2+=a*a*(-2*y+3);
        y--;
      }
      Draw_Point(x+xc,y+yc,color);
      Draw_Point(-x+xc,y+yc,color);
      Draw_Point(x+xc,-y+yc,color);
      Draw_Point(-x+xc,-y+yc,color);
    }
}*/
//д�� �����ַ�
//��ָ��λ����ʾһ���ַ�(8*12��С)
//dcolorΪ������ɫ��gbcolorΪ������ɫ
void showzifu(unsigned int x,unsigned int y,unsigned char value,unsigned int dcolor,unsigned int bgcolor)	
{  
    unsigned char i,j;
    unsigned int temp=0;    
    LCD_CS_0;
    Address_set(x,y,x+7,y+11);  //��������      
	                    
    temp+=(value-32)*12;   //ȷ��Ҫ��ʾ��ֵ
                           //�����õ���ascii��  ǰ32��asciiû�д���zifu���� ����Ҫ��32
                           //���� ÿ���ַ���12���ֽ���ʾ �����ٳ���12  ���Ƕ�Ӧ����ʾλ���׵�ַ
    for(j=0;j<12;j++)
    {
        for(i=0;i<8;i++)		    //�Ⱥ�ɨ
        { 		     
                if((zifu[temp]&(1<<(7-i)))!=0)					//��1 ���� Ȼ���Ӧλ�������� 
                {
                    Lcd_Write_Data(dcolor);
                    //Draw_Point(x+i,y+j,dcolor);
                } 
                else
                {
                    Lcd_Write_Data(bgcolor);
                    //Draw_Point(x+i,y+j,bgcolor);
                }   
        }
        temp++;
     }
    LCD_CS_1;
}

void Draw_CC(unsigned int x,unsigned int y,unsigned char num, unsigned int dcolor, unsigned int bgcolor)//д����
{
  unsigned int i,j;
  LCD_CS_0;
  Address_set(x,y,x+16-1,y+16-1);
  for(  j=0; j<32 ; j++)
    for( i=0; i<8; i++)
    {
      if ((CC[num][j] & (1<<(7-i)))!=0)
        Lcd_Write_Data(dcolor);
      else
        Lcd_Write_Data(bgcolor);
    }
  LCD_CS_1;
}