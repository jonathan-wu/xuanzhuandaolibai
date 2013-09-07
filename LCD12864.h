#ifndef LCD12864_H_
#define LCD12864_H_
/*12864Ӧ��ָ��*/
#define CLEAR_SCREEN 0x01      //����ָ�������ACֵΪ00H
#define AC_INIT  0x02      //��AC����Ϊ00H�����α��Ƶ�ԭ��λ��
#define CURSE_ADD 0x06      //�趨�α��Ƶ�����ͼ�������ƶ�����Ĭ���α����ƣ�ͼ�����岻����
#define FUN_MODE 0x30      //����ģʽ��8λ����ָ�
#define DISPLAY_ON 0x0c      //��ʾ��,��ʾ�α꣬���α�λ�÷���
#define DISPLAY_OFF 0x08      //��ʾ��
#define CURSE_DIR 0x14      //�α������ƶ�:AC=AC+1
#define SET_CG_AC 0x40      //����AC����ΧΪ��00H~3FH
#define SET_DD_AC 0x80

/*12864���Ŷ���*/
#define RS_CLR  P9OUT &=~BIT0        //RS�õ�
#define RS_SET  P9OUT |= BIT0         //RS�ø�
#define RW_CLR  P9OUT &=~BIT1        //RW�õ�
#define RW_SET  P9OUT |= BIT1         //RW�ø�
#define EN_CLR  P9OUT &=~BIT2        //E�õ�
#define EN_SET  P9OUT |= BIT2         //E�ø�
#define PSB_CLR P9OUT &=~BIT3        //PSB�õͣ����ڷ�ʽ
#define PSB_SET P9OUT |= BIT3         //PSB�øߣ����ڷ�ʽ
#define RST_CLR P9OUT &=~BIT4        //RST�õ�
#define RST_SET P9OUT |= BIT4         //RST�ø�
#define DataOut P10DIR |= 0xFF         //P9��Ϊ���ݿ�
#define DataIn  P10DIR &= ~0xFF
#define InData  P10IN
#define OutData P10OUT
#define Data_REN P10REN
extern void LCD12864_CheckBusy(void);
extern void LCD12864_WriteCmd(char cmd);  //д����
extern void LCD12864_ClearScreen(void);
extern void LCD12864_WriteData(char cmd);
extern void LCD12864_ClearGRAM(void); //���Դ�
extern void DisplayCgrom(unsigned char addr,unsigned char *hz);
extern void LCD12864_init();
extern void LCD12864_DisplayNum(unsigned char addr,int num);
extern void LCD12864_DisplayChar(unsigned char addr,unsigned char hz);
extern void LCD12864_DisplayStr(unsigned char x,unsigned char y,unsigned char *c);  //���x(0~3)�У�y(0~7)��д�ַ���,ÿ�п���ʾ1���ֻ�2�����ַ�
extern void LCD12864_DrawPoint(unsigned char x,unsigned char y,unsigned char type);  //���㵽�Դ�,x(0~127),y(0~63)��0Ϊ��ɫ��1 Ϊ��ɫ��2Ϊȡ��
extern void LCD12864_DrawLine(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char type);
extern void LCD12864_DrawCircle(unsigned char x0,unsigned char y0,unsigned char r, unsigned char type);
extern void LCD12864_DrawRectangle(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char type);
#endif