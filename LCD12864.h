#ifndef LCD12864_H_
#define LCD12864_H_
/*12864应用指令*/
#define CLEAR_SCREEN 0x01      //清屏指令：清屏且AC值为00H
#define AC_INIT  0x02      //将AC设置为00H。且游标移到原点位置
#define CURSE_ADD 0x06      //设定游标移到方向及图像整体移动方向（默认游标右移，图像整体不动）
#define FUN_MODE 0x30      //工作模式：8位基本指令集
#define DISPLAY_ON 0x0c      //显示开,显示游标，且游标位置反白
#define DISPLAY_OFF 0x08      //显示关
#define CURSE_DIR 0x14      //游标向右移动:AC=AC+1
#define SET_CG_AC 0x40      //设置AC，范围为：00H~3FH
#define SET_DD_AC 0x80

/*12864引脚定义*/
#define RS_CLR  P9OUT &=~BIT0        //RS置低
#define RS_SET  P9OUT |= BIT0         //RS置高
#define RW_CLR  P9OUT &=~BIT1        //RW置低
#define RW_SET  P9OUT |= BIT1         //RW置高
#define EN_CLR  P9OUT &=~BIT2        //E置低
#define EN_SET  P9OUT |= BIT2         //E置高
#define PSB_CLR P9OUT &=~BIT3        //PSB置低，串口方式
#define PSB_SET P9OUT |= BIT3         //PSB置高，并口方式
#define RST_CLR P9OUT &=~BIT4        //RST置低
#define RST_SET P9OUT |= BIT4         //RST置高
#define DataOut P10DIR |= 0xFF         //P9口为数据口
#define DataIn  P10DIR &= ~0xFF
#define InData  P10IN
#define OutData P10OUT
#define Data_REN P10REN
extern void LCD12864_CheckBusy(void);
extern void LCD12864_WriteCmd(char cmd);  //写命令
extern void LCD12864_ClearScreen(void);
extern void LCD12864_WriteData(char cmd);
extern void LCD12864_ClearGRAM(void); //清显存
extern void DisplayCgrom(unsigned char addr,unsigned char *hz);
extern void LCD12864_init();
extern void LCD12864_DisplayNum(unsigned char addr,int num);
extern void LCD12864_DisplayChar(unsigned char addr,unsigned char hz);
extern void LCD12864_DisplayStr(unsigned char x,unsigned char y,unsigned char *c);  //向第x(0~3)行，y(0~7)列写字符串,每列可显示1汉字或2西文字符
extern void LCD12864_DrawPoint(unsigned char x,unsigned char y,unsigned char type);  //画点到显存,x(0~127),y(0~63)、0为白色，1 为黑色，2为取反
extern void LCD12864_DrawLine(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char type);
extern void LCD12864_DrawCircle(unsigned char x0,unsigned char y0,unsigned char r, unsigned char type);
extern void LCD12864_DrawRectangle(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char type);
#endif