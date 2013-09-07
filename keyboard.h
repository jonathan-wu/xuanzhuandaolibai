/*
扫描键盘头文件，带中断，不需要一直扫描，减少CPU占用
1~8接P4.0~P4.7
使用P2.1作为中断口
含按键防抖功能
*/
//使用时先初始化，然后直接调用读取键盘值函数
#ifndef keyboard_H_
#define keyboard_H_
static unsigned char tem=0x00;//定义的按键行列记录值
static unsigned char readed=0;//定义数据是否被读取
extern void keyboard_init(void);
extern void scan_key(void);
extern unsigned char read_key(void);
extern void keyboard_clear(void);
#endif
