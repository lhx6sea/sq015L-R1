/***************************************************************************************
*|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
*|C:������ ��֪BUG
*|1.���þֲ�����������ʹ��ȫ�ֱ���������
*|2.swich��䲻Ҫʹ�ã�����ʹ��if  else ���棩
*|3.RAM �ֽ׶� ����������Ҫ��Ҫռ��9���ֽڣ��жϱ��� ACC,status,�����������ȣ�
*|4.Դ���������Ƚ϶�ʱ�������ٶȱȽ���
*|5.���� bool ����
*|______________________________________________________________________________________ 
*/
#include	"include.h"

//extern  uint8_t         addto20s;








/*********************************************************************
#define ShortInterval       5           // �̰�������� >= 2
#define LongInterval        66          // �����������
#define DoubleHitInterval   5           // ������˫���󶯼��

#define InvalidInterval     5           // ??????
#define KeyBeepInterval     5           // ?????

#define PreSet1    			(1)
#define KeyPort     		PORTB		// PB3/FanSpeed3	PB0/LED_SOS


__BIT_BYTE_U    ubFlagKey; 		        // �ֲ�{λ��}����

#define Switch      		ubFlagKey.bits.b0
#define PinValue		    ubFlagKey.bits.b1
#define ScanPins    		ubFlagKey.bits.b2
#define ScanData    		ubFlagKey.bits.b3
#define KeyValue	      	ubFlagKey.bits.b4

#define _bKeyPressed		ubFlagKey.bits.b7


extern uint8_t FanState;
extern uint8_t RelayState;
extern uint8_t addto20s;


uint8_t InvalidCounter;                 // ������ЧCount
uint8_t ValidCounter;           		// ������ЧCount
uint8_t DoubleHitCounter;       	    // ��ֹ����˫��
*/



/***************************************************************************************
*|``````````````````````````````````````````````````````````````````````````````````````
*|  void LogicalFlow(void)              �߼�����           
*|______________________________________________________________________________________ 
*/
void LogicalFlow(void)                  //@1ms
{

    if( FanState == 0 )                 //�ػ�
    {
        WorkLEDoff();
        FanSpeed0();
    }

    if( FanState == 1 )                 //����1��
    {
        WorkLEDon();
        FanSpeed1();
    }

    if( FanState == 2 )                 //����2��
    {
        WorkLEDon();
        FanSpeed2();
    }


    if( FanState == 3 )                 //����3��
    {
        WorkLEDon();
        FanSpeed3();
    }


	//if( FanState==FanSpeed_Off )		//�ػ�
	{
        //WorkLEDon();
        //WorkLEDoff();
		
        if(bIP5305OnOffTrigger)      	//����,����,����,������,��ѹ���
		{
			if(u8pulse200ms) 
            {
                IP5305_OnOff_1();
            }
			else
			{
				IP5305_OnOff_0();
				bIP5305OnOffTrigger=0;	//�������� 200ms
			}
		}

    }


	/***********************************************
    else if( FanState>=1 ) 
	{
        WorkLEDon();

        if(bKeyShiftTriggle)		  	//shift����
        {
			if(u8pulse200ms) KeyShift_0();
			else
			{
				KeyShift_1();
				bKeyShiftTriggle=0;     //�������� 200ms
			}
		}

    } 
    /*/   

}


/***************************************************************************************
*|``````````````````````````````````````````````````````````````````````````````````````
*|  void LogicalFlow(void)             		�߼�����           
*|______________________________________________________________________________________ 
*/
void HandleKeyPress(void)              		//10ms
{
    
    if(bOneClickTrigger)           			//����
    {
        bOneClickTrigger=0;

		if(FanState>0)						//������ſ��Ե���,fi0225
        {
            
            FanState++;                   	//����
            if(FanState>=4)
            {
                FanState=0;
			}
            else
            {
                bIP5305OnOffTrigger=1;		//200ms, �͵�ƽ
                u8pulse200ms=200;
            }
        }        
    }

    
    if(bLongPressTrigger)                   //����
    {
        bLongPressTrigger=0;

        if(FanState > 0)                    //�ػ�
        {
            FanState=0;
        }

        else	//if(FanState==0)   		//�ػ�,����,��,�ƶ���Դ
        {
			FanState=1;
            bIP5305OnOffTrigger=1;          //200ms, �͵�ƽ
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