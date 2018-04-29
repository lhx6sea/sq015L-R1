/***************************************************************************************
*|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
*|C:编译器 已知BUG
*|1.少用局部变量，可以使用全局变量传参数
*|2.swich语句不要使用（可以使用if  else 代替）
*|3.RAM 现阶段 编译器最少要需要占用9个字节（中断保存 ACC,status,处理函数参数等）
*|4.源代码行数比较多时，编译速度比较慢
*|5.少用 bool 变量
*|______________________________________________________________________________________ 
*/
#include	"include.h"

//extern  uint8_t         addto20s;








/*********************************************************************
#define ShortInterval       5           // 短按按键间隔 >= 2
#define LongInterval        66          // 长按按键间隔
#define DoubleHitInterval   5           // 防按键双击误动间隔

#define InvalidInterval     5           // ??????
#define KeyBeepInterval     5           // ?????

#define PreSet1    			(1)
#define KeyPort     		PORTB		// PB3/FanSpeed3	PB0/LED_SOS


__BIT_BYTE_U    ubFlagKey; 		        // 局部{位域}变量

#define Switch      		ubFlagKey.bits.b0
#define PinValue		    ubFlagKey.bits.b1
#define ScanPins    		ubFlagKey.bits.b2
#define ScanData    		ubFlagKey.bits.b3
#define KeyValue	      	ubFlagKey.bits.b4

#define _bKeyPressed		ubFlagKey.bits.b7


extern uint8_t FanState;
extern uint8_t RelayState;
extern uint8_t addto20s;


uint8_t InvalidCounter;                 // 按键无效Count
uint8_t ValidCounter;           		// 按键有效Count
uint8_t DoubleHitCounter;       	    // 防止按键双击
*/



/***************************************************************************************
*|``````````````````````````````````````````````````````````````````````````````````````
*|  void LogicalFlow(void)              逻辑流程           
*|______________________________________________________________________________________ 
*/
void LogicalFlow(void)                  //@1ms
{

    if( FanState == 0 )                 //关机
    {
        WorkLEDoff();
        FanSpeed0();
    }

    if( FanState == 1 )                 //风扇1档
    {
        WorkLEDon();
        FanSpeed1();
    }

    if( FanState == 2 )                 //风扇2档
    {
        WorkLEDon();
        FanSpeed2();
    }


    if( FanState == 3 )                 //风扇3档
    {
        WorkLEDon();
        FanSpeed3();
    }


	//if( FanState==FanSpeed_Off )		//关机
	{
        //WorkLEDon();
        //WorkLEDoff();
		
        if(bIP5305OnOffTrigger)      	//单击,开机,换挡,均触发,升压输出
		{
			if(u8pulse200ms) 
            {
                IP5305_OnOff_1();
            }
			else
			{
				IP5305_OnOff_0();
				bIP5305OnOffTrigger=0;	//按键脉冲 200ms
			}
		}

    }


	/***********************************************
    else if( FanState>=1 ) 
	{
        WorkLEDon();

        if(bKeyShiftTriggle)		  	//shift按键
        {
			if(u8pulse200ms) KeyShift_0();
			else
			{
				KeyShift_1();
				bKeyShiftTriggle=0;     //按键脉冲 200ms
			}
		}

    } 
    /*/   

}


/***************************************************************************************
*|``````````````````````````````````````````````````````````````````````````````````````
*|  void LogicalFlow(void)             		逻辑流程           
*|______________________________________________________________________________________ 
*/
void HandleKeyPress(void)              		//10ms
{
    
    if(bOneClickTrigger)           			//单击
    {
        bOneClickTrigger=0;

		if(FanState>0)						//开机后才可以单按,fi0225
        {
            
            FanState++;                   	//调速
            if(FanState>=4)
            {
                FanState=0;
			}
            else
            {
                bIP5305OnOffTrigger=1;		//200ms, 低电平
                u8pulse200ms=200;
            }
        }        
    }

    
    if(bLongPressTrigger)                   //长按
    {
        bLongPressTrigger=0;

        if(FanState > 0)                    //关机
        {
            FanState=0;
        }

        else	//if(FanState==0)   		//关机,长按,开,移动电源
        {
			FanState=1;
            bIP5305OnOffTrigger=1;          //200ms, 低电平
            u8pulse200ms=200;
        }
    
    }


    /***************************************************************
    if( FanState==0 )
    {
        FanState=1;
        bKeyShiftTriggle=1;
        delay200ms=200;
    }
    
    else if( FanState==1 )
    {
        FanState=2;
        bKeyShiftTriggle=1;
        delay200ms=200;
    }
    
    else if( FanState==2 )
    {
        FanState=3;
        bKeyShiftTriggle=1;
        delay200ms=200;
    }
    
    
    else if( FanState==3 )
    {
        FanState=0;
        bKeyOnOffTriggle=1;
        delay200ms=200;
    }
    ********************************/
}