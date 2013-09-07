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
* 名称 Draw_Line()
      采用布兰森汉姆(Bresenham)算法画线
* 功能：任意两点间的直线。根据硬件特点，实现加速。
* 入口参数：x0       直线起点所在行的位置
*         y0       直线起点所在列的位置
*         x1     直线终点所在行的位置
'       y1     直线终点所在列的位置
* 出口参数：   无
* 说明：操作失败原因是指定地址超出缓冲区范围。
*********************************************************/
void Draw_Line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int color)
{
  signed int temp;
  signed int dx,dy;               //定义起点到终点的横、纵坐标增加值
  signed int s1,s2,status,i;
  signed int Dx,Dy,sub;

  dx=x1-x0;
  if(dx>=0)                 //X的方向是增加的
    s1=1;
  else                     //X的方向是降低的
    s1=-1;
  dy=y1-y0;                 //判断Y的方向是增加还是降到的
  if(dy>=0)
    s2=1;
  else
    s2=-1;
    
  Dx=(x1-x0)*s1;             //计算横、纵标志增加值的绝对值
  Dy=(y1-y0)*s2;
  if(Dy>Dx)                                
  {                         //以45度角为分界线，靠进Y轴是status=1,靠近X轴是status=0 
    temp=Dx;
    Dx=Dy;
    Dy=temp;
    status=1;
  } 
  else
    status=0;
  
  /********判断垂直线和水平线********/
  if(dx==0)                   //横向上没有增量，画一条垂直线
  {
	Draw_Vline(x0,y0,y1,color);
	return;
  }
  if(dy==0)                   //纵向上没有增量，画一条水平线
  {
    Draw_Hline(x0,x1,y1,color);
    return;
  }
  
  
  /*********Bresenham算法画任意两点间的直线********/ 
    sub=(Dy<<1)-Dx;                 //第1次判断下个点的位置
    for(i=0;i<Dx;i++)
    { 
      Draw_Point(x0, y0, color);           //画点 
      if(sub>=0)                               
      { 
        if(status==1)               //在靠近Y轴区，x值加1
          x0+=s1; 
        else                     //在靠近X轴区，y值加1               
          y0+=s2; 
        sub-=Dx<<1;                 //判断下下个点的位置 
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
void Draw_Oval(unsigned int x, unsigned int y, unsigned int a, unsigned int b, unsigned int color) //中点算法绘制椭圆
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
//写入 单个字符
//在指定位置显示一个字符(8*12大小)
//dcolor为内容颜色，gbcolor为背静颜色
void showzifu(unsigned int x,unsigned int y,unsigned char value,unsigned int dcolor,unsigned int bgcolor)	
{  
    unsigned char i,j;
    unsigned int temp=0;    
    LCD_CS_0;
    Address_set(x,y,x+7,y+11);  //设置区域      
	                    
    temp+=(value-32)*12;   //确定要显示的值
                           //这里用的是ascii表  前32个ascii没有存入zifu库里 所以要减32
                           //并且 每个字符用12个字节显示 所以再乘以12  就是对应的显示位的首地址
    for(j=0;j<12;j++)
    {
        for(i=0;i<8;i++)		    //先横扫
        { 		     
                if((zifu[temp]&(1<<(7-i)))!=0)					//将1 左移 然后对应位进行相与 
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

void Draw_CC(unsigned int x,unsigned int y,unsigned char num, unsigned int dcolor, unsigned int bgcolor)//写汉字
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