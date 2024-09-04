#ifndef __L_ARCH_H__
#define __L_ARCH_H__

void IRQ_disable(void);
void IRQ_enable(void);

void fstack_init(fstack_t *s);
int fstack_pop(fstack_t *s, func_t *f);
int	fstack_push(fstack_t *s, func_t *func);
int	fstack_top(const fstack_t *s, func_t *f);

int msg_init(msg_t *pMsg);
void msgq_init(msgq_t *q);
int	msgq_in(msgq_t *q, msg_t *val);
int	msgq_in_irq(msgq_t *q, msg_t *val);
int	msgq_out(msgq_t *q, msg_t *val);
int	msgq_out_irq(msgq_t *q, msg_t *val);

void SetTimer(Timer_t * timer, int tick, msgType_t msgType); 
void SetTimer_irq(Timer_t * timer, int tick, msgType_t msgType);

void ClrTimer(Timer_t * timer);
void ClrTimer_irq(Timer_t * timer);

void actionQueueInit(actionQueue_t *q, Timer_t *timer, msgType_t stepMsgType, msgType_t overMsgType);
int actionQueueIn(actionQueue_t *q, action_t *action);
int actionQueueOut(actionQueue_t *q, action_t *action);

#endif
