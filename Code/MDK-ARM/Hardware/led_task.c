#include "led_task.h"

// 定义LED状态变量
LedState_t ledState = LED_STATE_OFF;
extern TIM_HandleTypeDef htim3;
extern osMessageQueueId_t ledQueueHandle; 

void StartLEDTask(void *argument) {
    LedState_t receivedState;
    osStatus_t res;
    // LED亮度范围 (0-99)
    const uint16_t maxBrightness = 99;
    uint16_t duty = 0;
    int8_t direction = 1;
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);

    for (;;) {
		// 每次循环检查LED状态队列
        // 检查队列是否有新消息（不阻塞）
        res = osMessageQueueGet(ledQueueHandle, &receivedState, NULL, 0);
        if (res == osOK) {
            ledState = receivedState;
        }
		if(res != osOK && res != osErrorResource) {
			printf("error: %d\r\n", res);
		}
		
		// 根据当前状态设置LED亮度
		// printf("receivedState: %d\r\n", ledState);
        switch (ledState) {
            case LED_STATE_OFF:
                __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
                osDelay(10);
                break;
            case LED_STATE_50_BRIGHT:
                __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 50);
                osDelay(10);
                break;
            case LED_STATE_100_BRIGHT:
                __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 100);
                osDelay(10);
                break;
            case LED_STATE_BREATH:
                __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, duty);
                duty += direction;
                if (duty >= maxBrightness) { duty = maxBrightness; direction = -1; }
                else if (duty <= 0) { duty = 0; direction = 1; }
                osDelay(10);
                break;
			default:
				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
				osDelay(10);
				break;
        }
    }
}

