#ifndef __LED_TASK_H__
#define __LED_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "cmsis_os.h"
#include "tim.h"  // 必须包含，用于访问htim1
#include "key_task.h"
#include "usart.h"

extern LedState_t ledState;
void StartLEDTask(void *argument);

#ifdef __cplusplus
}
#endif
#endif /* __LED_TASK_H__ */
