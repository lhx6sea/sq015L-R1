#ifndef		_data_h
#define     _data_h




//PCON:                 // WDTEN  EIS LVDF LVDSEL3 || LVDSEL2 LVDSEL1 LVDSEL0 LVDEN 
/***********************
1001 = 3.0V 
1010 = 3.2V 
1011 = 3.4V 
1100 = 3.5V 
1101 = 3.7V 
1110 = 4.1V 
1111 = 4.3V 
//*/ 

#define		LVD_3_0V	0x12
#define		LVD_3_2V	0x14
#define		LVD_3_4V	0x16
#define		LVD_3_5V	0x18
#define		LVD_3_7V	0x1A
#define		LVD_4_1V	0x1C
#define		LVD_4_3V	0x1E




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
extern volatile BIT_BYTE_U 	u8TimerFlag;      	// �ֲ�{λ��}����

#define	bTask_10ms        	u8TimerFlag.bits.b0
#define	bVoltageDropto3V	u8TimerFlag.bits.b1



//------------------------------------------------------------------
//ȫ��{λ��}����,����������C�ļ���
extern volatile BIT_BYTE_S    	u8FlagKey;               	

//#define bIP5305OnOffTrigger     u8FlagKey.b0

#define bOneClickTrigger        u8FlagKey.b5
#define bLongPressTrigger       u8FlagKey.b6
#define bTask_step_100ms       	u8FlagKey.b7


//#define bKeyShiftTriggle      ubKeyTrigger.bits.b1










#endif