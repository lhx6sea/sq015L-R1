/***************************************************************************************
*|``````````````````````````````````````````````````````````````````````````````````````
*|C:编译器 已知BUG
*|1.少用局部变量，可以使用全局变量传参数
*|2.swich语句不要使用（可以使用if  else 代替）
*|3.RAM 现阶段 编译器最少要需要占用9个字节（中断保存 ACC,status,处理函数参数等）
*|4.源代码行数比较多时，编译速度比较慢
*|5.少用 bool 变量
*|______________________________________________________________________________________
*/
#include "include.h"

#define ShortInterval       5               // 短按按键间隔 >= 2
#define LongInterval        66              // 长按按键间隔
#define DoubleHitInterval   5               // 防按键双击误动间隔

#define InvalidInterval     5               // ??????
#define KeyBeepInterval     5               // ?????

#define PreSet1             (1)
#define KeyPort             PORTB           // PB3/FanSpeed3    PB0/LED_SOS


BIT_BYTE_S    ubFlagKey;                  	// 局部{位域}变量

#define bSwitch             ubFlagKey.b0
#define PinValue            ubFlagKey.b1
#define ScanPins            ubFlagKey.b2
#define ScanData            ubFlagKey.b3
#define KeyValue            ubFlagKey.b4

#define _bKeyPressed        ubFlagKey.b7


//--------------------------------------------------------------------------------------
//全局变量
volatile uint8_t			FanState;

volatile uint8_t 			u8pulse200ms;
BIT_BYTE_S    				ubKeyTrigger;	// 全局{位域}变量, 在 data.h 有详细定义



volatile uint8_t InvalidCounter;            // 按键无效Count
volatile uint8_t ValidCounter;              // 按键有效Count
volatile uint8_t DoubleHitCounter;          // 防止释放抖动

//uint8_t KeyPressedCnt;                    // 按键按下计数器

/***************************************************************************************
*|``````````````````````````````````````````````````````````````````````````````````````
*|  void KeyScanPer10ms(void)
*|______________________________________________________________________________________
*/
void KeyScanPer10ms(void)                   // chk@10ms
{
    bSwitch = !bSwitch;

    if ( bSwitch )                          // run@20ms
    {
        PinValue =  PreSet1;
        PinValue =  (KeyPort&(1<<3));       // PB3 按键
        ScanPins =  PinValue;
    }
    else                                    // run@20ms
    {
        if( !ScanPins )          // invalidkey=1; validkey=0; PreSet1=1
        {
            ScanData = ScanPins;            // 获取按键数据 ScanData
            InvalidCounter = 0;

            if (++ValidCounter >= LongInterval) //长按
            {
                ValidCounter = LongInterval;

                if(!_bKeyPressed)          // 按键持续按下,只执行一次(功能)
                {
                    _bKeyPressed=1;
                    bLongPressTrigger=1;
                }
            }

        }//if(ScanPins != PreSet1)

        else                                // 松手后,发出键值(单击)
        {
            InvalidCounter++;               // 按键释放计数器

            if (InvalidCounter >= InvalidInterval)
            {
                InvalidCounter = InvalidInterval;

                if(DoubleHitCounter)
                {
                    DoubleHitCounter--;
                    ValidCounter = 0;
                    return;
                }

                _bKeyPressed=0;
                bLongPressTrigger=0;

                if (ValidCounter < ShortInterval)  return;

                //----------------------------------------------------------------------
                if ( ValidCounter == LongInterval )         //释放时,长按键, 置为无效.
                        { KeyValue = 1; }

                else if (ValidCounter >= ShortInterval)
                        { KeyValue = 0; }

                else    { KeyValue = 1; }                   //按键时间,太短,,无效按键!

                ValidCounter=0;                             //单击按键,只解析执行一次!

                //----------------------------------------------------------------------

                if (!KeyValue)                          //按键有效=0, 点按, 单击
                {
                    //PostMessage(MessageKey, key);
                    //KeyBeepCounter = KeyBeepInterval;

                    DoubleHitCounter = DoubleHitInterval;

                    bOneClickTrigger=1;

                }

            }

        }// if(ScanPins != PreSet1) else

    }// if(Switch) else

}//void KeyScanPer10ms(void)




/***************************************************************************************
*|``````````````````````````````````````````````````````````````````````````````````````
*|C:编译器 已知BUG
*|1.少用局部变量，可以使用全局变量传参数
*|2.swich语句不要使用（可以使用if  else 代替）
*|3.RAM 现阶段 编译器最少要需要占用9个字节（中断保存 ACC,status,处理函数参数等）
*|4.源代码行数比较多时，编译速度比较慢
*|5.少用 bool 变量
*|______________________________________________________________________________________
****************************************************************************************
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
//*/