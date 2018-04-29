/***************************************************************************************
*|``````````````````````````````````````````````````````````````````````````````````````
*|C:编译器 已知BUG(Mk6a12p)
*|1.少用局部变量，可以使用全局变量传参数
*|2.swich语句不要使用（可以使用if  else 代替）
*|3.RAM 现阶段 编译器最少要需要占用9个字节（中断保存 ACC,status,处理函数参数等）
*|4.源代码行数比较多时，编译速度比较慢
*|5.少用 bool 变量
*|______________________________________________________________________________________
*/

#include	"include.h"


#define	Fosc        (8)                             //内部RC振荡器=8Mhz


BIT_BYTE_S        	u8FlagTimer;                    //位变量  在boar.h  有分开的定义

#define bFlag1ms    u8FlagTimer.b0
#define bFlag10ms   u8FlagTimer.b1
#define bFlag100ms  u8FlagTimer.b2
#define bXor10ms    u8FlagTimer.b3

#define bGotoSleep  u8FlagTimer.b7


uint8_t addto10ms;
uint8_t addto100ms;
uint8_t addto11s;       //10s 无操作, 进入睡眠模式


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


    //寄存器    Bit7	Bit6    Bit5  Bit4  | Bit3  Bit2  Bit1  Bit0
    //SELECT	TMR0_EN	WRT_CNT	SUR0  EDGE0 | PSA   PS2   PS1   PS0

    //PSA：预分频器分配脚位
    //1: 预分频器分配到 WDT
    //0: 预分频器分配到TMR0        			TMR0 Clk/4=1Mhz/8=125Khz

    //R0：TMR0时钟源脚位
    //1: 外部时钟输入（>系统时钟  / 8）
    //0:（系统时钟）/ 4               		TMR0 Clk/4=1Mhz/8=125Khz

    //ram_clr();

    //1:VDD                         8:VSS
    //2:PB5=电压检测                7:PB0   Speed2档
    //3:PB4=Speed1&LED              6:PB1   Speed3档
    //4:PB3=Key                     5:PB2   移动电源,触发,开

    //SetPBDir(0x28);              		//PB3, PB5 为输入

    //PORTB=0x00;

    //WAKEUP=0x08;                    //PB3 唤醒
    //PB_PUP=0xDF;                    //PB_PUP=0x1F;

    //TMR0=125;                       //8bit倒计时定时器/自动重载 1ms中断
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
		__asm__("clrwdt");          //清看门狗
	}


    while(1)
    {
        
        __asm__("clrwdt");          //清看门狗


        if( bFlag1ms )
        {
            bFlag1ms= 0;
            LogicalFlow();          //逻辑流程
        }
        

        if( bFlag10ms )
        {
            bFlag10ms= 0;
            KeyScanPer10ms();       //按键扫描
        }
        

        if( bXor10ms )              //20ms
        {
            HandleKeyPress();       //按键处理
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
//RAM 清零
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
//1ms 中断
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

			//if(_pOverload==0)			//过载检测
			//{
				//FanState=0;			//直接关机
			//}

	    }

	    if(++addto100ms>=100)     		//100ms
	    {
	        addto100ms = 0;
	        bFlag100ms = 1;             //0.1s

	        if(FanState==0)
	        {
	            if(++addto11s>=110)   	//关机状态,10s,无操作,休眠!
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
*|	S.O.S 函数
*|______________________________________________________________________________________
*/
void SendSOSsignal(void)
{


}



/***************************************************************************************
*|``````````````````````````````````````````````````````````````````````````````````````
*|	启动函数
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