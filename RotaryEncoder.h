#include"Global.h"
#ifdef RotaryEncoder_Used_
#ifndef RotaryEncoder_H_
#define RotaryEncoder_H_

extern volatile unsigned long E1_V,E2_V;
extern volatile signed long E1_pulseCnt,E2_pulseCnt;
extern volatile signed long E2_interval;
extern void RotaryEncoder_init();

#endif
#endif