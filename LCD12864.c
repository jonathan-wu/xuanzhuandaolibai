#include"msp430x54x.h"
#include"LCD12864.h"
#include"UCS.h"
//#include"delay.h"

//用户可用函数：LCD12864_DrawPoint();LCD12864_drawLine();DisplayCgrom();

//需要放在开总中断之后
void LCD12864_init()    //初始化函数：初始化引脚，初始化设备
{
    P9DIR |= BIT0+BIT1+BIT2+BIT3+BIT4;
    P10SEL = 0x00;
    DataOut;
    PSB_SET;
    delay_ms(5);
    DataOut;
    OutData = 0;
    RST_SET;
    //以上引脚初始化
    LCD12864_WriteCmd(FUN_MODE);   //显示模式设置
    delay_ms(5);  
    LCD12864_WriteCmd(FUN_MODE);   //显示模式设置
    delay_ms(5); 
    LCD12864_WriteCmd(DISPLAY_ON);   //显示开
    delay_ms(5);
    LCD12864_WriteCmd(CLEAR_SCREEN);   //清屏
    delay_ms(5); 
}
void LCD12864_CheckBusy()       //检测是否忙，是则等待
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
void LCD12864_WriteCmd(char cmd)  //写命令
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
void LCD12864_WriteData(char dat) //写数据
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
char LCD12864_ReadData(void) //读数据
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
void LCD12864_DisplayStr(unsigned char x,unsigned char y,unsigned char *c)  //向第x(0~3)行，y(0~7)列写字符串,每列可显示1汉字或2西文字符
{
  LCD12864_WriteCmd(0x30);//关闭扩充指令集
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
    LCD12864_WriteCmd(0x34); //打开扩充指令集
    for (i=0;i<32;i++)
    {
      LCD12864_WriteCmd(0x80+i);//先写Y地址(行数)
      LCD12864_WriteCmd(0x80); //再写X地址(列数)
      for (j=0;j<32;j++)
        LCD12864_WriteData(0x00);
    }
    LCD12864_WriteCmd(0x30);//关闭扩充指令集
}
void LCD12864_ClearScreen(void) 
{
  LCD12864_WriteCmd(CLEAR_SCREEN);
  delay_ms(5);
}
void DisplayCgrom(unsigned char addr,unsigned char *hz)   //向起始地址addr写汉字字符串的指针hz
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
void LCD12864_DisplayChar(unsigned char addr,unsigned char hz)   //向地址addr写汉字字符hz
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
void LCD12864_DrawPoint(unsigned char x,unsigned char y,unsigned char type)//画点到显存,x(0~127),y(0~63)、0为白色，1 为黑色，2为取反
{
 unsigned char X,Y,k;  //X存储行地址，Y存储列地址、k存储点在字中的位置从左至右为0~15
 unsigned char DH,DL;  //存放读出数据的高字节和低字节
  if(y<64 && x<128)
  { 
    if(y < 32)     //确定所画点的地址行与列地址
    {
     X = 0x80 + (x >> 4);
     Y = 0x80 + y; 
    }
    else
    {
     X = 0x88 + (x >> 4);
     Y = 0x80 + (y - 32);
    }     
    LCD12864_WriteCmd(0x36);  //开启扩展指令，关闭绘图显示
    LCD12864_WriteCmd(Y);  //写入所确定的点的行位地址  
    LCD12864_WriteCmd(X);   //写入所确定的点的列字地址
    DH = LCD12864_ReadData(); //假读
    DH = LCD12864_ReadData();    //读高字节
    DL = LCD12864_ReadData(); //读低字节
    k = x % 16;          //余数为点在字中的位置
    //画点
    switch(type){     //画点类型，1黑或0白或2取反
     case 0:
      if(k<8)DH &= ~(0x01 << (7 - k));  //点在高字节
      else DL &= ~(0x01 << (7 - (k % 8)));  //点在低字节
      break;
     case 1:
      if(k < 8)DH |= (0x01 << (7 - k));  //修改该点同时保持其他位不变
      else DL |= (0x01 << (7 - (k % 8))); //修改该点同时保持其他位不变
      break;
     case 2:
      if(k < 8)DH ^= (0x01 << (7 - k));  //修改该点同时保持其他位不变
      else DL ^= (0x01 << (7 - (k % 8)));   //修改该点同时保持其他位不变
      break;
     default:
       break;  
    }
    LCD12864_WriteCmd(Y);     //写行位地址
    LCD12864_WriteCmd(X);     //写列字地址
    LCD12864_WriteData(DH);  //将高字节数据写回
    LCD12864_WriteData(DL);  //将低字节数据写回
    LCD12864_WriteCmd(0x30);  //转回普通指令
  }
}
void LCD12864_DrawLine(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char type)
{
  signed int temp;
  signed int dx,dy;               //定义起点到终点的横、纵坐标增加值
  signed char s1,s2,status,i;
  signed int Dx,Dy,sub;
  dx=x2-x1;
  if(dx>=0)s1=1;              //X的方向是增加的
  else s1=-1;                //X的方向是降低的
  dy=y2-y1;                 //判断Y的方向是增加还是降到的
  if(dy>=0)s2=1;
  else s2=-1;
  Dx=(x2-x1)*s1;             //计算横、纵标志增加值的绝对值
  Dy=(y2-y1)*s2;
  if(Dy>Dx)                                
  {                         //以45度角为分界线，靠进Y轴是status=1,靠近X轴是status=0 
    temp=Dx;
    Dx=Dy;
    Dy=temp;
    status=1;
  } 
  else status=0;
  if(dx==0)                   //横向上没有增量，画一条垂直线
  {
    for(i=y1;i!=y2;i+=s2) LCD12864_DrawPoint(x1, i, type);
    return;
  }
  if(dy==0)                   //纵向上没有增量，画一条水平线
  {
    for(i=x1;i!=x2;i+=s1)
    LCD12864_DrawPoint(i, y1, type);
    return;
  }
  sub=(Dy<<1)-Dx;                 //第1次判断下个点的位置
  for(i=0;i<Dx;i++)
  { 
    LCD12864_DrawPoint(x1, y1, type);           //画点 
    if(sub>=0)                               
    { 
      if(status==1)x1+=s1;             //在靠近Y轴区，x值加1 
      else y1+=s2;                    //在靠近X轴区，y值加1                
      sub-=Dx<<1;                 //判断下下个点的位置 
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