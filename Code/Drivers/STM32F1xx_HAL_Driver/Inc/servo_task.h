#ifndef __SERVO_TASK_H__
#define __SERVO_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "cmsis_os.h"
#include "tim.h"  // 必须包含，用于访问htim1
#include "usart.h"
#include "key_task.h"
extern ServoState_t servoState;
void StartServoTask(void *argument);

#ifdef __cplusplus
}
#endif
#endif /* __SERVO_TASK_H__ */
