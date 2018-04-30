/*
****************************************************
			中山凯鑫德电子股份有限公司
				www.freeyes.net
====================================================
@名字     	inital.c
@说明      	
@作者		lhx6sea
@日期		2018.04.29
****************************************************
*/



#include "include.h"



volatile uint8_t		u8addto5s;





void main( void )
{

	GIE=0; 	
	
	inital();
	sysinitial();
		
	t1_pwm_initial();
	pwm3_initial();	
		
	
	u8addto5s=0;				// 变量初始化
	FanState=0;
	u8addto5s=0;
	
	InvalidCounter=0;         	// 变量初始化
	ValidCounter=0;           	
	DoubleHitCounter=0; 
			
	bOneClickTrigger=0;
	bLongPressTrigger=0;	
	DoubleHitCounter=3;	
	
	u8Step100ms=0;
	bTask_step_100ms=0;	
	
	TestIO_5=1;		
	
	GIE=1; 	
	
	while(!bTask_step_100ms) 		//上电延时 100ms
	{	
		__asm__("clrwdt");   		//清看门狗
		PORTB=0X09;	
		bTask_10ms=0;	
	}    	
		
	while(1)
	{
		
		/*
		if(FanState)
		TestIO_5=!TestIO_5;			//whil(1)=10ms
		else
		TestIO_5=0;
		*/
		
		__asm__("clrwdt");          //清看门狗
		
		
		if(bTask_10ms)
		{
			bTask_10ms=0;
					
			//DelayXms(15);
			_nop();
			LogicalFlow();
			_nop();		
			//DelayXms(15);
			_nop();
			HandleKeyPress();
			_nop();	
			_nop();
			
			_nop();
			//DelayXms(15);
			_nop();
			KeyScanPer10ms();
			_nop();			
		
		}	
		
		if(!_pOverVoltage)			//过压后,停止PWM输出; 并从0开始增加
		{
			
			bTask_step_100ms=0;
			u8Step100ms=0;
			
			PWM0OE=1;       		//"1":PWMout禁止
			PWM0P=0;
			PORTB2=0;
			PWMCK=0;
        			
		}		
		
		/**************************************/
		if(u8addto5s>=111)
		{
			WDTEN=0;
			__asm__("clrwdt");          //清看门狗
			u8addto5s=0;
			_nop();
			_nop();
			_nop();
			TestIO_5=1;
			_nop();
			_Sleep();
			_nop();
			_nop();
			_nop();
			_nop();
			__asm__("clrwdt");          //清看门狗
			WDTEN=1;
			__asm__("clrwdt");          //清看门狗			
					
		}
				
	}//>{while(1)}
	
}//>{main}

//{}
//*/
