/*  
****************************************************
			上海芯圣电子股份有限公司
				www.holychip.cn
****************************************************
	@Author				LiFei
	@File				delay.c
	@Library Version	V1.0.0.0
	@Date				2017.09.06
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
	
	TestIO_5=1;
	
	__asm__("clrwdt");          //清看门狗
	PORTB=0X09;		
	DelayXms(90);				// 上电延时
	
	__asm__("clrwdt");          //清看门狗
	PORTB=0X09;
	DelayXms(90);				// 上电延时
	
	__asm__("clrwdt");          //清看门狗
	PORTB=0X09;
	DelayXms(90);				// 上电延时
	
	__asm__("clrwdt");          //清看门狗
	PORTB=0X09;
	DelayXms(90);				// 上电延时
	
	__asm__("clrwdt");          //清看门狗
	PORTB=0X09;

	u8addto5s=0;				// 变量初始化
	FanState=0;
	u8addto5s=0;
	
	InvalidCounter=0;         	// 变量初始化
	ValidCounter=0;           	
	DoubleHitCounter=0; 
			
	bOneClickTrigger=0;
	bLongPressTrigger=0;	
	DoubleHitCounter=3;			
	
	GIE=1; 	     	
		
	while(1)
	{
		
		if(FanState)
		TestIO_5=!TestIO_5;			//whil(1)=10ms
		else
		TestIO_5=0;
		
		__asm__("clrwdt");          //清看门狗
		_nop();
		DelayXms(15);
		_nop();
		KeyScanPer10ms();
		_nop();
		DelayXms(15);
		_nop();
		LogicalFlow();
		_nop();		
		DelayXms(15);
		_nop();
		HandleKeyPress();
		_nop();	
		_nop();
		
		/**************************************/			
		if(++u8Step100ms>9)			//约 270ms	
		{
			u8Step100ms=0;
			bTask_step_100ms=1;			
		}
		
		
		if(!_pOverVoltage)			//过压后,停止PWM输出; 并从0开始增加
		{
			PWM0OE=1;       		//"1":PWMout禁止
			bTask_step_100ms=0;
			u8Step100ms=0;
			PWM0P=0;
		}		
		
		/**************************************/
		if(u8addto5s>=252)
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
		
		/**************************************/
		if(FanState==0)					//关机,才,休眠!
		{
			if(++u8addto5s>=252)
			{
				_nop();
				u8addto5s=253;	
				_nop();
			}		
		}		
		else
		{
			u8addto5s=0;
		}
		/**************************************/		
		
	}//>{while(1)}
	
}//>{main}
//**********************************************************************
//^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v
//*/
