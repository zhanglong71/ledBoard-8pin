#include "hk32f0301mxxc_it.h"
#include "CONST.h"
#include "ptype.h"
#include "macro.h"
#include "global.h"
#include "l_arch.h"
#include "l_gpio.h"

void GPIO_initVOPPort(void)
{
}

void GPIO_init485(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  /* GPIOD Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  /* Configure PB04() in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  M485TR_R("不发送时，485处于接收状态");
}


void GPIO_VOPPWR_on(void)
{
    //GPIO_SetBits(GPIOD, GPIO_Pin_3);
}

void GPIO_VOPPWR_off(void)
{
    //GPIO_ResetBits(GPIOD, GPIO_Pin_3);
}

/** initial all led **/
void GPIO_init4led(void)
{
  GPIO_InitTypeDef        GPIO_InitStructure;
  /* GPIOD Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC | RCC_AHBPeriph_GPIOD, ENABLE);

  /* Configure (led1) in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;    // GPIO_PuPd_DOOWN
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
/** initial display **/
  MFAULTLED2_OFF("turn off fault led");
  MSTANDARDLED3_OFF("turn off standard led");
  MHIGHPOWERLED4_OFF("turn off highpower led");
  MCLEANLED5_OFF("turn off clean led");
  /** battery level **/
  MCHARGELED6_OFF("turn off charge led");
  MCHARGELED7_OFF("turn off charge led");
  MCHARGELED8_OFF("turn off charge led");
  /** bias light**/
  MBIASLED_ON("turn on bias led");
}

/*************************************************************************/
void led2fault_off(void)
{
    MFAULTLED2_OFF("turn off fault led");
}
void led2fault_on(void)
{
    MFAULTLED2_ON("turn on fault led");
}

void led3standard_off(void)
{
    MSTANDARDLED3_OFF("turn off standard led");
}
void led3standard_on(void)
{
    MSTANDARDLED3_ON("turn on standard led");
}

void led4highpower_off(void)
{
    MHIGHPOWERLED4_OFF("turn off highpower led");
}
void led4highpower_on(void)
{
    MHIGHPOWERLED4_ON("turn on highpower led");
}

void led5clean_off(void)
{
    MCLEANLED5_OFF("turn off clean led");
}
void led5clean_on(void)
{
    MCLEANLED5_ON("turn on clean led");
}

/*************************************************************************/
void standardMode(void)
{
    MFAULTLED2_OFF("turn off fault led");
    MSTANDARDLED3_ON("turn on standard led");
    MHIGHPOWERLED4_OFF("turn off highpower led");
    MCLEANLED5_OFF("turn off clean led");
}
void highpowerMode(void)
{
    MFAULTLED2_OFF("turn off fault led");
    MSTANDARDLED3_OFF("turn off standard led");
    MHIGHPOWERLED4_ON("turn on highpower led");
    MCLEANLED5_OFF("turn off clean led");
}

void faultMode(void)
{
    MFAULTLED2_ON("turn on fault led");
    MSTANDARDLED3_OFF("turn off standard led");
    MHIGHPOWERLED4_OFF("turn off highpower led");
    MCLEANLED5_OFF("turn off clean led");
}

void cleanMode(void)
{
    MFAULTLED2_OFF("turn off fault led");
    MSTANDARDLED3_OFF("turn off standard led");
    MHIGHPOWERLED4_OFF("turn off highpower led");
    MCLEANLED5_ON("turn on clean led");
}

void ledActoff(void)
{
    MFAULTLED2_OFF("turn off fault led");
    MSTANDARDLED3_OFF("turn off standard led");
    MHIGHPOWERLED4_OFF("turn off highpower led");
    MCLEANLED5_OFF("turn off clean led");
}

void ledAlloff(void)
{
    MFAULTLED2_OFF("turn off fault led");
    MSTANDARDLED3_OFF("turn off standard led");
    MHIGHPOWERLED4_OFF("turn off highpower led");
    MCLEANLED5_OFF("turn off clean led");

    MCHARGELED6_OFF("turn off charge led");
    MCHARGELED7_OFF("turn off charge led");
    MCHARGELED8_OFF("turn off charge led");

    MBIASLED_OFF("turn off bias led");
}
/*************************************************************************/
#if 0
void led6charge_off(void)
{
    MCHARGELED6_OFF("turn off charge led");
}
void led6charge_on(void)
{
    MCHARGELED6_ON("turn on charge led");
}

void led7charge_off(void)
{
    MCHARGELED7_OFF("turn off charge led");
}
void led7charge_on(void)
{
    MCHARGELED7_ON("turn on charge led");
}

void led8fcharge_off(void)
{
    MCHARGELED8_OFF("turn off charge led");
}
void led8charge_on(void)
{
    MCHARGELED8_ON("turn on charge led");
}
#endif
void charging_3_0(void)
{
    MCHARGELED6_OFF("turn off charge led");
    MCHARGELED7_OFF("turn off charge led");
    MCHARGELED8_OFF("turn off charge led");
}
void charging_3_1(void)
{
    MCHARGELED6_ON("turn on charge led");
    MCHARGELED7_OFF("turn off charge led");
    MCHARGELED8_OFF("turn off charge led");
}
void charging_3_2(void)
{
    MCHARGELED6_ON("turn on charge led");
    MCHARGELED7_ON("turn on charge led");
    MCHARGELED8_OFF("turn off charge led");
}
void charging_3_3(void)
{
    MCHARGELED6_ON("turn on charge led");
    MCHARGELED7_ON("turn on charge led");
    MCHARGELED8_ON("turn on charge led");
}

/*************************************************************************/
void led9_12_bias_off(void)
{
    MBIASLED_OFF("turn off bias led");
}
void led9_12_bias_on(void)
{
    MBIASLED_ON("turn on bias led");
}

paction_t_0 baisBlinkArr[] = {
    led9_12_bias_off,
    led9_12_bias_on,
};

void led9_12_bias_blink(void)
{
    int static step = 0;
    step++;
    step &= 0x1;
    baisBlinkArr[step]();
}

/*************************************************************************/
paction_t_0 chargingArr_step1[] = {
    charging_3_0,
    charging_3_3,
};
void doNothing(void)
{
}

void charging_blink(void)
{
    int static step = 0;
    step++;
    step &= 0x1;
    chargingArr_step1[step]();
}

paction_t_0 chargingArr_step2[] = {
    charging_3_0,
    charging_3_1,
    charging_3_2,
    charging_3_3,
};

void charging_animation(void)
{
    int static step = 0;
    chargingArr_step2[step]();
    step++;
    step &= 0x3;
}

void dispBatteryLevel(void)
{
     u8 _level = g_led_display.level;

     if (_level > 3) {
        _level = 3;
     }
     chargingArr_step2[_level]();
}

/*************************************************************************/
void ledChargeinit(void)
{
    g_led_display.status = CLED_BATLEVEL_NONE;
    g_led_display.level = 0;
    g_led_display.tick = 0;

    g_led_display.ptimer = &(g_timer[3]);
    g_led_display.stepMsgType = CLED_STEP;
    g_led_display.overMsgType = CLED_OVER;

    ClrTimer_irq(g_led_display.ptimer);
}

Pair_u8u8ptr_t ledAnimationArr[] = {
    {CLED_BATLEVEL_NONE,      doNothing},           // nothing
    {CLED_BATLEVEL_INIT,      charging_blink},      // init
    {CLED_BATLEVEL_OFF,       charging_3_0},        // led off
    {CLED_BATLEVEL_LEVEL,     dispBatteryLevel},    // battery level
    {CLED_BATLEVEL_BLINK,     charging_blink},      // battery low
    {CLED_BATLEVEL_ANIMATION, charging_animation},  // charging
};

void ledChargeProcess(void)
{
    ClrTimer_irq(g_led_display.ptimer);

    for(int i = 0; i < MTABSIZE(ledAnimationArr); i++) {
        if (ledAnimationArr[i].actionIdx == g_led_display.status) {
            ledAnimationArr[i].paction();
            break;
        }
    }

    SetTimer_irq(g_led_display.ptimer, g_led_display.tick, g_led_display.stepMsgType);
}

void ledChargeStatus_set(u8 _status)
{
    if (g_led_display.status == _status) {
        return;
    }
    
    ClrTimer_irq(g_led_display.ptimer);
    g_led_display.status = _status;
    if (_status == CLED_BATLEVEL_LEVEL) {
        // g_led_display.tick = TIMER_10SEC;
        g_led_display.tick = TIMER_400MS;   // ?????????
    } else {
        g_led_display.tick = TIMER_400MS;
    }
    
    // charging_3_3();
    SetTimer_irq(g_led_display.ptimer, TIMER_20MS, g_led_display.stepMsgType);
}

#if 0
void ledChargeStop(void)
{
    ledChargeStatus_set(CLED_BATLEVEL_LEVEL);
}
#endif

