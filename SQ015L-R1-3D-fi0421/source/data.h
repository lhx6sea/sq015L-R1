#ifndef     _data_H_
#define     _data_H_




//------------------------------------------------------------------
//全局变量		extern

extern volatile uint8_t		FanState;

extern volatile uint8_t 	u8Step100ms;

extern volatile uint8_t		u8addto5s;


extern volatile uint8_t 	InvalidCounter;    	// 按键无效Count
extern volatile uint8_t 	ValidCounter;       // 按键有效Count
extern volatile uint8_t 	DoubleHitCounter;	// 防止释放抖动


//------------------------------------------------------------------
//全局{位域}变量,变量定义在C文件内
extern volatile BIT_BYTE_S 	u8TimerFlag;      // 局部{位域}变量

#define	bTask_10ms        	u8TimerFlag.b0



//------------------------------------------------------------------
//全局{位域}变量,变量定义在C文件内
extern volatile BIT_BYTE_S    	u8FlagKey;               	

//#define bIP5305OnOffTrigger     u8FlagKey.b0

#define bOneClickTrigger        u8FlagKey.b5
#define bLongPressTrigger       u8FlagKey.b6
#define bTask_step_100ms       	u8FlagKey.b7


//#define bKeyShiftTriggle      ubKeyTrigger.bits.b1










#endif