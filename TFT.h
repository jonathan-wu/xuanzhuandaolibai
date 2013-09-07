#ifndef TFT_H_
#define TFT_H_
#define  LCD_DataPort PEOUT
#define LCD_RS_0  P1OUT &=~BIT0   //数据/命令切换
#define LCD_RS_1  P1OUT |= BIT0
#define LCD_WR_0  P1OUT &=~BIT1	  //写控制
#define LCD_WR_1  P1OUT |= BIT1
#define LCD_RD_0  P1OUT &=~BIT2   //读控制
#define LCD_RD_1  P1OUT |= BIT2
#define LCD_CS_0  P1OUT &=~BIT3   //片选	
#define LCD_CS_1  P1OUT |= BIT3
#define LCD_REST_0  P1OUT &=~BIT4 //复位   
#define LCD_REST_1  P1OUT |= BIT4
extern void TFT_init(void);
extern void Lcd_Pin_init(void);
extern void Lcd_Init(void);
extern void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
extern void Lcd_Write_Com_Data(int com,int val);
extern void Lcd_Write_Data(int Val);
extern void Lcd_Write_Com(int Val);
extern void LCD_Writ_Bus(int Val);
#endif
