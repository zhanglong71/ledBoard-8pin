
#include "CONST.h"
#include "ptype.h"
#include "macro.h"
#include "global.h"
#include "version.h"

#include "l_arch.h"
#include <string.h>
#include <stdio.h>

#include "l_u8FIFO.h"
#include "l_jsonTL.h"
#include "l_timer.h"
#include "l_gpio.h"
#include "l_jsonTL.h"
#include "l_rs485.h"
// #include "main.h"
/**********************************************************************************************/
RetStatus reportVersion(void)
{
    u8 i = 0;
    u8Data_t u8Data;
    char buf[32];
    RetStatus retStatus = POK;
    
    sprintf(buf, "%s.%s.%s.%s", CBOARD, CWARE, CDATETIME, CVERSION);

    for (i = 0; ((i < strlen(buf)) && (i < MTABSIZE(buf))); i++) {
        u8Data.u8Val = buf[i];
        retStatus = rs485_stor_irq(&u8Data);
        if (retStatus != POK) {
            return retStatus;
        }
    }
    return retStatus;
}

/*******************************************************************************
 * prase json body(JsonParseL0)
 * 
 * example:
 * {key1:value1, key2:value2, ... ,keyn:valuen}
 *******************************************************************************/
char JsonParseL0(char* jsonstrbuf, kv_t* jsonstcarr)
{
    u8 j_u8,k_u8,i_u8 = 0;
    char *p[CMAX1_COUPLE * 2];
    char *pChar = (char *)jsonstrbuf;
    jsonstcarr[0].KVIndex = 0;

    /** 1. simily as '{ ... }'! **/
    if((jsonstrbuf[0] != '{') || (jsonstrbuf[strlen(jsonstrbuf) - 1] != '}')) {
        return(0);
    }

    jsonstrbuf[strlen(jsonstrbuf) - 1] = '\0';            /** overwrite the start '}' ! **/
    for(j_u8 = 0; j_u8 < strlen(jsonstrbuf); j_u8++) {    /** overwrite the end '{' ! **/
        jsonstrbuf[j_u8] = jsonstrbuf[j_u8 + 1];
    }
    
    while((p[i_u8]  = strtok(pChar, ":,")) != NULL) {    /** split the string ... **/
        i_u8++;
        pChar = NULL;
    }
 
    for(j_u8 = 0; ((j_u8 < i_u8/2) && (j_u8 < CMAX1_COUPLE)); j_u8++) {
        jsonstcarr[j_u8].KVIndex = i_u8/2 - j_u8;
        strcpy(jsonstcarr[j_u8].key, p[j_u8 * 2]);
        strcpy(jsonstcarr[j_u8].value, p[j_u8 * 2 + 1]);

        jsonstcarr[j_u8].key[strlen(jsonstcarr[j_u8].key) - 1] = '\0';           /** overwrite the start '"' ? **/
        for(k_u8 = 0; k_u8 < strlen(jsonstcarr[j_u8].key); k_u8++)                 /** overwrite the end '"' ? **/
        {
            jsonstcarr[j_u8].key[k_u8] = jsonstcarr[j_u8].key[k_u8 + 1];
        }
    }
 
    return (1);
}

/*********************************************
 * {"voi":xxxx,"PLY":OK}
 * {"voi":xxxx,"PLY":err}
 *********************************************/
void generateLedDispAckOk(char* to)
{
    u8 i = 0;
    u8Data_t u8Data;
    char buf[32];
    
    sprintf(buf, "{\"led\":%s,\"DIS\":OK}", to);

    for (i = 0; ((i < strlen(buf)) && (i < MTABSIZE(buf))); i++) {
        u8Data.u8Val = buf[i];
        rs485_stor_irq(&u8Data);
    }
}
void generateLedDispAckErr(char* to)
{
    u8 i = 0;
    u8Data_t u8Data;
    char buf[32];
    
    sprintf(buf, "{\"led\":%s,\"DIS\":err}", to);

    for (i = 0; ((i < strlen(buf)) && (i < MTABSIZE(buf))); i++) {
        u8Data.u8Val = buf[i];
        rs485_stor_irq(&u8Data);
    }
}

/**********************************************************************************************/
void rgb2ActLedAllOff(void)
{
    msg_t msg;
    msg.msgType = CMSG_LEDALLOFF;
    msgq_in_irq(&g_msgq, &msg);
}

void rgb2ActLedFault(void)
{
    msg_t msg;
    msg.msgType = CMSG_LEDFAULT;
    msgq_in_irq(&g_msgq, &msg);
}

void rgb2ActLedStandard(void)
{
    msg_t msg;
    msg.msgType = CMSG_LEDSTANDARD;
    msgq_in_irq(&g_msgq, &msg);
}

void rgb2ActLedHighPower(void)
{
    msg_t msg;
    msg.msgType = CMSG_LEDHIGHPOWER;
    msgq_in_irq(&g_msgq, &msg);
}

void rgb2ActLedCharging(void)
{
    msg_t msg;
    msg.msgType = CMSG_LEDCHARGEING;
    msgq_in_irq(&g_msgq, &msg);
    
    g_componentStatus.charge = CINDEX_CHARGING;
}

void rgb2ActLedClean(void)
{
    msg_t msg;
    msg.msgType = CMSG_LEDCLEAN;
    msgq_in_irq(&g_msgq, &msg);
}

