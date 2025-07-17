#ifndef __MOTOR_TASK_H__
#define __MOTOR_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "cmsis_os.h"
#include "tim.h"
#include "usart.h"
#include "key_task.h"
// 方向控制宏
// 正转
#define MOTOR_FORWARD() do { \
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET); \
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET); \
} while(0)
// 反转
#define MOTOR_BACKWARD() do { \
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET); \
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET); \
} while(0)
// 停止
#define MOTOR_STOP() do { \
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET); \
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET); \
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0); \
} while(0)

extern MotorState_t motorState; 

void StartMotorTask(void *argument);

#ifdef __cplusplus
}
#endif
#endif /* __MOTOR_TASK_H__ */
