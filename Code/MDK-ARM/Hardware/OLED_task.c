#include "OLED_task.h"

void StartOLEDTask(void *argument)
{
		OLED_Init();
    for(;;)
    {
        OLED_ShowString(1, 1, "LED:");
        OLED_ShowNum(1, 6, ledState, 1);

        OLED_ShowString(2, 1, "Motor:");
        OLED_ShowNum(2, 7, motorState, 1);

        OLED_ShowString(3, 1, "Servo:");
        OLED_ShowNum(3, 8, servoState, 1);

        osDelay(200);
    }
}
