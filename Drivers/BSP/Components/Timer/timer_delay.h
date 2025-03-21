#ifndef TIMER_DELAY_H
#define TIMER_DELAY_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* External Function ---------------------------------------------------------*/
int	  DwtInit(TIM_TypeDef *timer, uint32_t clock);
void  DwtStart(void);
float DwtInterval(void);
void  DwtDelay_us(uint32_t usec);

#ifdef __cplusplus
}
#endif

#endif /* TIMER_DELAY_H */
