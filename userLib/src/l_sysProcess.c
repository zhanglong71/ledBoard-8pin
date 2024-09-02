#include "CONST.h"
#include "ptype.h"
#include "macro.h"
#include "global.h"
#include "l_arch.h"
#include <string.h>
#include <stdlib.h>
#include "l_u8FIFO.h"
#include "l_jsonTL.h"
#include "l_timer.h"
#include "l_gpio.h"
#include "l_actionFIFO.h"
#include "l_rs485.h"
#include "l_sysProcess.h"
#include "hk32f0301mxxc.h"

char buf[U8FIFOSIZE];
kv_t KVarr[6];
int sysProcess(void *pMsg)
{
    int iRet = TRUE;
    u8Data_t u8Data;
    u8 i = 0;
    switch(((msg_t *)pMsg)->msgType)
    {
    case CUART1_TOUT:
        /************************************
         * receive:  {"xxx":led,"R":0,"G":250,"B":0}  --- 只显示颜色
         *   或      {"xxx":led,"R":0,"G":250,"B":0,"TIM":12}  --- 支持颜色渐变】
         *          
         * ack:
         *
         *    {"led":xxx,"DIS":OK}
         *    {"led":xxx,"DIS":err}
         ************************************/
        memset(buf, 0, sizeof(buf));
        memset(KVarr, 0, sizeof(KVarr));
        
        for(i = 0; ((i < MTABSIZE(buf)) && (u8FIFOout_irq(&g_uart1RxQue, &u8Data) == TRUE)); i++) {
            buf[i] = u8Data.u8Val;
        }
        u8FIFOinit_irq(&g_uart1RxQue);  /** !!!!!!!!!!!! **/
        buf[i] = '\0';

        if (JsonParseL0(buf, KVarr)) {
            u8 red = 0;
            u8 green = 0;
            u8 blue = 0;
            u8 color_flag = 0;
            u8 src_idx = 0xff;
            u16 tim = 0;
            for (u8 i = 0; ((i < MTABSIZE(KVarr)) && (KVarr[i].KVIndex > 0)); i++) {
                 if (strstr(KVarr[i].value, "led")) {
                     Mset_bit(color_flag, 1);
                     src_idx = i;
                 }
                 if (strstr(KVarr[i].key, "R") && strstr("R", KVarr[i].key)) {
                     Mset_bit(color_flag, 2);
                     red = atoi(KVarr[i].value);
                 }
                 if (strstr(KVarr[i].key, "G") && strstr("G", KVarr[i].key)) {
                     Mset_bit(color_flag, 3);
                     green = atoi(KVarr[i].value);
                 }
                 if (strstr(KVarr[i].key, "B") && strstr("B", KVarr[i].key)) {
                     Mset_bit(color_flag, 4);
                     blue = atoi(KVarr[i].value);
                 }
                 if (strstr(KVarr[i].key, "TIM")) {
                     Mset_bit(color_flag, 5);
                     tim = atoi(KVarr[i].value);
                 }

                 if ((strstr(KVarr[i].key, "bv") && strstr("bv", KVarr[i].key)) ||
                     (strstr(KVarr[i].key, "bat_v") && strstr("bat_v", KVarr[i].key))) {  // !!!!!! The data takes effect immediately !!!!!!
                     Mset_bit(color_flag, 6);
                     g_componentStatus.bat_v = atoi(KVarr[i].value);
                 }
            }
            if (Mget_bit(color_flag, 1) && Mget_bit(color_flag, 2) && Mget_bit(color_flag, 3) && Mget_bit(color_flag, 4)) {
                if ((red <= 250) && (green <= 250) && (blue <= 250)) {
                    #if 1
                    Quadruple_u8u8u8u8_t light;
                    light.red = red;
                    light.green = green;
                    light.blue = blue;
                    light.tim = tim;
                    ledRGB2msg(&light);
                    
                    #endif
                    generateLedDispAckOk(KVarr[src_idx].key);
                } else {
                    generateLedDispAckErr(KVarr[src_idx].key);
                }
            } else {
                /*** nothing ***/
            }
        };
        break;

    case CPMT_TOUT:        /** 一段提示动作完成 **/
        actProcess(&g_promptQueue);
        break;
        
    case C485_TOUT:
        rs485actProcess();
        break;

    case C485_OVER:    
        rs485actOver();
        break;

    case CLED_STEP:
        ledChargeProcess();
        break;

    case CMSG_LEDALLOFF:     /** all led off **/
        ledAlloff();
        break;
    case CMSG_LEDACTOFF:
        ledAlloff();
        break;
    case CMSG_LEDFAULT:      /** fault director**/
        faultMode();
        break;
    case CMSG_LEDSTANDARD:   /** standard mode director**/
        standardMode();
        break;
    case CMSG_LEDHIGHPOWER:  /** highpower mode director**/
        highpowerMode();
        break;
    case CMSG_LEDCLEAN:      /** clean mode director**/
        cleanMode();
        break;
    case CMSG_LEDCHARGEING:     /** clean mode director**/
        ledActoff();
        ledChargeStart(TIMER_600MS);
        break;
    case CMSG_LEDCHARGESTOP:
        ledChargeStop();
        break;

    default:
        iRet = FALSE;
        break;	
    }
    return  iRet;   
}
/**********************************************************************************************************/

