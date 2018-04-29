#ifndef     _data_H_               
#define     _data_H_




//------------------------------------------------------------------
//全局变量
extern volatile uint8_t		FanState;

extern volatile uint8_t 	u8Pulse200ms;



extern BIT_BYTE_S    ubKeyTrigger;               	// 全局{位域}变量,定义在C文件内
//------------------------------------------------------------------
//全局{位域}变量
#define bIP5305OnOffTrigger     ubKeyTrigger.b0
#define bOneClickTrigger        ubKeyTrigger.b1
#define bLongPressTrigger       ubKeyTrigger.b2


//#define bKeyShiftTriggle      ubKeyTrigger.bits.b1










#endif