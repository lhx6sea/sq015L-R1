/***********************************************************************
*|``````````````````````````````````````````````````````````````````````
*|C:编译器 已知BUG(Mk6a12p)
*|1.少用局部变量，可以使用全局变量传参数
*|2.swich语句不要使用（可以使用if  else 代替）
*|3.RAM 现阶段 编译器最少占用9个字节(中断保存ACC,status,处理函数参数等)
*|4.源代码行数比较多时，编译速度比较慢
*|5.少用 bool 变量
*|______________________________________________________________________
*/
#include	"include.h"

/***********************************************************************
#define ShortInterval       5     				// 短按键间隔 >= 2
#define LongInterval        66   				// 长按键间隔
#define DoubleHitInterval   5      				// 防双击误动作间隔

#define InvalidInterval     5      				// ??????
#define KeyBeepInterval     5      				// ?????

#define PreSet1    			(1)
#define KeyPort     		PORTB


__BIT_BYTE_U    ubFlagKey; 		  				// 局部{位域}变量

#define Switch      		ubFlagKey.bits.b0
#define PinValue		    ubFlagKey.bits.b1
#define ScanPins    		ubFlagKey.bits.b2
#define ScanData    		ubFlagKey.bits.b3
#define KeyValue	      	ubFlagKey.bits.b4

#define _bKeyPressed		ubFlagKey.bits.b7


extern uint8_t FanState;
extern uint8_t RelayState;
extern uint8_t addto20s;


uint8_t InvalidCounter;                 		// 按键无效Count
uint8_t ValidCounter;           				// 按键有效Count
uint8_t DoubleHitCounter;       	    		// 防止按键双击
************************************************************************
*/

//const u8  DutyTable[]={0,4,13,23,31,0};
const u8  DutyTable[]={0,4,19,29,0};


/***********************************************************************
*|``````````````````````````````````````````````````````````````````````
*|  void LogicalFlow(void)       	逻辑流程
*|______________________________________________________________________
*/
void LogicalFlow(void)           	//run@1ms
{

    if( FanState == 0 )                     //关机
    {
        LED_close();
        PWM0P = 0;

        if(bTask_step_100ms)                //延时关闭,风机; 让高压消失
        {
            FanSpeed0();
        }
    }

    if( FanState == 1 )                     //风扇1档
    {
        LED_1D();
        FanSpeed1();

        if(bTask_step_100ms)
        {
            PWM0OE=0;       //"0":PWM输出     //fi0331
        }


        if(PWM0P < DutyTable[FanState])
        {
            if(bTask_step_100ms)
            {
                bTask_step_100ms=0;
                PWM0P++;
            }
        }
    }

    if( FanState == 2 )                     //风扇2档
    {
        LED_2D_3D();
        FanSpeed2();

        if(bTask_step_100ms)
        {
            PWM0OE=0;       //"0":PWM输出     //fi0331
        }

        if(PWM0P < DutyTable[FanState])
        {
            if(bTask_step_100ms)
            {
                bTask_step_100ms=0;
                PWM0P++;
            }
        }
    }


    if( FanState == 3 )                     //风扇3档
    {
        LED_2D_3D();
        FanSpeed3();

        if(bTask_step_100ms)
        {
            PWM0OE=0;       //"0":PWM输出     //fi0331
        }

        if(PWM0P < DutyTable[FanState])
        {
            if(bTask_step_100ms)
            {
                bTask_step_100ms=0;
                PWM0P++;
            }
        }
    }

    /************************************************
    if( FanState == 4 )                     //风扇4档
    {
        LED_2D_3D();
        FanSpeed4();

        if(bTask_step_100ms)
        {
            PWM0OE=0;       //"0":PWM输出     //fi0331
        }

        if(PWM0P < DutyTable[FanState])
        {
            if(bTask_step_100ms)
            {
                bTask_step_100ms=0;
                PWM0P++;
            }
        }
    }
    //*/


    /***************************************
    //if( FanState==FanSpeed_Off )          //关机
    {
        //WorkLEDon();
        //WorkLEDoff();

        if(bIP5305OnOffTrigger)             //单击,开机,换挡,均触发,升压输出
        {
            if(u8Step100ms)
            {
                //IP5305_OnOff_1();
                _nop();
            }
            else
            {
                //IP5305_OnOff_0();
                bIP5305OnOffTrigger=0;      //按键脉冲 200ms
            }
        }
    }
    //*/


    /***************************************
    else if( FanState>=1 )
    {
        WorkLEDon();

        if(bKeyShiftTriggle)                //shift按键
        {
            if(u8pulse200ms) KeyShift_0();
            else
            {
                KeyShift_1();
                bKeyShiftTriggle=0;         //按键脉冲 200ms
            }
        }

    }
    ***************************************/

}//>{LogicalFlow}


/***********************************************************************
*|``````````````````````````````````````````````````````````````````````
*|  void LogicalFlow(void)             		逻辑流程
*|______________________________________________________________________
*/
void HandleKeyPress(void)              		//10ms
{

    if(bOneClickTrigger)           			//单击
    {
        bOneClickTrigger=0;

        u8Step100ms=0;
        bTask_step_100ms=0;

        if(FanState>0)                      //开机后才可以单按,fi0225
        {

            if(++FanState>=4)               //0,1,2,3,4,5(0)
            {
                FanState=0;                 //档位                
            }

            /*******************************
            else
            {
                bIP5305OnOffTrigger=1;      //200ms, 低电平
                u8Step100ms=200;
            }
            *******************************/
        }
    }


    if(bLongPressTrigger)                   //长按
    {
        bLongPressTrigger=0;

        u8Step100ms=0;
        bTask_step_100ms=0;

        //if(FanState > 0)      //关机
        //{
        //    FanState=0;
        //}

        //else

        if(FanState==0)         //开机,,开,移动电源
        {
            FanState=1;

            //bIP5305OnOffTrigger=1;          //200ms, 低电平
            //u8Pulse200ms=200;
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
    ***************************************************************/

}//>{HandleKeyPress}