#ifndef     _data_H_
#define     _data_H_




//------------------------------------------------------------------
//ȫ�ֱ���		extern

extern volatile uint8_t		FanState;

extern volatile uint8_t 	u8Step100ms;

extern volatile uint8_t		u8addto5s;


extern volatile uint8_t 	InvalidCounter;    	// ������ЧCount
extern volatile uint8_t 	ValidCounter;       // ������ЧCount
extern volatile uint8_t 	DoubleHitCounter;	// ��ֹ�ͷŶ���


//------------------------------------------------------------------
//ȫ��{λ��}����,����������C�ļ���
extern volatile BIT_BYTE_S 	u8TimerFlag;      // �ֲ�{λ��}����

#define	bTask_10ms        	u8TimerFlag.b0



//------------------------------------------------------------------
//ȫ��{λ��}����,����������C�ļ���
extern volatile BIT_BYTE_S    	u8FlagKey;               	

//#define bIP5305OnOffTrigger     u8FlagKey.b0

#define bOneClickTrigger        u8FlagKey.b5
#define bLongPressTrigger       u8FlagKey.b6
#define bTask_step_100ms       	u8FlagKey.b7


//#define bKeyShiftTriggle      ubKeyTrigger.bits.b1










#endif