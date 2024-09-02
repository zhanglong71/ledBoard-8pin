#include "hk32f0301mxxc_it.h"
#include "CONST.h"
#include "ptype.h"
#include "macro.h"
#include "global.h"
#include "l_arch.h"
#include "l_gpio.h"

void GPIO_initVOPPort(void)
{
#if 0
  GPIO_InitTypeDef GPIO_InitStructure;
  /* GPIOD Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);

  /* Configure PD02() in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
    
  /* Configure PD03(5V_EN) in output pushpull mode */
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  GPIO_SetBits(GPIOD, GPIO_Pin_2);
  GPIO_ResetBits(GPIOD, GPIO_Pin_3);
#endif
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

void charging_animation_blink(void)
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

void charging_animation_step2(void)
{
    int static step = 0;
    step++;
    step &= 0x3;
    chargingArr_step2[step]();
}

void dispBatteryLevel(u8 _level)
{
     if (_level > 3) {
        _level = 3;
     }
     chargingArr_step2[_level]();
}

/*************************************************************************/

/*************************************************************************/
#if 0
static void GPIO_bit0(void)
{
    GPIOC->BSRR = GPIO_Pin_5; /** GPIO_SetBits(GPIOC, GPIO_Pin_5); **/
    NOP();
    NOP();
    
    GPIOC->BRR = GPIO_Pin_5;  /** GPIO_ResetBits(GPIOC, GPIO_Pin_5); **/
}

static void GPIO_bit1(void)
{
    GPIOC->BSRR = GPIO_Pin_5;  /** GPIO_SetBits(GPIOC, GPIO_Pin_5); **/
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    
    GPIOC->BRR = GPIO_Pin_5;   /** GPIO_ResetBits(GPIOC, GPIO_Pin_5); **/
    
}

const paction_t_0 colorArr[] = {
        GPIO_bit1,
        GPIO_bit0,
    };

void LED_display(u32 __color)
{
   IRQ_disable();

   colorArr[!(__color & (1 << 23))]();
   colorArr[!(__color & (1 << 22))]();
   colorArr[!(__color & (1 << 21))]();
   colorArr[!(__color & (1 << 20))]();
   colorArr[!(__color & (1 << 19))]();
   colorArr[!(__color & (1 << 18))]();
   colorArr[!(__color & (1 << 17))]();
   colorArr[!(__color & (1 << 16))]();
   colorArr[!(__color & (1 << 15))]();
   colorArr[!(__color & (1 << 14))]();
   colorArr[!(__color & (1 << 13))]();
   colorArr[!(__color & (1 << 12))]();
   colorArr[!(__color & (1 << 11))]();
   colorArr[!(__color & (1 << 10))]();
   colorArr[!(__color & (1 << 9))]();
   colorArr[!(__color & (1 << 8))]();
   colorArr[!(__color & (1 << 7))]();
   colorArr[!(__color & (1 << 6))]();
   colorArr[!(__color & (1 << 5))]();
   colorArr[!(__color & (1 << 4))]();
   colorArr[!(__color & (1 << 3))]();
   colorArr[!(__color & (1 << 2))]();
   colorArr[!(__color & (1 << 1))]();
   colorArr[!(__color & (1))]();
   
   IRQ_enable();
}
#endif

#if 0
/*************************************************************************
 * color value
 *************************************************************************/
u8 const led_depth_tab[] = {
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    10,
    12,
    15,
    19,
    24,
    30,
    37,
    45,
    54,
    64,
    75,
    87,
    100,
    114,
    129,
    145,
    162,
    180,
    199,
    219,
    240,
    250,

    240,
    219,
    199,
    180,
    162,
    145,
    129,
    114,
    100,
    87,
    75,
    64,
    54,
    45,
    37,
    30,
    24,
    19,
    15,
    //12,
    10,
    //9,
    //8,
    7,
    //6,
    //5,
    4,
    //3,
    //2,
    //1,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};
u8 getColorDepth(void)
{
    u8 static color_depth_index = 0;
    color_depth_index++;
    if (color_depth_index >= MTABSIZE(led_depth_tab)) {
        color_depth_index = 0;
    }
    return led_depth_tab[color_depth_index];
}
#endif

#if 0
u8 getBlinkOnOff(void)
{
    u8 const led_onOff_tab[] = {
        250,
        0,
    };
    u8 static color_onOff_index = 0;
    color_onOff_index++;
    if (color_onOff_index >= MTABSIZE(led_onOff_tab)) {
        color_onOff_index = 0;
    }
    return led_onOff_tab[color_onOff_index];
}
#endif

/*************************************************************************/
void ledChargeinit(void)
{
#if 1
    g_led_display.level = 0;
    g_led_display.tick = 0;

    g_led_display.ptimer = &(g_timer[3]);
    g_led_display.stepMsgType = CLED_STEP;
    g_led_display.overMsgType = CLED_OVER;

    ClrTimer_irq(g_led_display.ptimer);
#endif
}

void ledChargeProcess(void)
{
    ClrTimer_irq(g_led_display.ptimer);
    charging_animation_step2();

    SetTimer_irq(g_led_display.ptimer, g_led_display.tick, g_led_display.stepMsgType);
}

void ledChargeStart(u16 _tick)
{
    ClrTimer_irq(g_led_display.ptimer);
    if (_tick < TIMER_200MS) {
        g_led_display.tick = TIMER_200MS;
    } else {
        g_led_display.tick = _tick;   // set period
    }
    charging_3_3();
    SetTimer_irq(g_led_display.ptimer, g_led_display.tick, g_led_display.stepMsgType);
}

void ledChargeStop(void)
{
    // g_led_display.color = 0;   // mask
    g_led_display.tick = 0;
    ClrTimer_irq(g_led_display.ptimer);
}

