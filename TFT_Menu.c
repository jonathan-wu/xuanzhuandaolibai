#include "msp430x54x.h"
#include "main.h"
#include "TFT_Menu.h"
#include "TFT.h"
#include "GUI.h"
#include "keyboard.h"
void TFT_Menu_init(void)
{
  
}
int TFT_CreatInputBox(unsigned int X_val,unsigned int Y_val,unsigned char Enter,unsigned char Back)
{
  int key_val=0;
  unsigned char key;
  unsigned int InputState=0,InputVector=X_val;//InputState指示当前向量输入状态。无数值为0，有为1。
  while(1)
  {
    //TFT_WriteCmd(InputVector);
    //TFT_WriteCmd(0x0f);
    while((key=read_key())=='?');
    if('0'<=key&&key<='9')
    {
      //_NOP();
      showzifu(X_val,Y_val,' ',0xffff,0xffff);
      showzifu(X_val,Y_val,key,0x0000,0xffff);
      if(InputState==1) key_val/=10,InputState=1;
      else InputVector+=8,InputState=0;
      if(InputVector>X_val) InputVector=X_val,InputState=1;
      //TFT_WriteCmd(InputVector);
      key_val=key_val*10+key-'0';
    }
    else if(key==Back)
    {
      if(InputState==0) return -1;
      else
      {
        showzifu(InputVector,Y_val,' ',0xffff,0xffff);
        key_val/=10;
        InputState=0;
      }
      //TFT_WriteCmd(InputVector);
    }
    else if(key==Enter)
    {
      return key_val;
    }
  }
}
void TFT_Menu_StartMenu(void)
{
  int key_num=-1;
  Clear_Screen();
  TFT_ShowTitle();
  while(1)
  {
    Fill_Window(0,64,239,225,0xffff);//Clear_Screen();
    Draw_CC(0,64,25,0x0000,0xffff);//你
    Draw_CC(16,64,26,0x0000,0xffff);//好
    showzifu(32,66,',',0x0000,0xffff);
    Draw_CC(40,64,27,0x0000,0xffff);//欢
    Draw_CC(56,64,28,0x0000,0xffff);//迎
    Draw_CC(72,64,29,0x0000,0xffff);//使
    Draw_CC(88,64,30,0x0000,0xffff);//用
    showzifu(104,66,'!',0x0000,0xffff);
    
    Draw_CC(0,80,31,0x0000,0xffff);//请选择功能：A确认，B返回
    Draw_CC(16,80,32,0x0000,0xffff);
    Draw_CC(32,80,33,0x0000,0xffff);
    Draw_CC(48,80,34,0x0000,0xffff);
    Draw_CC(64,80,35,0x0000,0xffff);
    showzifu(80,82,':',0x0000,0xffff);
    showzifu(88,82,'A',0x0000,0xffff);
    Draw_CC(96,80,36,0x0000,0xffff);
    Draw_CC(112,80,37,0x0000,0xffff);
    showzifu(128,82,',',0x0000,0xffff);
    showzifu(136,82,'B',0x0000,0xffff);
    Draw_CC(144,80,38,0x0000,0xffff);
    Draw_CC(160,80,39,0x0000,0xffff);
    
    showzifu(0,98,'1',0x0000,0xffff);//基本功能1
    showzifu(8,98,':',0x0000,0xffff);
    Draw_CC(16,96,40,0x0000,0xffff);
    Draw_CC(32,96,41,0x0000,0xffff);
    Draw_CC(48,96,34,0x0000,0xffff);
    Draw_CC(64,96,35,0x0000,0xffff);
    showzifu(84,98,'1',0x0000,0xffff);
    
    showzifu(0,114,'2',0x0000,0xffff);//基本功能2
    showzifu(8,114,':',0x0000,0xffff);
    Draw_CC(16,112,40,0x0000,0xffff);
    Draw_CC(32,112,41,0x0000,0xffff);
    Draw_CC(48,112,34,0x0000,0xffff);
    Draw_CC(64,112,35,0x0000,0xffff);
    showzifu(84,114,'2',0x0000,0xffff);
    
    showzifu(0,130,'3',0x0000,0xffff);//基本功能3
    showzifu(8,130,':',0x0000,0xffff);
    Draw_CC(16,128,40,0x0000,0xffff);
    Draw_CC(32,128,41,0x0000,0xffff);
    Draw_CC(48,128,34,0x0000,0xffff);
    Draw_CC(64,128,35,0x0000,0xffff);
    showzifu(84,130,'3',0x0000,0xffff);
    
    showzifu(0,146,'4',0x0000,0xffff);//发挥功能1
    showzifu(8,146,':',0x0000,0xffff);
    Draw_CC(16,144,42,0x0000,0xffff);
    Draw_CC(32,144,43,0x0000,0xffff);
    Draw_CC(48,144,34,0x0000,0xffff);
    Draw_CC(64,144,35,0x0000,0xffff);
    showzifu(84,146,'1',0x0000,0xffff);
    
    showzifu(0,162,'5',0x0000,0xffff);//发挥功能2
    showzifu(8,162,':',0x0000,0xffff);
    Draw_CC(16,160,42,0x0000,0xffff);
    Draw_CC(32,160,43,0x0000,0xffff);
    Draw_CC(48,160,34,0x0000,0xffff);
    Draw_CC(64,160,35,0x0000,0xffff);
    showzifu(84,162,'2',0x0000,0xffff);
    
    showzifu(0,178,'6',0x0000,0xffff);//发挥功能3
    showzifu(8,178,':',0x0000,0xffff);
    Draw_CC(16,176,42,0x0000,0xffff);
    Draw_CC(32,176,43,0x0000,0xffff);
    Draw_CC(48,176,34,0x0000,0xffff);
    Draw_CC(64,176,35,0x0000,0xffff);
    showzifu(84,178,'3',0x0000,0xffff);
    
    showzifu(0,194,'7',0x0000,0xffff);//发挥功能4:(设置)
    showzifu(8,194,':',0x0000,0xffff);
    Draw_CC(16,192,42,0x0000,0xffff);
    Draw_CC(32,192,43,0x0000,0xffff);
    Draw_CC(48,192,34,0x0000,0xffff);
    Draw_CC(64,192,35,0x0000,0xffff);
    showzifu(84,194,'4',0x0000,0xffff);
    showzifu(90,194,':',0x0000,0xffff);
    showzifu(96,194,'(',0x0000,0xffff);
    Draw_CC(104,192,44,0x0000,0xffff);
    Draw_CC(120,192,45,0x0000,0xffff);
    showzifu(136,194,')',0x0000,0xffff);
    
    Draw_CC(0,208,31,0x0000,0xffff);
    Draw_CC(16,208,32,0x0000,0xffff);
    Draw_CC(32,208,33,0x0000,0xffff);
    showzifu(48,210,':',0x0000,0xffff);
    key_num=TFT_CreatInputBox(56,210,'A','B');
    switch(key_num)
    {
    case -1:break;  //主菜单不可以return
    case 0:break;                        
    case 1:
      function_1();
      break;
    case 2:
      function_2();
      break;
    case 3:
      function_3();
      break;
    case 4:
      function_4();
      break;
    case 5:
      break;
    case 6:
      function_6();
      break;
    default:
      break;
    }
  }
}
/*
void TFT_Menu_OffMenu(void)
{
}
void TFT_Menu_1(void)
{
  int key_num=-1;
  while(1)
  {
    TFT_ClearScreen();
    TFT_DisplayStr(0,0,"子菜单1");
    TFT_DisplayStr(1,0,"请选择功能：");
    TFT_DisplayStr(2,0,"请输入：");
    TFT_DisplayStr(3,0,"确认:A  取消:B");
    key_num=TFT_CreatInputBox(0x8c,0x8f,'A','B');
    switch(key_num)
    {
    case -1:return;  //返回上级菜单
    case 0:break;                        
    case 1:TFT_Menu_1_1();break;
    case 2:TFT_Menu_1_2();break;
    default:break;
    }
  }
}
void TFT_Menu_2(void)
{
  int key_num=-1;
  while(1)
  {
    TFT_ClearScreen();
    TFT_DisplayStr(0,0,"子菜单2");
    TFT_DisplayStr(1,0,"请选择功能：");
    TFT_DisplayStr(2,0,"请输入：");
    TFT_DisplayStr(3,0,"确认:A  取消:B");
    key_num=TFT_CreatInputBox(0x8c,0x8f,'A','B');
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

void TFT_Menu_1_1(void)
{
  int key_num=-1;
  while(1)
  {
    TFT_ClearScreen();
    TFT_DisplayStr(0,0,"子菜单1-1");
    TFT_DisplayStr(1,0,"请选择功能：");
    TFT_DisplayStr(2,0,"请输入：");
    TFT_DisplayStr(3,0,"确认:A  取消:B");
    key_num=TFT_CreatInputBox(0x8c,0x8f,'A','B');
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
void TFT_Menu_1_2(void)
{
  int key_num=-1;
  while(1)
  {
    TFT_ClearScreen();
    TFT_DisplayStr(0,0,"子菜单1-2");
    TFT_DisplayStr(1,0,"请选择功能：");
    TFT_DisplayStr(2,0,"请输入：");
    TFT_DisplayStr(3,0,"确认:A  取消:B");
    key_num=TFT_CreatInputBox(0x8c,0x8f,'A','B');
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
    TFT_ClearScreen();
    TFT_DisplayStr(0,0,"数字为：");
    TFT_DisplayNum(0x90,num);
    TFT_DisplayStr(2,0,"请输入：");
    TFT_DisplayStr(3,0,"确认:A  返回:B");
    key_num=TFT_CreatInputBox(0x8c,0x8f,'A','B');
    switch(key_num)
    {
    case -1:return;  //返回上级菜单
    default:return;
    }
  }
}
*/
void TFT_ShowTitle(void)
{
  int i;
  for(i=0;i<12;i++) Draw_CC(i*16+24,32,i,0xf800,0xffff);//简
  showzifu(135,290,'b',0x001f,0xffff);
  showzifu(143,290,'y',0x001f,0xffff);
  showzifu(151,290,':',0x001f,0xffff);
  for(i=0;i<5;i++) Draw_CC(i*16+159,288,i+12,0x001f,0xffff);
  showzifu(71,306,'f',0x001f,0xffff);
  showzifu(79,306,'r',0x001f,0xffff);
  showzifu(87,306,'o',0x001f,0xffff);
  showzifu(95,306,'m',0x001f,0xffff);
  showzifu(103,306,':',0x001f,0xffff);
  for(i=0;i<8;i++) Draw_CC(i*16+111,304,i+17,0x001f,0xffff);
}