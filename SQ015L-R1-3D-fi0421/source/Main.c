/*
****************************************************
			��ɽ���εµ��ӹɷ����޹�˾
				www.freeyes.net
====================================================
@����     	inital.c
@˵��      	
@����		lhx6sea
@����		2018.04.29
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
		
	
	u8addto5s=0;				// ������ʼ��
	FanState=0;
	u8addto5s=0;
	
	InvalidCounter=0;         	// ������ʼ��
	ValidCounter=0;           	
	DoubleHitCounter=0; 
			
	bOneClickTrigger=0;
	bLongPressTrigger=0;	
	DoubleHitCounter=3;	
	
	u8Step100ms=0;
	bTask_step_100ms=0;	
	
	TestIO_5=1;		
	
	GIE=1; 	
	
	while(!bTask_step_100ms) 		//�ϵ���ʱ 100ms
	{	
		__asm__("clrwdt");   		//�忴�Ź�
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
		
		__asm__("clrwdt");          //�忴�Ź�
		
		
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
		
		if(!_pOverVoltage)			//��ѹ��,ֹͣPWM���; ����0��ʼ����
		{
			
			bTask_step_100ms=0;
			u8Step100ms=0;
			
			PWM0OE=1;       		//"1":PWMout��ֹ
			PWM0P=0;
			PORTB2=0;
			PWMCK=0;
        			
		}		
		
		/**************************************/
		if(u8addto5s>=111)
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
				
	}//>{while(1)}
	
}//>{main}

//{}
//*/
