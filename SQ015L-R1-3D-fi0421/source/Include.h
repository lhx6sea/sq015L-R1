#ifndef     _include_h_
#define     _include_h_


//------------------------------------------------------------------
//CPU,������,C����

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
//Ӳ��IO
#include	"Board.h"


//------------------------------------------------------------------
//ȫ�ֱ���
#include	"data.h"


//------------------------------------------------------------------
//��������
#include    "Initial.h"
void inital(void);
void sysinitial(void);



extern volatile uint8_t InvalidCounter;            // ������ЧCount
extern volatile uint8_t ValidCounter;              // ������ЧCount
extern volatile uint8_t DoubleHitCounter;          // ��ֹ�ͷŶ���


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
//����ȫ�ֺ���

void HandleKeyPress(void);
void LogicalFlow(void);

void KeyScanPer10ms(void);          //@10ms
//void SendSOSsignal(void);           //@150ms






#endif