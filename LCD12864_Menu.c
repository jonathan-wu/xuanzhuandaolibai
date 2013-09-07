#include "msp430x54x.h"
#include "LCD12864_Menu.h"
#include "LCD12864.h"
#include "keyboard.h"
void LCD12864_Menu_init(void)
{
}
int  LCD12864_CreatInputBox(unsigned char L,unsigned char R,unsigned char Enter,unsigned char Back)       //LΪ��˵�ַ��RΪ�Ҷ˵�ַ��EnterΪȷ���ַ���BackΪȡ���ַ���������Ȼ���� -1(��־ִ�з��ز���)
{
  int key_val=0;
  unsigned char key,InputState=0,InputVector=L;//InputStateָʾ��ǰ��������״̬������ֵΪ0����Ϊ1��
  while(1)
  {
    LCD12864_WriteCmd(InputVector);
    LCD12864_WriteCmd(0x0f);
    while((key=read_key())=='?');
    if('0'<=key&&key<='9')
    {
      DisplayCgrom(InputVector,"  ");
      LCD12864_DisplayChar(InputVector,key);
      if(InputVector==R && InputState==1) key_val/=10,InputState=1;
      else InputVector++,InputState=0;
      if(InputVector>R) InputVector=R,InputState=1;
      LCD12864_WriteCmd(InputVector);
      key_val=key_val*10+key-'0';
    }
    else if(key==Back)
    {
      if(InputVector==L && InputState==0) return -1;
      if(InputState==1)
      {
        key_val/=10;
        InputState=0;
      }
      else
      {
        key_val/=10;
        InputVector--;
      }
      DisplayCgrom(InputVector,"  ");
      LCD12864_WriteCmd(InputVector);
    }
    else if(key==Enter)
    {
      return key_val;
    }
  }
}
void LCD12864_Menu_StartMenu(void)
{
  int key_num=-1;
  while(1)
  {
    LCD12864_ClearScreen();
    LCD12864_DisplayStr(0,0,"��ӭʹ�ã�");
    LCD12864_DisplayStr(1,0,"��ѡ���ܣ�");
    LCD12864_DisplayStr(2,0,"�����룺");
    LCD12864_DisplayStr(3,0,"ȷ��:A  ȡ��:B");
    key_num=LCD12864_CreatInputBox(0x8c,0x8f,'A','B');
    switch(key_num)
    {
    case -1:break;  //���˵�������return
    case 0:break;                        
    case 1:LCD12864_Menu_1();break;
    case 2:LCD12864_Menu_2();break;
    default:break;
    }
  }
}
void LCD12864_Menu_OffMenu(void)
{
}
void LCD12864_Menu_1(void)
{
  int key_num=-1;
  while(1)
  {
    LCD12864_ClearScreen();
    LCD12864_DisplayStr(0,0,"�Ӳ˵�1");
    LCD12864_DisplayStr(1,0,"��ѡ���ܣ�");
    LCD12864_DisplayStr(2,0,"�����룺");
    LCD12864_DisplayStr(3,0,"ȷ��:A  ȡ��:B");
    key_num=LCD12864_CreatInputBox(0x8c,0x8f,'A','B');
    switch(key_num)
    {
    case -1:return;  //�����ϼ��˵�
    case 0:break;                        
    case 1:LCD12864_Menu_1_1();break;
    case 2:LCD12864_Menu_1_2();break;
    default:break;
    }
  }
}
void LCD12864_Menu_2(void)
{
  int key_num=-1;
  while(1)
  {
    LCD12864_ClearScreen();
    LCD12864_DisplayStr(0,0,"�Ӳ˵�2");
    LCD12864_DisplayStr(1,0,"��ѡ���ܣ�");
    LCD12864_DisplayStr(2,0,"�����룺");
    LCD12864_DisplayStr(3,0,"ȷ��:A  ȡ��:B");
    key_num=LCD12864_CreatInputBox(0x8c,0x8f,'A','B');
    switch(key_num)
    {
    case -1:return;  //�����ϼ��˵�
    case 0:break;                        
    case 1:break;
    case 2:break;
    default:Display(key_num);break;
    }
  }
}

void LCD12864_Menu_1_1(void)
{
  int key_num=-1;
  while(1)
  {
    LCD12864_ClearScreen();
    LCD12864_DisplayStr(0,0,"�Ӳ˵�1-1");
    LCD12864_DisplayStr(1,0,"��ѡ���ܣ�");
    LCD12864_DisplayStr(2,0,"�����룺");
    LCD12864_DisplayStr(3,0,"ȷ��:A  ȡ��:B");
    key_num=LCD12864_CreatInputBox(0x8c,0x8f,'A','B');
    switch(key_num)
    {
    case -1:return;  //�����ϼ��˵�
    case 0:break;                        
    case 1:break;
    case 2:break;
    default:break;
    }
  }
}
void LCD12864_Menu_1_2(void)
{
  int key_num=-1;
  while(1)
  {
    LCD12864_ClearScreen();
    LCD12864_DisplayStr(0,0,"�Ӳ˵�1-2");
    LCD12864_DisplayStr(1,0,"��ѡ���ܣ�");
    LCD12864_DisplayStr(2,0,"�����룺");
    LCD12864_DisplayStr(3,0,"ȷ��:A  ȡ��:B");
    key_num=LCD12864_CreatInputBox(0x8c,0x8f,'A','B');
    switch(key_num)
    {
    case -1:return;  //�����ϼ��˵�
    default:Display(-100);break;
    }
  }
}
void Display(int num)
{
  int key_num=-1;
  while(1)
  {
    LCD12864_ClearScreen();
    LCD12864_DisplayStr(0,0,"����Ϊ��");
    LCD12864_DisplayNum(0x90,num);
    LCD12864_DisplayStr(2,0,"�����룺");
    LCD12864_DisplayStr(3,0,"ȷ��:A  ����:B");
    key_num=LCD12864_CreatInputBox(0x8c,0x8f,'A','B');
    switch(key_num)
    {
    case -1:return;  //�����ϼ��˵�
    default:return;
    }
  }
}