#ifndef     _data_H_               
#define     _data_H_




//------------------------------------------------------------------
//ȫ�ֱ���
extern volatile uint8_t		FanState;

extern volatile uint8_t 	u8Pulse200ms;



extern BIT_BYTE_S    ubKeyTrigger;               	// ȫ��{λ��}����,������C�ļ���
//------------------------------------------------------------------
//ȫ��{λ��}����
#define bIP5305OnOffTrigger     ubKeyTrigger.b0
#define bOneClickTrigger        ubKeyTrigger.b1
#define bLongPressTrigger       ubKeyTrigger.b2


//#define bKeyShiftTriggle      ubKeyTrigger.bits.b1










#endif