ifndef _typedef_H_
#define _typedef_H_


typedef unsigned char   u8;
typedef unsigned char   uint8_t;
typedef signed char     s8;
typedef unsigned short  u16;
typedef signed char     s16;
typedef unsigned long   u32;
typedef signed long     s32;


//typedef bool bit;                 //*|5.���� bool ����                


typedef	struct strVarName
{
	unsigned	b0:1;
	unsigned 	b1:1;
	unsigned 	b2:1;
	unsigned 	b3:1;
	unsigned	b4:1;
	unsigned 	b5:1;
	unsigned 	b6:1;
	unsigned 	b7:1;

}	BIT_BYTE_S; 			//λ��ṹ�帴�����ͱ���


/***************************************************
//``````````````````````````````````````````````````
typedef union  unionVarName
{
	struct
	{
		unsigned	bit0:1;
		unsigned 	bit1:1;
		unsigned 	bit2:1;
		unsigned 	bit3:1;
		unsigned	bit4:1;
		unsigned 	bit5:1;
		unsigned 	bit6:1;
		unsigned 	bit7:1;
	
	}bbit; 
	
	u8 byte; 
    
}	BIT_BYTE_U;
//__________________________________________________
***************************************************/

#endif