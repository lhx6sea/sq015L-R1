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


/*
;***********************************************************************
;                            _____________
;                          _|             |_
;                 <P+> VDD|_.1          8 ._|VSS <P->
;                          _|             |_
;                 <--> PB5|_.2          7 ._|PB0 <---
;                          _|             |_
;                 <--> PB4|_.3          6 ._|PB1 <-->
;                          _|             |_
;                 ---> PB3|_.4          5 ._|PB2 <-->
;                           |_____________|
;
;***********************************************************************
*/


void t1_pwm_initial(void)
{
	PWMCT = 0;			//PWM0-->PB2>>>>>>>>>>>>>>>	 
						//PWM1-->PB1
						//PWM2-->PB0
	/*************************************	
	PWMCT��PWM0/1/2����˿�����λ 
	PWMCT:=0
	PWM0 ������ PORTB2 ��	Buzzer  ???????????????
	PWM1 ������ PORTB1 �� 
	PWM2 ������ PORTB0 �� 
	
	PWMCT:=1
	PWM0 ������ PORTA3 ��	Buzzer
	PWM1 ������ PORTA2 �� 
	PWM2 ������ PORTA1 �� 
	***********************************/					
	T1IE = 0;
	
	//���OPTIONѡ��8M/2T; ��Fosc=16M��Fsys=8M��Fcpu=4M��		
	T1 = 79;			//T1�����Ĵ��� 
	T1LOAD = 79;		//T1���ؼĴ��� 
	
	PWM0P = 0;			//PWM0Pռ�ձȼĴ��� 
	PWM1P = 0;			//PWM1Pռ�ձȼĴ��� 
	PWM2P = 0;			//PWM2Pռ�ձȼĴ��� 
	
	//[PWMCON] PWM0OE PWM1OE PWM2OE PWMCK :: PWMMD PWMINV PWM1E PWM2E
	//Bit [4]  PWMCK��T1 ʱ�ӱ�Ƶѡ�� 
	//0 = T1 ʱ�Ӳ���Ƶ 
	//1 = T1 ʱ�ӱ�Ƶ(T1PR=000 ʱ��Ч)���˿���λ��������ѡ T1 ʱ��Դ��Ч		
	PWMCON = 0x00;		//����PWM0����ֹPWM1��PWM2; T1ʱ�ӱ�Ƶ
	
	//{T1CON}  T1EN  PWM0E  BUZE  T1CK1 || T1CK0  T1PR2  T1PR1  T1PR0 	
	T1CON = 0xC8;		//Fpwm=Fsys=8Mhz  ??????????	
}

void pwm3_initial(void)
{
	PWM3CT = 0;			//PWM3-->PB5  �˿��趨
						//PWM31-->PB4
						//FLT-->PB3
	/********************************************					
	PWM3CT��PWM3/PWM31/FLT �˿�����λ 
	PWM3CT=0 
	PWM3  ������ PORTB5 �� 
	PWM31 ������ PORTB4 �� 
	FLT   ������ PORTB3 �� 
	PWM3CT=01
	PWM3  ������ PORTA0 �� 
	PWM31 ������ PORTB7 �� 
	FLT   ������ PORTB6 �� 
	**********************************************/			
					
	//PWM3C  PWM3IE  PWM3IF  FLTS  FLTC || PWM3S[1:0]  PWM3CK[1:0] 
	//PWM3SM[1:0]=00 ;PWM3 �� PWM31 ��Ϊ����Ч 
	//PWM3CK[1:0]=00 ;Fpwm=Fosc/1 					
	PWM3C   = 0x00;
	
	//PWM3����= [ PWM3P] * PWM3 ����ʱ��Դ����
	PWM3P = 80;			//16Mhz/128=125Khz	7bitPWM
	
	//PWM3 ռ�ձ�  = [ PWM3D] * PWM3 ����ʱ������ 
	PWM3D = 40;
	
	//����ģʽ�£�PWM31 ռ�ձ�ʱ��  = [ PWM3DT] * PWM3 ����ʱ������ 
	PWM3DT = 40;
	
	//PWM3EN:  -  FLT_MODE  EFLT  || PWM3M  PWM31_OEN  PWM3_OEN  PWM3_EN 	
	PWM3EN = 0x00;		//output PWM , ��·����PWM
}



/***********************************************************************
#define PWM2E                   PWMCONbits.PWM2E                // bit 0
#define PWM1E                   PWMCONbits.PWM1E                // bit 1
#define PWMINV                  PWMCONbits.PWMINV               // bit 2
#define PWMMD                   PWMCONbits.PWMMD                // bit 3
#define PWMCK                   PWMCONbits.PWMCK                // bit 4
#define PWM2OE                  PWMCONbits.PWM2OE               // bit 5
#define PWM1OE                  PWMCONbits.PWM1OE               // bit 6
#define PWM0OE                  PWMCONbits.PWM0OE               // bit 7
***********************************************************************/


