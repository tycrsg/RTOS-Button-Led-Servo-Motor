#include "servo_task.h"

// 定义舵机状态变量
ServoState_t servoState = Servo_STATE_OFF;
extern TIM_HandleTypeDef htim2;
extern osMessageQueueId_t servoQueueHandle;


void StartServoTask(void *argument) {
  ServoState_t receivedState;
  osStatus_t res;
  // 舵机角度范围 (0-180度)
  const uint16_t minAngle = 500;  // 0.5ms (0度)
  const uint16_t maxAngle = 2500; // 2.5ms (180度)
  const uint16_t midAngle = (minAngle + maxAngle) / 2; // 90度
  
  for(;;) {
		printf("servo_task2\r\n");
    // 每次循环检查舵机状态队列
    // 检查队列是否有新消息（不阻塞）
    res = osMessageQueueGet(servoQueueHandle, &receivedState, NULL, 0);
    if (res == osOK) {
      servoState = receivedState;
    }
    if(res != osOK && res != osErrorResource) {
      printf("error: %d\r\n", res);
    }
    // 根据当前状态设置舵机角度
    // printf("receivedState: %d\r\n", servoState);
    switch (servoState) {
      case Servo_STATE_OFF:
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, minAngle);
        osDelay(10);
        break;
      case Servo_STATE_30_ANGLE:
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, minAngle + (maxAngle - minAngle) * 30 / 180);
        osDelay(10);
        break;
      case Servo_STATE_90_ANGLE:
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, midAngle);
        osDelay(10);
        break;
      case Servo_STATE_120_ANGLE:
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, minAngle + (maxAngle - minAngle) * 120 / 180);
        osDelay(10);
        break;
      case Servo_STATE_180_ANGLE:
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, maxAngle);
        osDelay(10);
        break;
      default:
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, minAngle);
        osDelay(10);
        break;
    }
  }
}