void rgb2ActLedChargeStop(void)
{
    msg_t msg;
    msg.msgType = CMSG_LEDCHARGESTOP;
    msgq_in_irq(&g_msgq, &msg);

    g_componentStatus.charge = CINDEX_UNCHARGED;
}

void rgb2ActLedBattery0Level(void)
{
    msg_t msg;
    msg.msgType = CMSG_LEDCHARGESTOP;
    msgq_in_irq(&g_msgq, &msg);

    g_componentStatus.charge = CINDEX_UNCHARGED;
}
void rgb2ActLedBattery1Level(void)
{
    msg_t msg;
    msg.msgType = CMSG_LEDCHARGESTOP;
    msgq_in_irq(&g_msgq, &msg);

    g_componentStatus.charge = CINDEX_UNCHARGED;
}

void rgb2ActLedBattery2Level(void)
{
    msg_t msg;
    msg.msgType = CMSG_LEDCHARGESTOP;
    msgq_in_irq(&g_msgq, &msg);

    g_componentStatus.charge = CINDEX_UNCHARGED;
}

void rgb2ActLedBattery3Level(void)
{
    msg_t msg;
    msg.msgType = CMSG_LEDCHARGESTOP;
    msgq_in_irq(&g_msgq, &msg);

    g_componentStatus.charge = CINDEX_UNCHARGED;
    // g_led_display.level = color->green;
}

#if 0
Quintuple_u8u8u8u8u8ptr_t rgbtim2ActArr[] = {
 /** red,  green, blue, time **/
    {0,   200,   0,    0,  rgb2ActLedStandard},       // standard, charge complete
    {0,   100,   0,    0,  rgb2ActLedHighPower},      // high power
    {0,   250,   0,    5,  rgb2ActLedCharging},       // charging
    {0,   200,   0,    5,  rgb2ActLedCharging},       // charging
    {200, 0,     200,  5,  rgb2ActLedClean},          // clean
    {0,   101,   0,    1,  rgb2ActLedChargeStop},     // charge stop(display volate level)
    {0,   0,     0,    0,  rgb2ActAllLedOff},         // all Led off
    {200, 0,     0,    50, rgb2ActLedFault},          // fault
};
#endif

Color2action_t rgbtim2ActArr[] = {
 /** red,  green, blue, time **/
    {CCOLOR_STANDARD,      {0,   200,   0,    0},  rgb2ActLedStandard},       // standard, charge complete
    {CCOLOR_HIGHPOWER,     {0,   100,   0,    0},  rgb2ActLedHighPower},      // high power
    {CCOLOR_CHARGING,      {0,   250,   0,    5},  rgb2ActLedCharging},       // charging
    {CCOLOR_CHARGING2,     {0,   200,   0,    5},  rgb2ActLedCharging},       // charging
    {CCOLOR_CLEAN,         {200, 0,     200,  5},  rgb2ActLedClean},          // clean
    {CCOLOR_BATTERY0LEVEL, {0,   0,     0,    1},  rgb2ActLedBattery0Level},     // charge stop(display 0 level)
    {CCOLOR_BATTERY1LEVEL, {0,   1,     0,    1},  rgb2ActLedBattery1Level},     // charge stop(display 1 level)
    {CCOLOR_BATTERY2LEVEL, {0,   2,     0,    1},  rgb2ActLedBattery2Level},     // charge stop(display 2 level)
    {CCOLOR_BATTERY3LEVEL, {0,   3,     0,    1},  rgb2ActLedBattery3Level},  // charge stop(display 3 level)
    {CCOLOR_ALLOFF,        {0,   0,     0,    0},  rgb2ActLedAllOff},         // all Led off
    {CCOLOR_FAULT,         {200, 0,     0,    50}, rgb2ActLedFault},          // fault
};

RetStatus ledRGB2msg(Quadruple_u8u8u8u8_t *color, u8* colorIdx)
{
    int idx;
    for (idx = 0; idx < MTABSIZE(rgbtim2ActArr); idx++) {
        if ((rgbtim2ActArr[idx].color.red == color->red) &&
            (rgbtim2ActArr[idx].color.green == color->green) &&
            (rgbtim2ActArr[idx].color.blue == color->blue) &&
            (rgbtim2ActArr[idx].color.tim == color->tim)) {
            rgbtim2ActArr[idx].paction();
            *colorIdx = rgbtim2ActArr[idx].colorIdx;
            return POK;
        }
    }
    return PERROR;
}

u8 batteryVoltage2percent(void)
{
#define CVOLTAGE_MAX (1580)
#define CVOLTAGE_MIN (1300)
    
#define CVOLTAGE_0 (CVOLTAGE_MIN)
#define CVOLTAGE_1 (1350)
#define CVOLTAGE_2 (1500)
#define CVOLTAGE_3 (CVOLTAGE_MAX)

    u16 voltage = g_componentStatus.bat_v;
    
    if (voltage >= CVOLTAGE_3) {
        return 3;
    } else if (voltage >= CVOLTAGE_2) {
        return 2;
    } else if (voltage >= CVOLTAGE_1) {
        return 1;
    } else {
        return 0;
    }

#undef CVOLTAGE_MAX
#undef CVOLTAGE_MIN
#undef CVOLTAGE_0
#undef CVOLTAGE_1
#undef CVOLTAGE_2
#undef CVOLTAGE_3
}

