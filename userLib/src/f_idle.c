#include "hk32f0301mxxc_it.h"
#include "CONST.h"
#include "ptype.h"
#include "macro.h"
#include "global.h"
#include "l_arch.h"
#include "l_gpio.h"
#include "l_u8FIFO.h"
#include "l_actionFIFO.h"
#include "l_sysProcess.h"
#include "l_jsonTL.h"
#include "l_uart.h"
#include "l_timer.h"
#include "l_rs485.h"
#include "f_idle.h"

int f_idle(void *pMsg)
{
#define CREPORT_PERIOD (30)

    switch(((msg_t *)pMsg)->msgType) 
    {
    case CMSG_TMR:
        g_tick++;

        g_led_display.level = batteryVoltage2percent();  /** note: g_led_display.level update by master STOP CHARGING CMD either **/
        if (g_componentStatus.ledStatus != CCOLOR_ALLOFF) { // adjust battery level display only
            if (g_led_display.level < 1) {
                if (g_componentStatus.charge == CINDEX_UNCHARGED) {
                    generateAskstatus();
                    ledChargeStatus_set(CLED_BATLEVEL_BLINK);
                }
            } else {
                if (g_componentStatus.charge != CINDEX_CHARGING) {
                    u8 tmp = g_tick % CREPORT_PERIOD;
                    if (tmp == 3) {
                        generateAskstatus();
                    } else if (tmp == 4) {
                        //dispBatteryLevel();
                        ledChargeStatus_set(CLED_BATLEVEL_LEVEL);
                    }
                }
            }
        }
        break;
        
    case CMSG_INIT:
        g_tick = 0;
        SetTimer_irq(&g_timer[0], TIMER_1SEC, CMSG_TMR);
        ledChargeStatus_set(CLED_BATLEVEL_INIT);
	    break;
          
    case CPMT_OVER:
        GPIO_VOPPWR_off();
        break;
        
    default:
        break;
	}  

    return  0;
}

int f_init(void *pMsg)
{
    func_t func;
    msg_t msg;
    RetStatus retStatus;
    switch(((msg_t *)pMsg)->msgType) 
    {   
    case CSYS_INIT:        // step1
        /* Configure clock GPIO, UARTs */
        RCC_Configuration4uart();
    
        /* Configure GPIO Pin Tx/Rx for Uart communication */
        GPIO_Configuration4uart();
    
        /* Configure NVIC */
        NVIC_Configuration4uart();
    
        UART1_Configuration();
        UART2_Configuration();
        // SysTick_Config(SystemCoreClock / 1000);        // 1ms
        SysTick_Config(SystemCoreClock / 100);       // 10ms
        TIM_Config();
        GPIO_init4led();
        // GPIO_initVOPPort();
        GPIO_init485();
        /*********************************/
        vp_init();
        promptInit();
        rs485Init();
        ledChargeinit();
        
        for(int i = 0; i < MTABSIZE(g_ustimer); i++) {
            ClrTimer(&g_ustimer[i]);
        }
        for(int i = 0; i < MTABSIZE(g_timer); i++) {
            ClrTimer(&g_timer[i]);
        }
    
        u8FIFOinit(&g_uart1TxQue);
        u8FIFOinit(&g_uart1RxQue);
        u8FIFOinit(&g_uart2TxQue);
        u8FIFOinit(&g_uart2RxQue);
 
        // LED_display(CINIT_COLOR);
        SetTimer_irq(&g_timer[0], TIMER_100MS, CSYS_INITS1);
        break;
 
    case CSYS_INITS1:      // step2
        vp_setDefaultVolume();
        SetTimer_irq(&g_timer[0], TIMER_100MS, CSYS_INITS2);
        break;
    case CSYS_INITS2:      // step3
        retStatus = reportVersion();
        if (retStatus != POK) {  // busy! try again later; giveup the 
            SetTimer_irq(&g_timer[0], TIMER_100MS, CSYS_INITS2);
        } else {    
            SetTimer_irq(&g_timer[0], TIMER_1SEC, CMSG_TMR);
        }
        break;

    case CPMT_OVER:       // over
        GPIO_VOPPWR_off();
        fstack_init(&g_fstack);
        func.func = f_idle;
        fstack_push(&g_fstack, &func);

        //msgq_init(&g_msgq);
        msg.msgType = CMSG_INIT;
        msgq_in_irq(&g_msgq, &msg);
        g_tick = 0;
        SetTimer_irq(&g_timer[0], TIMER_1SEC, CMSG_TMR);
        break;
        
    default:
        break;
    }  

    return  0;
}


