/***********************************************************************************
*|``````````````````````````````````````````````````````````````````````````````````
*|C:������ ��֪BUG(Mk6a12p)
*|1.���þֲ�����������ʹ��ȫ�ֱ���������
*|2.swich��䲻Ҫʹ�ã�����ʹ��if  else ���棩
*|3.RAM �ֽ׶� ����������Ҫ��Ҫռ��9���ֽڣ��жϱ��� ACC,status,�����������ȣ�
*|4.Դ���������Ƚ϶�ʱ�������ٶȱȽ���
*|5.���� bool ����
*|__________________________________________________________________________________
*/
#include "include.h"

#define ShortInterval       3               // �̰���ʱ�� >= 2
#define LongInterval        99             	// ������ʱ��
#define DoubleHitInterval   3               // ������˫������, ���ְ���,��ӦҪ��!

#define InvalidInterval     3               // �����ͷ�,������
#define KeyBeepInterval     5               // ������

#define KeyNull             (1)
#define KeyPort             PORTB           // PB3/FanSpeed3    PB0/LED_SOS


volatile BIT_BYTE_S         u8FlagKey;      // �ֲ�{λ��}����

#define bSwitch             u8FlagKey.b0
#define pKeyLast            u8FlagKey.b1    //PinValue
#define pKeyCurr            u8FlagKey.b2    //ScanPins
//#define pKeyData            u8FlagKey.b3  //ScanData
#define KeyValue            u8FlagKey.b3
#define bKeyPressed         u8FlagKey.b4


//----------------------------------------------------------------------------------
//ȫ�ֱ���
volatile uint8_t            FanState;
volatile uint8_t            u8Step100ms;

//volatile BIT_BYTE_S     	ubKeyTrigger;   // ȫ��{λ��}����, �� data.h ����ϸ����

volatile uint8_t InvalidCounter;            // ������ЧCount
volatile uint8_t ValidCounter;              // ������ЧCount
volatile uint8_t DoubleHitCounter;          // ��ֹ�ͷŶ���

//uint8_t KeyPressedCnt;                    // �������¼�����

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
        //pKeyCurr =  KeyNull;              // PB3 ����, KeyPin=3
        //PinValue =  (KeyPort&(1<<KeyPin));
        pKeyLast = pKeyCurr;
        pKeyCurr = PORTB3;
    }
    else                                    // run@20ms
    {
    	bSwitch=1;
        if((pKeyCurr==0)&&(pKeyLast==0))    // KeyValid=0;
        {
            //pKeyData = pKeyCurr;          // ��ȡ�������� ScanData
            InvalidCounter = 0;

            u8addto5s=0;                    // ������,������,������!
            
            //bTask_step_100ms=0;

            if (++ValidCounter >= LongInterval)
            {
                ValidCounter=LongInterval;  // ����

                if(!bKeyPressed)            // ������������,ִֻ��һ��(����)
                {
                    bKeyPressed=1;
                    bLongPressTrigger=1;
                    
                    
					u8Step100ms=0;
					bTask_step_100ms=0; 
					                    
                    //_StopReqSignal=1;     // ͣ��,�ذ�
                }
            }

        }//if((pKeyCurr==0)&&(pKeyLast==0))

        else                                // ���ֺ�,������ֵ(����)
        {
            InvalidCounter++;               // �����ͷż�����

            if (InvalidCounter >= InvalidInterval)
            {
                InvalidCounter = InvalidInterval;

                if(DoubleHitCounter)        // �ͷ�,����
                {
                    DoubleHitCounter--;
                    ValidCounter = 0;
                    return;
                }

                bKeyPressed=0;

                bLongPressTrigger=0;

                if (ValidCounter < ShortInterval)  return;

                //------------------------------------------------------------------
                if ( ValidCounter == LongInterval )		//�ͷ�ʱ,������, ��Ϊ��Ч.
                        { KeyValue = 1; }

                else if (ValidCounter >= ShortInterval)
                        { KeyValue = 0; }

                else    { KeyValue = 1; }             	//����ʱ��,̫��,,��Ч����!

                ValidCounter=0;                       	//��������,ֻ����ִ��һ��!

                //------------------------------------------------------------------

                if (KeyValue==0)                    	//������Ч=0, �㰴, ����
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
*|C:������ ��֪BUG(Mk6a12p)
*|1.���þֲ�����������ʹ��ȫ�ֱ���������
*|2.swich��䲻Ҫʹ�ã�����ʹ��if  else ���棩
*|3.RAM �ֽ׶� ����������Ҫ��Ҫռ��9���ֽڣ��жϱ��� ACC,status,�����������ȣ�
*|4.Դ���������Ƚ϶�ʱ�������ٶȱȽ���
*|5.���� bool ����
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
//{}
//*/