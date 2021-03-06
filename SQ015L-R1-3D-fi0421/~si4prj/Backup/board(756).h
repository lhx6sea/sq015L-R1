#ifndef     _BOARD_H_               //IOmap.H
#define     _BOARD_H_

//#include "MK6A12P.h"
//#include "typedef.h"

/*
****************************************************************************************
;                            _____________
;                          _|             |_
;                  <P> VDD|_ 1          8  _|VSS <P>
;                          _|             |_
;                  <-> PB5|_ 2          7  _|PB0 <->
;                          _|             |_
;                  <-> PB4|_ 3          6  _|PB1 <->
;                          _|             |_
;                  --> PB3|_ 4          5  _|PB2 <->
;                           |_____________|
;
;---------------------------------------------------------------------------------------
*/

// 1:VDD                         8:VSS
// 2:PB5=电压检测                7:PB0   Speed2档
// 3:PB4=Speed1&LED              6:PB1   Speed3档
// 4:PB3=Key                     5:PB2   移动电源,触发,开

#define TestIO                 	(PORTB4)			

#define Wrk_LED                 (PORTB4)			//指示灯和1档共用
#define Fan_1D                  (PORTB4)
#define Fan_2D                  (PORTB0)
#define Fan_3D                  (PORTB1)

#define _pOverload             	(PORTB5)			//过载保护

#define IP5305_OnOff_0()        {PORTB2=0;}
#define IP5305_OnOff_1()        {PORTB2=1;}


#define _pKeyPin              	(PORTB3)
#define KeyPin                  (3)             	//PB3, only one single key



//#define KeyShift_0()          (PB1=0)
//#define KeyShift_1()          (PB1=1)


//#define RelayPull()           (PB5=1)
//#define RelayOpen()           (PB5=0)
//#define RelayZero()           (PB5=0)




#define WorkLEDon()             {Wrk_LED=1;}
#define WorkLEDoff()            {Wrk_LED=0;}

#define FanSpeed0()             {Fan_1D=0;Fan_2D=0;Fan_3D=0;}
#define FanSpeed1()             {Fan_1D=1;Fan_2D=0;Fan_3D=0;}
#define FanSpeed2()             {Fan_1D=1;Fan_2D=1;Fan_3D=0;}
#define FanSpeed3()             {Fan_1D=1;Fan_2D=0;Fan_3D=1;}

//------------------------------------------------------------------
//FanState
#define FanSpeed_Off            0
#define FanSpeed_5V             1
#define FanSpeed_7V             2
#define FanSpeed_9V             3


/*
****************************************************************************************
#define EXT_SIGNAL_PIN          PB0

#define LED_PIN                 PA3                     //PA3
#define LED_ON                  LED_PIN=1
#define LED_OFF                 LED_PIN=0

#define LA8308_FB_PIN           PA0
#define LA8308_FB_ON            LA8308_FB_PIN=0
#define LA8308_FB_OFF           LA8308_FB_PIN=1

#define LA8308_EN_PIN           PB7
#define LA8308_EN_ON            LA8308_EN_PIN=1
#define LA8308_EN_OFF           LA8308_EN_PIN=0

#define LA8308_OCSET_PIN        PB6
#define LA8308_OCSET_ON         LA8308_OCSET_PIN=0
#define LA8308_OCSET_OFF        LA8308_OCSET_PIN=1

//IIC  定义
#define AT24C02_SDA             PA1                     //PA1
#define AT24C02_SCL             PA2                     //PA2

#define AT24C02_SDA_H           AT24C02_SDA=1
#define AT24C02_SDA_L           AT24C02_SDA=0

#define AT24C02_SCL_H           AT24C02_SCL=1
#define AT24C02_SCL_L           AT24C02_SCL=0

#define AT24C02_SDA_IN          {__asm__("movla 0x02"); __asm__("IODIR PORTA ");}
#define AT24C02_SDA_OUT         {__asm__("movla 0x00"); __asm__("IODIR PORTA ");}
#define AT24C02_DEVICE_WADDR    0xa0
#define AT24C02_DEVICE_RADDR    0xa1


//按键编码
#define KEY_POWER               0x02
#define KEY_ON                  0x10
#define KEY_INC                 0x08
#define KEY_DEC                 0x04


//位变量
#define time_10ms_flag          FLAG1.bbit.bit0
#define power_flag              FLAG1.bbit.bit1
#define led_flag                FLAG1.bbit.bit2
#define eeprom_write_flag       FLAG1.bbit.bit3
#define zero_flag               FLAG1.bbit.bit4
#define zero_back_flag          FLAG1.bbit.bit5
#define out_flag                FLAG1.bbit.bit6
****************************************************************************************
*/
#endif