#include "CONST.h"
#include "ptype.h"
#include "macro.h"
#include "global.h"

#include "l_timer.h"
#include "l_arch.h"
#include "l_gpio.h"
#include "l_actionFIFO.h"

/*******************************************************************************
 * check is the queue empty
 *******************************************************************************/
static int isActionQueEmpty(actionQueue_t *q)
{
    if(q->tail == q->head) {
        return TRUE;
    }
    return    FALSE;
}

/*******************************************************************************
 * check is the queue full
 *******************************************************************************/
static int isActionQueFull(actionQueue_t *q)
{
    // if((q->tail + 1 == q->head) || (((q->tail + 1) % (ACTIONQUEUESIZE)) == q->head)) {
    if(((q->tail + 1) == q->head) || (((q->tail + 1) % (MTABSIZE(q->buf))) == q->head)) {
        return TRUE;
    }
    return    FALSE;
}

static void actionQueueClear(actionQueue_t *q)
{
    q->tail = 0;
    q->head = 0;
    q->flag = 0;
}

/*******************************************************************************
 * put the data into the (loop)queue
 *******************************************************************************/
void actionQueueInit(actionQueue_t *q, Timer_t *timer, msgType_t stepMsgType, msgType_t overMsgType)
{
    q->tail = 0;
    q->head = 0;
    // q->flag = 0;
    
    q->stepMsgType = stepMsgType;  
    q->overMsgType = overMsgType;
    q->timer = timer;
    ClrTimer_irq(q->timer);
}

/*******************************************************************************
 * put the data into the (loop)queue
 *******************************************************************************/
int actionQueueIn(actionQueue_t *q, action_t *action)
{
    if(isActionQueFull(q) == TRUE) {  
        return FALSE;
    }

    q->buf[q->tail].actionType = action->actionType;
    q->buf[q->tail].actionTime = action->actionTime;
    q->buf[q->tail].actionPara = action->actionPara;
    //q->buf[q->tail].func       = action->func;
    q->tail = (q->tail + 1) % (MTABSIZE(q->buf));
 
    return TRUE;
}

int actionQueueOut(actionQueue_t *q, action_t *action)
{
    if(isActionQueEmpty(q) == TRUE) {
        return FALSE;
    }
    
    action->actionType = q->buf[q->head].actionType;
    action->actionTime = q->buf[q->head].actionTime;
    action->actionPara = q->buf[q->head].actionPara;
    //action->func       = q->buf[q->head].func;
    
    q->head = (q->head + 1) % (MTABSIZE(q->buf));
       
    return TRUE;
}

/*********************************************************************************/
void vp_stor(unsigned char __vpIdx)
{
	action_t action;
    
    action.actionType = CVOP_PWRON;
    action.actionTime = TIMER_200MS;
    actionQueueIn(&g_promptQueue, &action);
    
    action.actionType = CACT_VOPON;
    action.actionTime = TIMER_3SEC;
    action.actionPara = __vpIdx;
    actionQueueIn(&g_promptQueue, &action);

    action.actionType = CVOP_PWROFF;
    action.actionTime = TIMER_100MS;
    actionQueueIn(&g_promptQueue, &action);
}

void vp_setDefaultVolume(void)
{
	action_t action;
    
    action.actionType = CVOP_PWRON;
    action.actionTime = TIMER_100MS;
    actionQueueIn(&g_promptQueue, &action);

    action.actionType = CACT_VOPON;
    action.actionTime = TIMER_100MS;
    action.actionPara = 0xe3;
    actionQueueIn(&g_promptQueue, &action);
}

/**
 * similer as timer delay
 **/
void actionDelay(int _delay)
{
	action_t action;
    action.actionType = CACT_DELAY;
    action.actionTime = _delay;
    actionQueueIn(&g_promptQueue, &action);
}

/*******************************************************************************
 * start action and set action flag
 *******************************************************************************/
static void startAction(actionQueue_t *q, action_t * pAction)
{
	switch(pAction->actionType) 
    {
    case CLED_BREATH:
		q->flag = (1<<4);
        break;
	case CACT_DELAY:
		q->flag = (1<<3);
		break;
	
	case CACT_VOPON:
		q->flag = (1<<2);
		vp_play((u8)pAction->actionPara);
		break;
    case CVOP_PWRON:
        q->flag = (1<<1);
        GPIO_VOPPWR_on();
        break;
    case CVOP_PWROFF:
        q->flag = (1<<0);
        GPIO_VOPPWR_off();
        break;
        
	default:
		/** don't goto here **/
		q->flag = 0;
		break;
	}
}

 /*******************************************************************************
 * stop the action; no flag modify
 *******************************************************************************/
static void stopAction(actionQueue_t *q)
{
  	/** stop the timeout action  **/
    if(q->flag & (1<<3)) {
          /** delay... do Nothing **/
    } else if(q->flag & (1<<2)) {
	    vp_play((u8)CVOP_STOP);
    } else if(q->flag & (1<<1)) {
        // GPIO_VOPPWR_off();   /** do nothing **/
        //Mreset_bit(q->flag, 1);
    } else if(q->flag & (1<<0)) {
        // GPIO_VOPPWR_off();   /** do nothing **/
        //Mreset_bit(q->flag, 0);
    } else if(q->flag & (1<<4)) {
        //Mreset_bit(q->flag, 4);
  	} else {
	}
}

/** 清空动作队列，并且停止当前动作 **/
void promptInit(void)
{
	actionQueueInit(&g_promptQueue, &(g_timer[2]), CPMT_TOUT, CPMT_OVER);
	stopAction(&g_promptQueue);
}

/**
 * the stop is used to end VOP play!
 **/
void vp_stop(void)
{
    /** stop last and  **/
    ClrTimer_irq(g_promptQueue.timer);
    stopAction(&g_promptQueue);
    actionQueueClear(&g_promptQueue);
    GPIO_VOPPWR_off();
}

/**
 * the stop ACTION is used to start another VOP
 * 
 **/
void vp_stop1(void)
{
    ClrTimer_irq(g_promptQueue.timer);
    actionQueueClear(&g_promptQueue);
}


/** 
 * event queue process
 * check the queue and start action when idle(idle ==> doing)
 **/
void actionDoing(actionQueue_t * q)
{
	action_t action;
	
	if(q->flag == 0) {
		if(actionQueueOut(q, &action) == TRUE) {
			startAction(q, &action);
	        SetTimer_irq(q->timer, action.actionTime, q->stepMsgType);
		}
	} else {

	}
}

/*************************************************
 * one section over, then start another section
 * otherwise action over
 *************************************************/
void actProcess(actionQueue_t * q)
{
    //msg_t msg;
	action_t action;
	
	/** stop the timeout action first  **/
	stopAction(q);
  	ClrTimer_irq(q->timer);
    
	/** start the next action **/
	if(actionQueueOut(q, &action) == TRUE) {
		startAction(q, &action);
	    SetTimer_irq(q->timer, action.actionTime, q->stepMsgType);
	} else {
		if(q->flag != 0) {
			q->flag = 0;
			SetTimer_irq(q->timer, TIMER_10MS, q->overMsgType);
            
            //msg.msgType = q->overMsgType;
            //msgq_in_irq(&g_msgq, &msg);
		}
	}
}

