#ifndef     _include_h_
#define     _include_h_


//------------------------------------------------------------------
//CPU,编译器,C语言

//#include 	<SQ013L.h>
#include 	<sq015L.h>
//#include 	<hc18p235L.h>
//#include 	<hc18p110L.h>





//#include "delay.h"
#include "Pwm.h"

#include    "typedef.h"
//#include    "C:\Program Files\HC-IDE\HOLYCHIP_DEFINE.h"
#include    "HOLYCHIP_DEFINE.h"


//------------------------------------------------------------------
//硬件IO
#include	"Board.h"


//------------------------------------------------------------------
//全局变量
#include	"data.h"


//------------------------------------------------------------------
//函数声明
#include    "Initial.h"
void inital(void);
void sysinitial(void);



extern volatile uint8_t InvalidCounter;            // 按键无效Count
extern volatile uint8_t ValidCounter;              // 按键有效Count
extern volatile uint8_t DoubleHitCounter;          // 防止释放抖动


/*
********************************************************************
void delay(void);
void sleep_handle(void);
void ram_clr(void);
void at24c02_write_byte(u8 addr,u8 dat);
u8   at24c02_read_byte(u8 addr);
void key_scay(void);
void key_handle(void);
********************************************************************
*/


//------------------------------------------------------------------
//声明全局函数

void HandleKeyPress(void);
void LogicalFlow(void);

void KeyScanPer10ms(void);          //@10ms
//void SendSOSsignal(void);           //@150ms






#endif