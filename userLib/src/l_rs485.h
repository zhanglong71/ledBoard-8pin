#ifndef __L_RSA85_H__
#define __L_RSA85_H__

void rs485Init(void);
RetStatus rs485_stor_irq(u8Data_t *u8Data);

void rs485actProcess(void);
void rs485TransXDoing(void);
void rs485actOver(void);

smStatus_t rs485NextStep(smStatus_t cur_status);
void generateAskstatus(void);

#endif
