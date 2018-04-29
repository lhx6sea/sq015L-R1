/***********************************************************************
*|``````````````````````````````````````````````````````````````````````
*|C:������ ��֪BUG(Mk6a12p)
*|1.���þֲ�����������ʹ��ȫ�ֱ���������
*|2.swich��䲻Ҫʹ�ã�����ʹ��if  else ���棩
*|3.RAM �ֽ׶� ����������ռ��9���ֽ�(�жϱ���ACC,status,������������)
*|4.Դ���������Ƚ϶�ʱ�������ٶȱȽ���
*|5.���� bool ����
*|______________________________________________________________________
*/
#include	"include.h"

/***********************************************************************
#define ShortInterval       5     				// �̰������ >= 2
#define LongInterval        66   				// ���������
#define DoubleHitInterval   5      				// ��˫���������

#define InvalidInterval     5      				// ??????
#define KeyBeepInterval     5      				// ?????

#define PreSet1    			(1)
#define KeyPort     		PORTB


__BIT_BYTE_U    ubFlagKey; 		  				// �ֲ�{λ��}����

#define Switch      		ubFlagKey.bits.b0
#define PinValue		    ubFlagKey.bits.b1
#define ScanPins    		ubFlagKey.bits.b2
#define ScanData    		ubFlagKey.bits.b3
#define KeyValue	      	ubFlagKey.bits.b4

#define _bKeyPressed		ubFlagKey.bits.b7


extern uint8_t FanState;
extern uint8_t RelayState;
extern uint8_t addto20s;


uint8_t InvalidCounter;                 		// ������ЧCount
uint8_t ValidCounter;           				// ������ЧCount
uint8_t DoubleHitCounter;       	    		// ��ֹ����˫��
************************************************************************
*/

//const u8  DutyTable[]={0,4,13,23,31,0};
const u8  DutyTable[]={0,4,19,29,0};


/***********************************************************************
*|``````````````````````````````````````````````````````````````````````
*|  void LogicalFlow(void)       	�߼�����
*|______________________________________________________________________
*/
void LogicalFlow(void)           	//run@1ms
{

    if( FanState == 0 )                     //�ػ�
    {
        LED_close();
        PWM0P = 0;

        if(bTask_step_100ms)                //��ʱ�ر�,���; �ø�ѹ��ʧ
        {
            FanSpeed0();
        }
    }

    if( FanState == 1 )                     //����1��
    {
        LED_1D();
        FanSpeed1();

        if(bTask_step_100ms)
        {
            PWM0OE=0;       //"0":PWM���     //fi0331
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

    if( FanState == 2 )                     //����2��
    {
        LED_2D_3D();
        FanSpeed2();

        if(bTask_step_100ms)
        {
            PWM0OE=0;       //"0":PWM���     //fi0331
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


    if( FanState == 3 )                     //����3��
    {
        LED_2D_3D();
        FanSpeed3();

        if(bTask_step_100ms)
        {
            PWM0OE=0;       //"0":PWM���     //fi0331
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
    if( FanState == 4 )                     //����4��
    {
        LED_2D_3D();
        FanSpeed4();

        if(bTask_step_100ms)
        {
            PWM0OE=0;       //"0":PWM���     //fi0331
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
    //if( FanState==FanSpeed_Off )          //�ػ�
    {
        //WorkLEDon();
        //WorkLEDoff();

        if(bIP5305OnOffTrigger)             //����,����,����,������,��ѹ���
        {
            if(u8Step100ms)
            {
                //IP5305_OnOff_1();
                _nop();
            }
            else
            {
                //IP5305_OnOff_0();
                bIP5305OnOffTrigger=0;      //�������� 200ms
            }
        }
    }
    //*/


    /***************************************
    else if( FanState>=1 )
    {
        WorkLEDon();

        if(bKeyShiftTriggle)                //shift����
        {
            if(u8pulse200ms) KeyShift_0();
            else
            {
                KeyShift_1();
                bKeyShiftTriggle=0;         //�������� 200ms
            }
        }

    }
    ***************************************/

}//>{LogicalFlow}


/***********************************************************************
*|``````````````````````````````````````````````````````````````````````
*|  void LogicalFlow(void)             		�߼�����
*|______________________________________________________________________
*/
void HandleKeyPress(void)              		//10ms
{

    if(bOneClickTrigger)           			//����
    {
        bOneClickTrigger=0;

        u8Step100ms=0;
        bTask_step_100ms=0;

        if(FanState>0)                      //������ſ��Ե���,fi0225
        {

            if(++FanState>=4)               //0,1,2,3,4,5(0)
            {
                FanState=0;                 //��λ                
            }

            /*******************************
            else
            {
                bIP5305OnOffTrigger=1;      //200ms, �͵�ƽ
                u8Step100ms=200;
            }
            *******************************/
        }
    }


    if(bLongPressTrigger)                   //����
    {
        bLongPressTrigger=0;

        u8Step100ms=0;
        bTask_step_100ms=0;

        //if(FanState > 0)      //�ػ�
        //{
        //    FanState=0;
        //}

        //else

        if(FanState==0)         //����,,��,�ƶ���Դ
        {
            FanState=1;

            //bIP5305OnOffTrigger=1;          //200ms, �͵�ƽ
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