/***************************************************************************************
*|``````````````````````````````````````````````````````````````````````````````````````
*|C:������ ��֪BUG
*|1.���þֲ�����������ʹ��ȫ�ֱ���������
*|2.swich��䲻Ҫʹ�ã�����ʹ��if  else ���棩
*|3.RAM �ֽ׶� ����������Ҫ��Ҫռ��9���ֽڣ��жϱ��� ACC,status,�����������ȣ�
*|4.Դ���������Ƚ϶�ʱ�������ٶȱȽ���
*|5.���� bool ����
*|______________________________________________________________________________________
*/
#include "include.h"

#define ShortInterval       5               // �̰�������� >= 2
#define LongInterval        66              // �����������
#define DoubleHitInterval   5               // ������˫���󶯼��

#define InvalidInterval     5               // ??????
#define KeyBeepInterval     5               // ?????

#define PreSet1             (1)
#define KeyPort             PORTB           // PB3/FanSpeed3    PB0/LED_SOS


BIT_BYTE_S    ubFlagKey;                  	// �ֲ�{λ��}����

#define bSwitch             ubFlagKey.b0
#define PinValue            ubFlagKey.b1
#define ScanPins            ubFlagKey.b2
#define ScanData            ubFlagKey.b3
#define KeyValue            ubFlagKey.b4

#define _bKeyPressed        ubFlagKey.b7


//--------------------------------------------------------------------------------------
//ȫ�ֱ���
volatile uint8_t			FanState;

volatile uint8_t 			u8pulse200ms;
BIT_BYTE_S    				ubKeyTrigger;	// ȫ��{λ��}����, �� data.h ����ϸ����



volatile uint8_t InvalidCounter;            // ������ЧCount
volatile uint8_t ValidCounter;              // ������ЧCount
volatile uint8_t DoubleHitCounter;          // ��ֹ�ͷŶ���

//uint8_t KeyPressedCnt;                    // �������¼�����

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
        PinValue =  (KeyPort&(1<<3));       // PB3 ����
        ScanPins =  PinValue;
    }
    else                                    // run@20ms
    {
        if( !ScanPins )          // invalidkey=1; validkey=0; PreSet1=1
        {
            ScanData = ScanPins;            // ��ȡ�������� ScanData
            InvalidCounter = 0;

            if (++ValidCounter >= LongInterval) //����
            {
                ValidCounter = LongInterval;

                if(!_bKeyPressed)          // ������������,ִֻ��һ��(����)
                {
                    _bKeyPressed=1;
                    bLongPressTrigger=1;
                }
            }

        }//if(ScanPins != PreSet1)

        else                                // ���ֺ�,������ֵ(����)
        {
            InvalidCounter++;               // �����ͷż�����

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
                if ( ValidCounter == LongInterval )         //�ͷ�ʱ,������, ��Ϊ��Ч.
                        { KeyValue = 1; }

                else if (ValidCounter >= ShortInterval)
                        { KeyValue = 0; }

                else    { KeyValue = 1; }                   //����ʱ��,̫��,,��Ч����!

                ValidCounter=0;                             //��������,ֻ����ִ��һ��!

                //----------------------------------------------------------------------

                if (!KeyValue)                          //������Ч=0, �㰴, ����
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
*|C:������ ��֪BUG
*|1.���þֲ�����������ʹ��ȫ�ֱ���������
*|2.swich��䲻Ҫʹ�ã�����ʹ��if  else ���棩
*|3.RAM �ֽ׶� ����������Ҫ��Ҫռ��9���ֽڣ��жϱ��� ACC,status,�����������ȣ�
*|4.Դ���������Ƚ϶�ʱ�������ٶȱȽ���
*|5.���� bool ����
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
            //û�а������±�־

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
            //��һ�ΰ������±�־
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