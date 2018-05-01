/***********************************************************************************
*|``````````````````````````````````````````````````````````````````````````````````
*|C:编译器 已知BUG(Mk6a12p)
*|1.少用局部变量，可以使用全局变量传参数
*|2.swich语句不要使用（可以使用if  else 代替）
*|3.RAM 现阶段 编译器最少要需要占用9个字节（中断保存 ACC,status,处理函数参数等）
*|4.源代码行数比较多时，编译速度比较慢
*|5.少用 bool 变量
*|__________________________________________________________________________________
*/
#include "include.h"

#define ShortInterval       3               // 短按键时间 >= 2
#define LongInterval        99             	// 长按键时间
#define DoubleHitInterval   3               // 防按键双击误动作, 松手按键,响应要快!

#define InvalidInterval     3               // 按键释放,防抖动
#define KeyBeepInterval     5               // 按键音

#define KeyNull             (1)
#define KeyPort             PORTB           // PB3/FanSpeed3    PB0/LED_SOS


volatile BIT_BYTE_S         u8FlagKey;      // 局部{位域}变量

#define bSwitch             u8FlagKey.b0
#define pKeyLast            u8FlagKey.b1    //PinValue
#define pKeyCurr            u8FlagKey.b2    //ScanPins
//#define pKeyData            u8FlagKey.b3  //ScanData
#define KeyValue            u8FlagKey.b3
#define bKeyPressed         u8FlagKey.b4


//----------------------------------------------------------------------------------
//全局变量
volatile uint8_t            FanState;
volatile uint8_t            u8Step100ms;

//volatile BIT_BYTE_S     	ubKeyTrigger;   // 全局{位域}变量, 在 data.h 有详细定义

volatile uint8_t InvalidCounter;            // 按键无效Count
volatile uint8_t ValidCounter;              // 按键有效Count
volatile uint8_t DoubleHitCounter;          // 防止释放抖动

//uint8_t KeyPressedCnt;                    // 按键按下计数器

/***********************************************************************************
*|``````````````````````````````````````````````````````````````````````````````````
*|  void KeyScanPer10ms(void)
*|__________________________________________________________________________________
*/
void KeyScanPer10ms(void)                   // chk@10ms
{
    //bSwitch = !bSwitch;

    if ( bSwitch )                          // run@20ms
    {
    	bSwitch=0;
        //pKeyCurr =  KeyNull;              // PB3 按键, KeyPin=3
        //PinValue =  (KeyPort&(1<<KeyPin));
        pKeyLast = pKeyCurr;
        pKeyCurr = PORTB3;
    }
    else                                    // run@20ms
    {
    	bSwitch=1;
        if((pKeyCurr==0)&&(pKeyLast==0))    // KeyValid=0;
        {
            //pKeyData = pKeyCurr;          // 获取按键数据 ScanData
            InvalidCounter = 0;

            u8addto5s=0;                    // 长按键,过程中,会休眠!
            
            //bTask_step_100ms=0;

            if (++ValidCounter >= LongInterval)
            {
                ValidCounter=LongInterval;  // 长按

                if(!bKeyPressed)            // 按键持续按下,只执行一次(功能)
                {
                    bKeyPressed=1;
                    bLongPressTrigger=1;
                    
                    
					u8Step100ms=0;
					bTask_step_100ms=0; 
					                    
                    //_StopReqSignal=1;     // 停机,回摆
                }
            }

        }//if((pKeyCurr==0)&&(pKeyLast==0))

        else                                // 松手后,发出键值(单击)
        {
            InvalidCounter++;               // 按键释放计数器

            if (InvalidCounter >= InvalidInterval)
            {
                InvalidCounter = InvalidInterval;

                if(DoubleHitCounter)        // 释放,防抖
                {
                    DoubleHitCounter--;
                    ValidCounter = 0;
                    return;
                }

                bKeyPressed=0;

                bLongPressTrigger=0;

                if (ValidCounter < ShortInterval)  return;

                //------------------------------------------------------------------
                if ( ValidCounter == LongInterval )		//释放时,长按键, 置为无效.
                        { KeyValue = 1; }

                else if (ValidCounter >= ShortInterval)
                        { KeyValue = 0; }

                else    { KeyValue = 1; }             	//按键时间,太短,,无效按键!

                ValidCounter=0;                       	//单击按键,只解析执行一次!

                //------------------------------------------------------------------

                if (KeyValue==0)                    	//按键有效=0, 点按, 单击
                {
                    //PostMessage(MessageKey, key);
                    //KeyBeepCounter=KeyBeepInterval;

                    DoubleHitCounter=DoubleHitInterval;

                    bOneClickTrigger=1;
                    
					u8Step100ms=0;
					bTask_step_100ms=0;                    
                }
            }

        }//>{if((pKeyCurr==0)&&(pKeyLast==0)) else }

    }//>{if(bSwitch) else }

}//>{KeyScanPer10ms}


																					

/***********************************************************************************
*|``````````````````````````````````````````````````````````````````````````````````
*|C:编译器 已知BUG(Mk6a12p)
*|1.少用局部变量，可以使用全局变量传参数
*|2.swich语句不要使用（可以使用if  else 代替）
*|3.RAM 现阶段 编译器最少要需要占用9个字节（中断保存 ACC,status,处理函数参数等）
*|4.源代码行数比较多时，编译速度比较慢
*|5.少用 bool 变量
*|__________________________________________________________________________________
************************************************************************************
u8 key_state;
u8 key_zhi;
u8 key_long;

void key_scay(void)
{
    u8 temp;
    temp = PORTB|0xe1;
    temp = ~temp;

    if(key_state== 0)
    {
            //没有按键按下标志

            if (temp)
                {
                    key_state = 1;
                    key_long=5;
                }
            else
                key_state=0;
    }
    else if(key_state== 1)
    {
            //第一次按键按下标志
            if (temp)
                {
                    key_long--;
                    if(key_long==0)
                    {
                    key_state =2;
                    key_zhi=temp;
                    key_long=20;
                    }
                }
            else
                {
                    key_state = 0;

                }
    }
    else if(key_state== 2)
    {
            --key_long;
            if(key_long==0)
            {
                key_state=3;
            }else
            {
                if (temp==0)
                    {
                        key_state = 0;

                    }
            }
    }
    else if(key_state==3)
    {
            ++key_long;
            if(key_long>=20)
            {
                key_long=0;
                if(temp==KEY_INC)
                    key_zhi=KEY_INC;
                if(temp==KEY_DEC)
                    key_zhi=KEY_DEC;
            }
            if(temp==0)
                key_state=0;
    }
    else key_state = 0;
}
//{}
//*/