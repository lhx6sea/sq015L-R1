/***************************************************************************************
*|``````````````````````````````````````````````````````````````````````````````````````
*|C:������ ��֪BUG(Mk6a12p)
*|1.���þֲ�����������ʹ��ȫ�ֱ���������
*|2.swich��䲻Ҫʹ�ã�����ʹ��if  else ���棩
*|3.RAM �ֽ׶� ����������Ҫ��Ҫռ��9���ֽڣ��жϱ��� ACC,status,�����������ȣ�
*|4.Դ���������Ƚ϶�ʱ�������ٶȱȽ���
*|5.���� bool ����
*|______________________________________________________________________________________
*/

#include	"include.h"


#define	Fosc        (8)                             //�ڲ�RC����=8Mhz


BIT_BYTE_S        	u8FlagTimer;                    //λ����  ��boar.h  �зֿ��Ķ���

#define bFlag1ms    u8FlagTimer.b0
#define bFlag10ms   u8FlagTimer.b1
#define bFlag100ms  u8FlagTimer.b2
#define bXor10ms    u8FlagTimer.b3

#define bGotoSleep  u8FlagTimer.b7


uint8_t addto10ms;
uint8_t addto100ms;
uint8_t addto11s;       //10s �޲���, ����˯��ģʽ


//======================================================================================
//main pro entry
//------------------------------------------------------------------
void main ( void )
{
    //delay();

    //PORTB=0;
    //PORTA=0;

    //__asm__("movla 0x00");
    //__asm__("IODIR PORTA ");        //__asm__("movam PORTA ");

    //__asm__("movla 0x28");
    //__asm__("IODIR PORTB ");

    //__asm__("movla 0xc2");
    //__asm__("select");              //WDT=20ms; TMR0 Clk/4=1Mhz/8=125Khz


    //�Ĵ���    Bit7	Bit6    Bit5  Bit4  | Bit3  Bit2  Bit1  Bit0
    //SELECT	TMR0_EN	WRT_CNT	SUR0  EDGE0 | PSA   PS2   PS1   PS0

    //PSA��Ԥ��Ƶ�������λ
    //1: Ԥ��Ƶ�����䵽 WDT
    //0: Ԥ��Ƶ�����䵽TMR0        			TMR0 Clk/4=1Mhz/8=125Khz

    //R0��TMR0ʱ��Դ��λ
    //1: �ⲿʱ�����루>ϵͳʱ��  / 8��
    //0:��ϵͳʱ�ӣ�/ 4               		TMR0 Clk/4=1Mhz/8=125Khz

    //ram_clr();

    //1:VDD                         8:VSS
    //2:PB5=��ѹ���                7:PB0   Speed2��
    //3:PB4=Speed1&LED              6:PB1   Speed3��
    //4:PB3=Key                     5:PB2   �ƶ���Դ,����,��

    //SetPBDir(0x28);              		//PB3, PB5 Ϊ����

    //PORTB=0x00;

    //WAKEUP=0x08;                    //PB3 ����
    //PB_PUP=0xDF;                    //PB_PUP=0x1F;

    //TMR0=125;                       //8bit����ʱ��ʱ��/�Զ����� 1ms�ж�
    //IRQM=0x81;                      //TMR0 Clk/4=1Mhz/8=125Khz

    //------------------------------
    
	inital();
	sysinitial();
	    
    //IP5305_OnOff_0();

    FanState=0;
    addto11s=0;
    bGotoSleep=0;
    addto100ms=0;
    		
	while(1)
	{
		__asm__("clrwdt");          //�忴�Ź�
	}


    while(1)
    {
        
        __asm__("clrwdt");          //�忴�Ź�


        if( bFlag1ms )
        {
            bFlag1ms= 0;
            LogicalFlow();          //�߼�����
        }
        

        if( bFlag10ms )
        {
            bFlag10ms= 0;
            KeyScanPer10ms();       //����ɨ��
        }
        

        if( bXor10ms )              //20ms
        {
            HandleKeyPress();       //��������
        }


        if(bFlag100ms )
        {
            bFlag100ms = 0;
            SendSOSsignal();        //S.O.S
        }


        /****************************************************/
        if(bGotoSleep)
        {
			bGotoSleep=0;            			
			_nop();
			_nop();            
			_nop();            
			_nop();
			_nop();            
			_nop();
			_Sleep();
			_nop();
			_nop();
			_nop();            
			_nop();
			_nop();
			_nop();            
        }
        //*/
    }

}

/***************************************************************************************
//RAM ����
//------------------------------------------------------------------
void ram_clr(void)
{
    FSR=0x90;
    while(1)
    {
        INDF=0;
        FSR++;
        if(FSR==0xc0)
        break;
    }
}
***********/

//======================================================================================
//1ms �ж�
//------------------------------------------------------------------
void all_ISR_entry(void) __interrupt 0	
{
    __asm__("clrwdt");
    
	if(PBIF){ PBIF=0; }

	if(T0IF)
	{
		T0IF=0;

	    bFlag1ms=1;
	    
	    TestIO = !TestIO;

		if(u8Pulse200ms>0) u8Pulse200ms--;

	    if(++addto10ms>=10)            	//10ms
	    {
	        addto10ms = 0;
	        bFlag10ms = 1;
	        bXor10ms^=1;

			//if(_pOverload==0)			//���ؼ��
			//{
				//FanState=0;			//ֱ�ӹػ�
			//}

	    }

	    if(++addto100ms>=100)     		//100ms
	    {
	        addto100ms = 0;
	        bFlag100ms = 1;             //0.1s

	        if(FanState==0)
	        {
	            if(++addto11s>=110)   	//�ػ�״̬,10s,�޲���,����!
	            {
	                addto11s=0;
	                bGotoSleep=1;
	                //if( RelayState==9 ) RelayState=0;
	            }
	        }
	        else
	        {
	            addto11s=0;
	            bGotoSleep=0;
	        }

	    }

	    //----------------------------------------------------------------
	    //IRQF = 0;                   	//Clear the timer0 interrupt flag
	}
}


/***************************************************************************************
*|``````````````````````````````````````````````````````````````````````````````````````
*|	S.O.S ����
*|______________________________________________________________________________________
*/
void SendSOSsignal(void)
{


}



/***************************************************************************************
*|``````````````````````````````````````````````````````````````````````````````````````
*|	��������
*|______________________________________________________________________________________
****************************************************************************************
void _mktc_gsinit_startup(void)
{
    __asm

    PAGESEL     _main
    LGOTO       _main

    __endasm;
}
*/