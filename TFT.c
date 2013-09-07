#include "msp430x54x.h"
#include "UCS.h"
#include "TFT.h"
void TFT_init(void)
{
  Lcd_Pin_init();
  Lcd_Init();
}
void Lcd_Pin_init(void)
{
  P1DIR |= BIT0+BIT1+BIT2+BIT3+BIT4;
  P1DS  |= BIT0+BIT1+BIT2+BIT3+BIT4;
  P9DIR = 0xff;
  P10DIR = 0xff;
  P9DS   = 0xff;
  P10DS   = 0xff;  
  P1OUT &=~(BIT0+BIT1+BIT2+BIT3+BIT4);
  P9OUT=0x00;
  P10OUT=0x00;
  delay_us(10);
}
void Lcd_Init(void)
{
  LCD_REST_1;
  delay_us(5);	
  LCD_REST_0;
  delay_us(5);
  LCD_REST_1;
  LCD_CS_1;
  LCD_RD_1;
  LCD_WR_1;
  delay_us(5);
  LCD_CS_0;  //打开片选使能
  Lcd_Write_Com_Data(0x00,0x0000);		
  Lcd_Write_Com_Data(0x00,0x0000);		
  Lcd_Write_Com_Data(0x00,0x0000);	
  Lcd_Write_Com_Data(0x00,0x0001);	
  Lcd_Write_Com_Data(0xA4,0x0001);		
  delay_us(10); 
  Lcd_Write_Com_Data(0x60,0x2700);			
  Lcd_Write_Com_Data(0x08,0x0808);		
  Lcd_Write_Com_Data(0x30,0x0214);
  Lcd_Write_Com_Data(0x31,0x3715);
  Lcd_Write_Com_Data(0x32,0x0604);
  Lcd_Write_Com_Data(0x33,0x0E16);
  Lcd_Write_Com_Data(0x34,0x2211);
  Lcd_Write_Com_Data(0x35,0x1500);
  Lcd_Write_Com_Data(0x36,0x8507);
  Lcd_Write_Com_Data(0x37,0x1407);
  Lcd_Write_Com_Data(0x38,0x1403);
  Lcd_Write_Com_Data(0x39,0x0020);
  Lcd_Write_Com_Data(0x90,0x0015);
  Lcd_Write_Com_Data(0x10,0x0410);
  Lcd_Write_Com_Data(0x11,0x0237);
  Lcd_Write_Com_Data(0x29,0x0046);
  Lcd_Write_Com_Data(0x2A,0x0046);
  Lcd_Write_Com_Data(0x07,0x0000);
  Lcd_Write_Com_Data(0x12,0x0189);
  Lcd_Write_Com_Data(0x13,0x1100);
  delay_us(150);
  Lcd_Write_Com_Data(0x12,0x01B9);
  Lcd_Write_Com_Data(0x01,0x0100);
  Lcd_Write_Com_Data(0x02,0x0200);
  Lcd_Write_Com_Data(0x03,0x1030);
  Lcd_Write_Com_Data(0x09,0x0001);
  Lcd_Write_Com_Data(0x0A,0x0000);
  Lcd_Write_Com_Data(0x0D,0x0000);
  Lcd_Write_Com_Data(0x0E,0x0030);
  Lcd_Write_Com_Data(0x50,0x0000);
  Lcd_Write_Com_Data(0x51,0x00EF);
  Lcd_Write_Com_Data(0x52,0x0000);
  Lcd_Write_Com_Data(0x53,0x013F);
  Lcd_Write_Com_Data(0x61,0x0001);
  Lcd_Write_Com_Data(0x6A,0x0000);
  Lcd_Write_Com_Data(0x80,0x0000);
  Lcd_Write_Com_Data(0x81,0x0000);
  Lcd_Write_Com_Data(0x82,0x005F);
  Lcd_Write_Com_Data(0x92,0x0100);
  Lcd_Write_Com_Data(0x93,0x0701);
  delay_us(80);
  Lcd_Write_Com_Data(0x07,0x0100);
  Lcd_Write_Com_Data(0x20,0x0000);
  Lcd_Write_Com_Data(0x21,0x0000);
  Lcd_Write_Com(0x0022);
  LCD_CS_1;  //关闭片选使能
}
void LCD_Writ_Bus(int Val)   //并行数据写入函数
{
    LCD_DataPort=Val;	
   // LCD_DataPortL=VL;		
    LCD_WR_0;
    LCD_WR_1; 
}



void Lcd_Write_Com(int Val)	 //发送命令-8位参数
{	
    LCD_RS_0;
    LCD_Writ_Bus(Val);
}
void Lcd_Write_Data(int Val) //发送数据-8位参数
{
    LCD_RS_1;
    LCD_Writ_Bus(Val);
}
void Lcd_Write_Com_Data(int com,int val)		   //发送数据命令
{
    Lcd_Write_Com(com);
    Lcd_Write_Data(val);
}

//设置坐标范围		与tft驱动IC有关
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
  Lcd_Write_Com(0x0050);Lcd_Write_Data(x1);//0x0050~0x0053 windows control
  Lcd_Write_Com(0x0051);Lcd_Write_Data(x2);
  Lcd_Write_Com(0x0052);Lcd_Write_Data(y1);
  Lcd_Write_Com(0x0053);Lcd_Write_Data(y2);  
  Lcd_Write_Com(0x0020);Lcd_Write_Data(x1);	  
  Lcd_Write_Com(0x0021);Lcd_Write_Data(y1); 
  Lcd_Write_Com(0x0022);							 
}