volatile BIT_BYTE_U         u8TimerFlag;      // �ֲ�{λ��}����

#define	bTask_10ms        	u8TimerFlag.bits.b0
#define	bVoltageDropto3V	u8TimerFlag.bits.b1
#define	bLowVoltageState	u8TimerFlag.bits.b2

#define	bVoltageUpto_3_5	u8TimerFlag.bits.b3
#define	bVoltageUpto_3_7	u8TimerFlag.bits.b4
#define	bVoltageUpto_4_1	u8TimerFlag.bits.b5
#define	bVoltageUpto_4_3	u8TimerFlag.bits.b6



//======================================================================
//1ms �ж�
//----------------------------------------------------------------------
void all_Interrupt_ISR_entry(void) __interrupt 0
{    
	//INTFLAG:	- - - - ::  -  INTF  PBIF  T0IF 
	//T0CR:		- - - - ::  -    -   T1IE  T1IF 
	//WDTEN  EIS [LVDF] LVDSEL3 || LVDSEL2 LVDSEL1 LVDSEL0 LVDEN
	_nop();

	if(PBIF)
	{ 
		PBIF=0; 
	}
	
	else if(LVDF)
	{
		LVDF=0;
		
		u8addto5s=0;
		
		SCS=1;					//�͵�ѹ,��Ƶ����
		OPTION=0;
		
		u8Step100ms=0;
		bTask_step_100ms=0;	
		
		bVoltageDropto3V=1;
		bLowVoltageState=1;	
		
		bVoltageUpto_3_5=0;	
		bVoltageUpto_3_7=0;	
		bVoltageUpto_4_1=0;	
		bVoltageUpto_4_3=0;	
		
	}
	
	else if(INTF)
	{
		INTF=0;	
		
		//PWM0OE=1; 			//��ֹPWM0 ���
		//FanState=0;	
		//PWM0P = 0;
	}
	
	else if(T0IF)				//10ms
	{	
		T0IF=0;
		T0=100;					//(256-125);
		
		bTask_10ms=1;
		
		if(bVoltageUpto_3_5)	//50ms, �ָ�һ�ε�ѹ
		{
			bVoltageUpto_3_5=0;	//upto to 3.7V
			LVDF=0;
			PCON= ((PCON&0xE1)|LVD_3_7V);			
			bVoltageUpto_3_7=1;					
		}
		
		if(bVoltageUpto_3_7)	//50ms, �ָ�һ�ε�ѹ
		{
			bVoltageUpto_3_7=0;	//upto to 4.1V
			LVDF=0;
			PCON= ((PCON&0xE1)|LVD_4_1V);			
			bVoltageUpto_4_1=1;					
		}
		
		if(bVoltageUpto_4_1)	//50ms, �ָ�һ�ε�ѹ
		{
			bVoltageUpto_4_1=0;	//upto to 4.3V
			LVDF=0;
			PCON= ((PCON&0xE1)|LVD_4_3V);			
			bVoltageUpto_4_3=1;					
		}
		
		
		if(bVoltageUpto_4_3)	//���,�ָ�,��Ƶ����ģʽ
		{
			bVoltageUpto_4_3=0;	//upto to 4.3V
			LVDF=0;
			PCON= ((PCON&0xE1)|LVD_3_0V);
						
			bLowVoltageState=0;	
			SCS=0;
			OPTION=6;				
		}						
			
		
		TestIO_5=!TestIO_5;		//whil(1)=10ms	
		
		
		/********************************************/			
		if(++u8Step100ms>=10)	//Լ 100ms; ��Ƶ 500ms	
		{
			u8Step100ms=0;
			bTask_step_100ms=1;	
			
			if(bVoltageDropto3V)
			{
				bVoltageDropto3V=0;		//500ms,��,���Իָ�
				LVDF=0;
				PCON= ((PCON&0xE1)|LVD_3_5V);
				
				bVoltageUpto_3_5=1;
			
			}
			
			
			
		
			/**************************************/
			if(FanState==0)			//�ػ�����?
			{
				if(++u8addto5s>99)	//�ػ�,10s,����
				{
					_nop();
					u8addto5s=111;	
					_nop();
				}		
			}		
			else
			{
				u8addto5s=0;
			}
			/**************************************/			
					
		}		
				
	}
	
	else
	{
		PBIF=0; 
		INTF=0;
		T0IF=0;
	}
	
}

//{}
//*/