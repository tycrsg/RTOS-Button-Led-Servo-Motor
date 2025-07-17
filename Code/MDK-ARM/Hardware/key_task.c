#include "key_task.h"

uint8_t Key_Detect(void)
{
    // 按键优先级：KEY3 > KEY2 > KEY1
    if (KEY3 == GPIO_PIN_RESET) { // 按下为低电平
        HAL_Delay(10); // 去抖动
        if (KEY3 == GPIO_PIN_RESET) return KEY3_PRESS;
    }
    if (KEY2 == GPIO_PIN_RESET) {
        HAL_Delay(10);
        if (KEY2 == GPIO_PIN_RESET) return KEY2_PRESS;
    }
    if (KEY1 == GPIO_PIN_RESET) {
        HAL_Delay(10);
        if (KEY1 == GPIO_PIN_RESET) return KEY1_PRESS;
    }
    return 0;
}

void StartKeyTask(void *argument)
{
    uint8_t key = 0;
    uint8_t last_key = 0;
    LedState_t ledState = LED_STATE_OFF;
    MotorState_t motorState = Motor_STATE_OFF;
    ServoState_t servoState = Servo_STATE_OFF;
    osStatus_t res;	
    for( ; ; )
    {
				(void)res;
        key = Key_Detect();
        if (key != 0 && last_key == 0) { // 只在按下瞬间响应一次
            if (key == KEY1_PRESS) {
                switch (ledState) {
                    case LED_STATE_OFF:
                        ledState = LED_STATE_50_BRIGHT;
                        break;
                    case LED_STATE_50_BRIGHT:
                        ledState = LED_STATE_100_BRIGHT;
                        break;
                    case LED_STATE_100_BRIGHT:
                        ledState = LED_STATE_BREATH;
                        break;
                    case LED_STATE_BREATH:
                        ledState = LED_STATE_OFF;
                        break;
                    default:
                        ledState = LED_STATE_OFF;
                        break; 
                }
                res = osMessageQueuePut(
                    ledQueueHandle,
                    &ledState,
                    0U,
                    portMAX_DELAY
                );
            }
        }
    if (key != 0 && last_key == 0) {    
       if  (key==KEY2_PRESS){
           switch (servoState) {
               case Servo_STATE_OFF:
                   servoState = Servo_STATE_30_ANGLE;
                   break;
               case Servo_STATE_30_ANGLE:
                   servoState = Servo_STATE_90_ANGLE;
                   break;
               case Servo_STATE_90_ANGLE:
                   servoState = Servo_STATE_120_ANGLE;
                   break;
               case Servo_STATE_120_ANGLE:
                   servoState = Servo_STATE_180_ANGLE;
                   break;
                case Servo_STATE_180_ANGLE:
                   servoState = Servo_STATE_OFF;
                   break;
               default:
                   servoState = Servo_STATE_OFF;
                   break;
           }
              res = osMessageQueuePut(  
                servoQueueHandle,  // CubeMX生成的句柄
                &servoState,         // 要发送的数据
                0U,                // 消息优先级
                portMAX_DELAY      // 超时时间（一直等待）
         );
        }
        }
    if (key != 0 && last_key == 0) {
       if (key == KEY3_PRESS) {
           switch (motorState) {
               case Motor_STATE_OFF:
                   motorState = Motor_STATE_50_SPEED;
                   break;
               case Motor_STATE_50_SPEED:
                   motorState = Motor_STATE_100_SPEED;
                   break;
               case Motor_STATE_100_SPEED:
                   motorState = Motor_STATE_OFF;
                   break;
               default:
                   motorState = Motor_STATE_OFF;
                   break;
           }
              res = osMessageQueuePut(  
                 motorQueueHandle,  // CubeMX生成的句柄
                 &motorState,         // 要发送的数据
                 0U,                // 消息优先级
                 portMAX_DELAY      // 超时时间（一直等待）
              );
       }
    }
       last_key = key; // 记录上一次的按键状态
        osDelay(10);    // 防止任务跑太快
	}
}
