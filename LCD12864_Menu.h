#ifndef LCD12864_Menu_H_
#define LCD12864_Menu_H_
extern unsigned char LCD12864_Vector;
extern void LCD12864_Menu_init(void);
extern void LCD12864_Menu_StartMenu(void);
extern void LCD12864_Menu_1(void);
extern void LCD12864_Menu_2(void);
extern void LCD12864_Menu_1_1(void);
extern void LCD12864_Menu_1_2(void);
extern int  LCD12864_CreatInputBox(unsigned char L,unsigned char R,unsigned char Enter,unsigned char Back);  //L为左端地址，R为右端地址，Enter为确认字符，Back为取消字符。返回自然数或 -1(标志执行返回操作)
extern void Display(int num);
#endif 
