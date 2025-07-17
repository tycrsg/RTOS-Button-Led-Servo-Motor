#ifndef KEY_TASK_H
#define KEY_TASK_H

#include "main.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "gpio.h"
#include "task.h"
#include "queue.h"

/* 声明外部变量（告诉编译器这些变量在其他文件中定义） */
extern osMessageQueueId_t motorQueueHandle;
extern osMessageQueueId_t servoQueueHandle;
extern osMessageQueueId_t ledQueueHandle;

// 按键定义
#define KEY_MOTOR_PIN GPIO_PIN_1
#define KEY_SERVO_PIN GPIO_PIN_10
#define KEY_LED_PIN   GPIO_PIN_0
#define KEY_MOTOR_GPIO_Port GPIOB
#define KEY_SERVO_GPIO_Port GPIOB
#define KEY_LED_GPIO_Port   GPIOB
// 按键读取宏
#define KEY3        HAL_GPIO_ReadPin(KEY_MOTOR_GPIO_Port, KEY_MOTOR_PIN)   /* 读取KEY1引脚状态（SW3） */
#define KEY2        HAL_GPIO_ReadPin(KEY_SERVO_GPIO_Port, KEY_SERVO_PIN)   /* 读取KEY2引脚状态（SW4） */
#define KEY1        HAL_GPIO_ReadPin(KEY_LED_GPIO_Port  , KEY_LED_PIN  )   /* 读取KEY3引脚状态（SW5） */
// 按键按下时返回的值
#define KEY1_PRESS    1              
#define KEY2_PRESS    2              
#define KEY3_PRESS    3              

// 定义 LED 状态枚举
typedef enum {
   LED_STATE_OFF,        // 关闭
   LED_STATE_50_BRIGHT,  // 50%亮度
   LED_STATE_100_BRIGHT, // 100%亮度
   LED_STATE_BREATH      // 呼吸灯
} LedState_t;
// 定义servo状态枚举
typedef enum {
		Servo_STATE_OFF,
		Servo_STATE_30_ANGLE,
		Servo_STATE_90_ANGLE,
		Servo_STATE_120_ANGLE,
      Servo_STATE_180_ANGLE
}ServoState_t;
// 定义motor状态枚举
typedef enum {
       Motor_STATE_OFF,
       Motor_STATE_50_SPEED,
       Motor_STATE_100_SPEED
}MotorState_t;

uint8_t Key_Detect(void);
void StartKeyTask(void *argument);

#endif
