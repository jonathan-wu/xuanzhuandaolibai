#ifndef TFT_Menu_H_
#define TFT_Menu_H_
extern unsigned char TFT_Vector;
extern void TFT_Menu_init(void);
extern void TFT_Menu_StartMenu(void);
extern void TFT_Menu_1(void);
extern void TFT_Menu_2(void);
extern void TFT_Menu_1_1(void);
extern void TFT_Menu_1_2(void);
extern int TFT_CreatInputBox(unsigned int X_val,unsigned int Y_val,unsigned char Enter,unsigned char Back);  //L为左端地址，R为右端地址，Enter为确认字符，Back为取消字符。返回自然数或 -1(标志执行返回操作)
extern void Display(int num);
extern void TFT_ShowTitle(void);
#endif 
