#include "timer_delay.h"
#include <assert.h>

static TIM_HandleTypeDef Timer;

static uint16_t start;

/**
 * @brief  Initialize DWT
 */
int DwtInit(TIM_TypeDef *timer, uint32_t clock) {
	assert(timer);
	Timer.Instance				 = timer;
	Timer.Init.Prescaler		 = (clock / 1000000) - 1;
	Timer.Init.CounterMode		 = TIM_COUNTERMODE_UP;
	Timer.Init.Period			 = 0xFFFFFFFF;
	Timer.Init.ClockDivision	 = TIM_CLOCKDIVISION_DIV1;
	Timer.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	if (HAL_OK != HAL_TIM_Base_Init(&Timer)) {
		return 0;
	}
	if (HAL_OK != HAL_TIM_Base_Start(&Timer)) {
		return 0;
	}
	return 1;
}

/**
 * @brief  Start DWT Counter
 */
void DwtStart(void) {
	start = __HAL_TIM_GET_COUNTER(&Timer);
}

/**
 * @brief  Calculate Interval Base On Previous Start Time
 * @retval Interval in us
 */
float DwtInterval(void) {
	return (float)(__HAL_TIM_GET_COUNTER(&Timer) - start);
}

/**
 * @brief  Function to delay in microsecond
 * @param	usec	Period in microsecond
 */
inline void DwtDelay_us(uint32_t usec) {
	start = __HAL_TIM_GET_COUNTER(&Timer);
	while ((__HAL_TIM_GET_COUNTER(&Timer) - start) < usec) {
	};
}
