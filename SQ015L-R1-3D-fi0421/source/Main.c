/*  
****************************************************
			�Ϻ�оʥ���ӹɷ����޹�˾
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
	
	__asm__("clrwdt");          //�忴�Ź�
	PORTB=0X09;		
	DelayXms(90);				// �ϵ���ʱ
	
	__asm__("clrwdt");          //�忴�Ź�
	PORTB=0X09;
	DelayXms(90);				// �ϵ���ʱ
	
	__asm__("clrwdt");          //�忴�Ź�
	PORTB=0X09;
	DelayXms(90);				// �ϵ���ʱ
	
	__asm__("clrwdt");          //�忴�Ź�
	PORTB=0X09;
	DelayXms(90);				// �ϵ���ʱ
	
	__asm__("clrwdt");          //�忴�Ź�
	PORTB=0X09;

	u8addto5s=0;				// ������ʼ��
	FanState=0;
	u8addto5s=0;
	
	InvalidCounter=0;         	// ������ʼ��
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
		
		__asm__("clrwdt");          //�忴�Ź�
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
		if(++u8Step100ms>9)			//Լ 270ms	
		{
			u8Step100ms=0;
			bTask_step_100ms=1;			
		}
		
		
		if(!_pOverVoltage)			//��ѹ��,ֹͣPWM���; ����0��ʼ����
		{
			PWM0OE=1;       		//"1":PWMout��ֹ
			bTask_step_100ms=0;
			u8Step100ms=0;
			PWM0P=0;
		}		
		
		/**************************************/
		if(u8addto5s>=252)
		{
			WDTEN=0;
			__asm__("clrwdt");          //�忴�Ź�
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
			__asm__("clrwdt");          //�忴�Ź�
			WDTEN=1;
			__asm__("clrwdt");          //�忴�Ź�			
					
		}
		
		/**************************************/
		if(FanState==0)					//�ػ�,��,����!
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
