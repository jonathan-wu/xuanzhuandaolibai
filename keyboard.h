/*
ɨ�����ͷ�ļ������жϣ�����Ҫһֱɨ�裬����CPUռ��
1~8��P4.0~P4.7
ʹ��P2.1��Ϊ�жϿ�
��������������
*/
//ʹ��ʱ�ȳ�ʼ����Ȼ��ֱ�ӵ��ö�ȡ����ֵ����
#ifndef keyboard_H_
#define keyboard_H_
static unsigned char tem=0x00;//����İ������м�¼ֵ
static unsigned char readed=0;//���������Ƿ񱻶�ȡ
extern void keyboard_init(void);
extern void scan_key(void);
extern unsigned char read_key(void);
extern void keyboard_clear(void);
#endif
