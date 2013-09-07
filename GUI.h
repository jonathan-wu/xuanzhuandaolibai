#ifndef GUI_H_
#define GUI_H_
extern void GUI_init(void);
extern void Fill_Window(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int color);
extern void Clear_Screen(void);
extern void Draw_Point(unsigned int x,unsigned int y,unsigned int color);
extern void Draw_Vline(unsigned int x,unsigned int y1,unsigned int y2,unsigned int color);
extern void Draw_Hline(unsigned int x1,unsigned int x2,unsigned int y,unsigned int color);
extern void Draw_Rectangle(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int color);
extern void Draw_Line(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int color);
extern void Draw_Circle(unsigned int x0,unsigned int y0,unsigned int r, unsigned int color);
extern void Draw_Oval(unsigned int x, unsigned int y, unsigned int a, unsigned int b, unsigned int color);//»­ÍÖÔ²º¯Êı£¬´ı²âÊÔ
extern void showzifu(unsigned int x,unsigned int y,unsigned char value,unsigned int dcolor,unsigned int bgcolor);//»­×Ö·û
extern void Draw_CC(unsigned int x,unsigned int y,unsigned char num,unsigned int dcolor,unsigned int bgcolor);//»­ºº×Ö,(x,y)×ø±ê£¬numÎª×Ö¿âÖĞ±àºÅ£¬dcolorÎª×ÖÑÕÉ«£¬bgcolorÎª±³¾°É«
#endif 