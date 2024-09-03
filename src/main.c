/**
  ******************************************************************************
  * @file    main.c
  * @author  Alexander
  * @version V1.0.0
  * @date    30-Jan-2023
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 HKMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include "CONST.h"
#include "ptype.h"
#include "macro.h"
#include "global.h"
#include "l_arch.h"
#include "l_u8FIFO.h"
#include "l_actionFIFO.h"
#include "l_timer.h"
#include "l_uart.h"
#include "l_gpio.h"
#include "l_rs485.h"
#include "f_idle.h"
#include "l_sysProcess.h"


/** @addtogroup HK32F0301MxxC_StdPeriph_Examples
  * @{
  */

/** @addtogroup UART_2xUARTOnBoard
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
//UartRxBufDef Uart1Rx, Uart2Rx;
//UART_TypeDef* UartInstance[2] = {UART1, UART2};
//uint8_t UartIndex;

/* Private functions ---------------------------------------------------------*/
//static void RCC_Configuration(void);
//static void GPIO_Configuration(void);
//static void NVIC_Configuration(void);
//static void Uart1SendDatas(uint8_t *p, uint8_t len);
//static void Uart2SendDatas(uint8_t *p, uint8_t len);
/* global variables ----------------------------------------------------------*/
#if 1
 fstack_t g_fstack;
 msgq_t g_msgq;
 msg_t msg;
 func_t func;
 u16 g_tick;			/** 定时器计数 **/
 u16 g_flag;
 Timer_t g_timer[TIMER_NUM];		/** g_timer[0] for global, g_timer[1] for uart2 receive, g_timer[2] for g_promptQueue g_timer[3] for led display **/
 Timer_t g_ustimer[TIMER_NUM_40US];		/** for 485 transmit only **/
//u8FIFO_t g_uart3TxQue;
//u8FIFO_t g_uart3RxQue;
u8FIFO_t g_uart2TxQue;
u8FIFO_t g_uart2RxQue;
u8FIFO_t g_uart1TxQue;
u8FIFO_t g_uart1RxQue;

rs485transX_t rs485transX;

actionQueue_t g_promptQueue;
u8 g_IT_uart1_tmr = 0; // used uart1 received timeover

LedDisp_t g_led_display;    // for led charging display
/******************************************************************************/
ComponentField_t g_componentStatus = {
    .bat_v                = 0,
    .charge               = CINDEX_UNCHARGED,
    .ledStatus            = CCOLOR_NONE,
};
/******************************************************************************/

#endif 
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    fstack_init(&g_fstack);
    func.func = f_init;
    fstack_push(&g_fstack, &func);
     
    msgq_init(&g_msgq);
    msg.msgType = CSYS_INIT;
    msgq_in_irq(&g_msgq, &msg);

    /* Infinite Loop */
    while(1)
    {
        //deamon_uart1_send();
        //deamon_uart2_send();
        actionDoing(&g_promptQueue);
        rs485TransXDoing();
        
        if(msgq_out_irq(&g_msgq, &msg) == FALSE) {
            continue;
        }
        if(sysProcess(&msg) == TRUE) {
            continue;
        }

        if(fstack_top(&g_fstack, &func) == FALSE) {
            /** something wrong happend, Power Down or recover it **/
            fstack_init(&g_fstack);
            func.func = f_idle;
            fstack_push(&g_fstack, &func);

            g_tick = 0;
            SetTimer_irq(&g_timer[0], TIMER_1SEC, CMSG_TMR);
            continue;
        }
        func.func((unsigned *)&msg);
    }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */
