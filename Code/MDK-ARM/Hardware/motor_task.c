#include "motor_task.h"

// 定义电机状态变量
MotorState_t motorState = Motor_STATE_OFF;
extern TIM_HandleTypeDef htim1;
extern osMessageQueueId_t motorQueueHandle;

void StartMotorTask(void *argument)
{
  MotorState_t receivedState;
  osStatus_t res;
  // 速度范围 (0-90% 安全范围)
  const uint16_t min_speed = 0;     // 0% 占空比
  const uint16_t max_speed = 900;   // 90% 占空比
  
  for(;;)
  {
		printf("motor_task3\r\n");
    // 正转加速
    MOTOR_FORWARD();
    res = osMessageQueueGet(motorQueueHandle, &receivedState, NULL, 0);
    if (res == osOK) {  
      motorState = receivedState;
    }
    if(res != osOK && res != osErrorResource) {
      printf("error: %d\r\n", res);
    }
    // 根据当前状态设置电机速度
    printf("receivedState: %d\r\n", motorState);
    switch (motorState) {
      case Motor_STATE_OFF:
        MOTOR_STOP();
        osDelay(10);
        break;
      case Motor_STATE_50_SPEED:
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, min_speed + (max_speed - min_speed) * 50 / 100);
        osDelay(10);
        break;
      case Motor_STATE_100_SPEED:
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, max_speed);
        osDelay(10);
        break;
      default:
        MOTOR_STOP();
        osDelay(10);
        break;
    }
    
  }
}
