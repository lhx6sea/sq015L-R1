#ifndef     _Include_H_             
#define     _Include_H_


//------------------------------------------------------------------
//CPU,编译器,C语言
#include 	<SQ013L.h>                 
//#include 	<hc18p235L.h>
//#include 	<hc18p110L.h>

#include    "typedef.h"
#include    "C:\Program Files\HC-IDE\HOLYCHIP_DEFINE.h"


//------------------------------------------------------------------
//硬件IO
#include	"Board.h"


//------------------------------------------------------------------
//全局变量
#include	"data.h"



//------------------------------------------------------------------
//函数声明
//#include    "Initial.h"

/*
*****************************************
void delay(void);
void sleep_handle(void);
void ram_clr(void);
void at24c02_write_byte(u8 addr,u8 dat);
u8   at24c02_read_byte(u8 addr);
void key_scay(void);
void key_handle(void);
**************************************
*/



//------------------------------------------------------------------
//声明位全局函数
void HandleKeyPress(void);
void LogicalFlow(void);
void KeyScanPer10ms(void);          //@10ms
void SendSOSsignal(void);           //@150ms



void inital(void);
void sysinitial(void);





#endif