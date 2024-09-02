#ifndef __MACRO_H__
#define __MACRO_H__
/*******************************************************************************/
/***************************** 数组大小 ****************************************/
#define	MTABSIZE(x)	(sizeof(x)/sizeof(x[0]))
/*******************************************************************************/
#define	MIRQ_enable()	__enable_irq()		//中断使能
#define	MIRQ_disable()	__disable_irq()		//中断禁止
/*********************************************************************************/
#define MVopData_L(x)  do{GPIO_ResetBits(GPIOD, GPIO_Pin_2);}while(0)
#define MVopData_H(x) do{GPIO_SetBits(GPIOD, GPIO_Pin_2);}while(0)
/*********************************************************************************/
#define M485TR_T(x) do{GPIO_SetBits(GPIOB, GPIO_Pin_4);}while(0)
#define M485TR_R(x) do{GPIO_ResetBits(GPIOB, GPIO_Pin_4);}while(0)
/*********************************************************************************/
#define Mset_bit(var, offset) do{	\
        ((var) |= (1 << (offset))); \
    }while(0)
    
#define Mreset_bit(var, offset) do{	\
    ((var) &= ~(1 << (offset))); \
    }while(0)

#define Mget_bit(var, offset) \
    !(!((var) & (1 << (offset))))
/*********************************************************************************/
#define	MCOMMENT(x)
/*********************************************************************************/
/** Note: LED1-MCU pin different from LED printing **/
#define MFAULTLED2_OFF(x) do{GPIO_SetBits(GPIOC, GPIO_Pin_4);}while(0)    // fault LED2
#define MFAULTLED2_ON(x) do{GPIO_ResetBits(GPIOC, GPIO_Pin_4);}while(0)

#define MSTANDARDLED3_OFF(x) do{GPIO_SetBits(GPIOC, GPIO_Pin_5);}while(0)    // standard LED3
#define MSTANDARDLED3_ON(x) do{GPIO_ResetBits(GPIOC, GPIO_Pin_5);}while(0)

#define MHIGHPOWERLED4_OFF(x) do{GPIO_SetBits(GPIOC, GPIO_Pin_6);}while(0)    // strong LED4
#define MHIGHPOWERLED4_ON(x) do{GPIO_ResetBits(GPIOC, GPIO_Pin_6);}while(0)

#define MCLEANLED5_OFF(x) do{GPIO_SetBits(GPIOC, GPIO_Pin_7);}while(0)    // clean LED5
#define MCLEANLED5_ON(x) do{GPIO_ResetBits(GPIOC, GPIO_Pin_7);}while(0)

#define MCHARGELED6_OFF(x) do{GPIO_SetBits(GPIOD, GPIO_Pin_1);}while(0)    // charging LED6
#define MCHARGELED6_ON(x) do{GPIO_ResetBits(GPIOD, GPIO_Pin_1);}while(0)

#define MCHARGELED7_OFF(x) do{GPIO_SetBits(GPIOD, GPIO_Pin_2);}while(0)    // charging LED7
#define MCHARGELED7_ON(x) do{GPIO_ResetBits(GPIOD, GPIO_Pin_2);}while(0)

#define MCHARGELED8_OFF(x) do{GPIO_SetBits(GPIOD, GPIO_Pin_3);}while(0)    // charging LED8
#define MCHARGELED8_ON(x) do{GPIO_ResetBits(GPIOD, GPIO_Pin_3);}while(0)

// H - ON, L - OFF
#define MBIASLED_ON(x) do{GPIO_SetBits(GPIOD, GPIO_Pin_4);}while(0)   // bias light LED9,LED10,LED11,LED12
#define MBIASLED_OFF(x) do{GPIO_ResetBits(GPIOD, GPIO_Pin_4);}while(0)

/*********************************************************************************/
#if 0
#define Mprintf(q, buf, len)  do{
        u8Data_t u8Data;                    \
        for(u8 j = 0; j < len); j++) {     \
            u8Data.u8Val = buf[i];          \
            u8FIFOin_irq(&q, &u8Data);      \
        }                                   \
    }while(0)
#endif
/*******************************************************************************/

#endif
