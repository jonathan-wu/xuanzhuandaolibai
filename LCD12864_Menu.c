#include "msp430x54x.h"
#include "LCD12864_Menu.h"
#include "LCD12864.h"
#include "keyboard.h"
void LCD12864_Menu_init(void)
{
}
int  LCD12864_CreatInputBox(unsigned char L,unsigned char R,unsigned char Enter,unsigned char Back)       //L为左端地址，R为右端地址，Enter为确认字符，Back为取消字符。返回自然数或 -1(标志执行返回操作)
{
  int key_val=0;
  unsigned char key,InputState=0,InputVector=L;//InputState指示当前向量输入状态。无数值为0，有为1。
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
    LCD12864_DisplayStr(0,0,"欢迎使用！");
    LCD12864_DisplayStr(1,0,"请选择功能：");
    LCD12864_DisplayStr(2,0,"请输入：");
    LCD12864_DisplayStr(3,0,"确认:A  取消:B");
    key_num=LCD12864_CreatInputBox(0x8c,0x8f,'A','B');
    switch(key_num)
    {
    case -1:break;  //主菜单不可以return
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
    LCD12864_DisplayStr(0,0,"子菜单1");
    LCD12864_DisplayStr(1,0,"请选择功能：");
    LCD12864_DisplayStr(2,0,"请输入：");
    LCD12864_DisplayStr(3,0,"确认:A  取消:B");
    key_num=LCD12864_CreatInputBox(0x8c,0x8f,'A','B');
    switch(key_num)
    {
    case -1:return;  //返回上级菜单
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
    LCD12864_DisplayStr(0,0,"子菜单2");
    LCD12864_DisplayStr(1,0,"请选择功能：");
    LCD12864_DisplayStr(2,0,"请输入：");
    LCD12864_DisplayStr(3,0,"确认:A  取消:B");
    key_num=LCD12864_CreatInputBox(0x8c,0x8f,'A','B');
    switch(key_num)
    {
    case -1:return;  //返回上级菜单
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
    LCD12864_DisplayStr(0,0,"子菜单1-1");
    LCD12864_DisplayStr(1,0,"请选择功能：");
    LCD12864_DisplayStr(2,0,"请输入：");
    LCD12864_DisplayStr(3,0,"确认:A  取消:B");
    key_num=LCD12864_CreatInputBox(0x8c,0x8f,'A','B');
    switch(key_num)
    {
    case -1:return;  //返回上级菜单
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
    LCD12864_DisplayStr(0,0,"子菜单1-2");
    LCD12864_DisplayStr(1,0,"请选择功能：");
    LCD12864_DisplayStr(2,0,"请输入：");
    LCD12864_DisplayStr(3,0,"确认:A  取消:B");
    key_num=LCD12864_CreatInputBox(0x8c,0x8f,'A','B');
    switch(key_num)
    {
    case -1:return;  //返回上级菜单
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
    LCD12864_DisplayStr(0,0,"数字为：");
    LCD12864_DisplayNum(0x90,num);
    LCD12864_DisplayStr(2,0,"请输入：");
    LCD12864_DisplayStr(3,0,"确认:A  返回:B");
    key_num=LCD12864_CreatInputBox(0x8c,0x8f,'A','B');
    switch(key_num)
    {
    case -1:return;  //返回上级菜单
    default:return;
    }
  }
}