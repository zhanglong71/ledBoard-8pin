#ifndef __L_JSONTL_H__
#define __L_JSONTL_H__

char JsonParseL0(char* jsonstrbuf, kv_t* jsonstcarr);
RetStatus reportVersion(void);
/***********************************************/
void generateLedDispAckOk(char* to);
void generateLedDispAckErr(char* to);
void ledRGB2msg(Quadruple_u8u8u8u8_t *color);

u8 batteryVoltage2percent(void);

/***********************************************/

#endif
