#ifndef __L_GPIO_H_
#define __L_GPIO_H_

void GPIO_initVOPPort(void);
void GPIO_init485(void);

void GPIO_VOPPWR_off(void);
void GPIO_VOPPWR_on(void);


void GPIO_init4led(void);
void charging_blink(void);
void charging_animation(void);
void dispBatteryLevel(void);
void led9_12_bias_blink(void);

void standardMode(void);
void highpowerMode(void);
void faultMode(void);
void cleanMode(void);
void led9_12_bias_on(void);
void led9_12_bias_off(void);
void ledActoff(void);
void ledAlloff(void);

// void LED_display(u32 __color);

void ledChargeinit(void);
void ledChargeProcess(void);
void ledChargeStatus_set(u8 _status);
// void ledChargeStop(void);

#endif
