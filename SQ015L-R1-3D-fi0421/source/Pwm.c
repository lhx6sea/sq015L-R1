/*  
************************************************************************
*					上海芯圣电子股份有限公司
*						www.holychip.cn
************************************************************************
*	@Author				LiFei
*	@File				Pwm.c
*	@Library Version	V1.0.0.0
*	@Date				2017.09.06
************************************************************************
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
	PWMCT：PWM0/1/2输出端口配置位 
	PWMCT:=0
	PWM0 配置在 PORTB2 口	Buzzer  ???????????????
	PWM1 配置在 PORTB1 口 
	PWM2 配置在 PORTB0 口 
	
	PWMCT:=1
	PWM0 配置在 PORTA3 口	Buzzer
	PWM1 配置在 PORTA2 口 
	PWM2 配置在 PORTA1 口 
	***********************************/					
	T1IE = 0;
	
	//如果OPTION选择8M/2T; 则Fosc=16M，Fsys=8M，Fcpu=4M。		
	T1 = 79;			//T1计数寄存器 
	T1LOAD = 79;		//T1重载寄存器 
	
	PWM0P = 0;			//PWM0P占空比寄存器 
	PWM1P = 0;			//PWM1P占空比寄存器 
	PWM2P = 0;			//PWM2P占空比寄存器 
	
	//[PWMCON] PWM0OE PWM1OE PWM2OE PWMCK:::PWMMD PWMINV PWM1E PWM2E
	//Bit [4]  PWMCK：T1 时钟倍频选择 
	//0 = T1 时钟不倍频 
	//1 = T1 时钟倍频(T1PR=000 时有效)，此控制位对所有所选 T1 时钟源有效		
	PWMCON = 0x00;		//output PWM 
	
	//{T1CON}  T1EN  PWM0E  BUZE  T1CK1 || T1CK0  T1PR2  T1PR1  T1PR0 	
	T1CON = 0xC8;		//Fpwm=Fsys=8Mhz  ??????????	
}

void pwm3_initial(void)
{
	PWM3CT = 0;			//PWM3-->PB5  端口设定
						//PWM31-->PB4
						//FLT-->PB3
	/********************************************					
	PWM3CT：PWM3/PWM31/FLT 端口配置位 
	PWM3CT=0 
	PWM3  配置在 PORTB5 口 
	PWM31 配置在 PORTB4 口 
	FLT   配置在 PORTB3 口 
	PWM3CT=01
	PWM3  配置在 PORTA0 口 
	PWM31 配置在 PORTB7 口 
	FLT   配置在 PORTB6 口 
	**********************************************/			
					
	//PWM3C  PWM3IE  PWM3IF  FLTS  FLTC || PWM3S[1:0]  PWM3CK[1:0] 
	//PWM3SM[1:0]=00 ;PWM3 和 PWM31 均为高有效 
	//PWM3CK[1:0]=00 ;Fpwm=Fosc/1 					
	PWM3C   = 0x00;
	
	//PWM3周期= [ PWM3P] * PWM3 工作时钟源周期
	PWM3P = 80;			//16Mhz/128=125Khz	7bitPWM
	
	//PWM3 占空比  = [ PWM3D] * PWM3 工作时钟周期 
	PWM3D = 40;
	
	//独立模式下：PWM31 占空比时间  = [ PWM3DT] * PWM3 工作时钟周期 
	PWM3DT = 40;
	
	//PWM3EN:  -  FLT_MODE  EFLT  || PWM3M  PWM31_OEN  PWM3_OEN  PWM3_EN 	
	PWM3EN = 0x00;		//output PWM , 两路独立PWM
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


//======================================================================
//1ms 中断
//----------------------------------------------------------------------
void all_Interrupt_ISR_entry(void) __interrupt 0
{
    __asm__("clrwdt");
    
	_nop();

	if(PBIF)
	{ 
		PBIF=0; 
	}
	
	else if(INTF)
	{
		INTF=0;	
		
		//PWM0OE=1; 		//禁止PWM0 输出
		//FanState=0;	
		//PWM0P = 0;
	}
	
	else if(T0IF)
	{
	
		T0IF=0;
	}
	else
	{
		PBIF=0; 
		INTF=0;
		T0IF=0;
	}
	
}