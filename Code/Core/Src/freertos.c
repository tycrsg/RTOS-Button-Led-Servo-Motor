/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "motor_task.h"
#include "servo_task.h"
#include "led_task.h"
#include "key_task.h"
#include "OLED_task.h"
#include "usart.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
volatile uint8_t key1_flag = 0;
volatile uint8_t key2_flag = 0;
volatile uint8_t key3_flag = 0;
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for MotorTask */
osThreadId_t MotorTaskHandle;
const osThreadAttr_t MotorTask_attributes = {
  .name = "MotorTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal3,
};
/* Definitions for ServoTask */
osThreadId_t ServoTaskHandle;
const osThreadAttr_t ServoTask_attributes = {
  .name = "ServoTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal2,
};
/* Definitions for LEDTask */
osThreadId_t LEDTaskHandle;
const osThreadAttr_t LEDTask_attributes = {
  .name = "LEDTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal1,
};
/* Definitions for Key_TASK */
osThreadId_t Key_TASKHandle;
const osThreadAttr_t Key_TASK_attributes = {
  .name = "Key_TASK",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for OLEDtask */
osThreadId_t OLEDtaskHandle;
const osThreadAttr_t OLEDtask_attributes = {
  .name = "OLEDtask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for motorQueue */
osMessageQueueId_t motorQueueHandle;
const osMessageQueueAttr_t motorQueue_attributes = {
  .name = "motorQueue"
};
/* Definitions for servoQueue */
osMessageQueueId_t servoQueueHandle;
const osMessageQueueAttr_t servoQueue_attributes = {
  .name = "servoQueue"
};
/* Definitions for ledQueue */
osMessageQueueId_t ledQueueHandle;
const osMessageQueueAttr_t ledQueue_attributes = {
  .name = "ledQueue"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartMotorTask(void *argument);
void StartServoTask(void *argument);
void StartLEDTask(void *argument);
void StartKeyTask(void *argument);
void StartOLEDTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of motorQueue */
  motorQueueHandle = osMessageQueueNew (16, sizeof(uint16_t), &motorQueue_attributes);

  /* creation of servoQueue */
  servoQueueHandle = osMessageQueueNew (16, sizeof(uint16_t), &servoQueue_attributes);

  /* creation of ledQueue */
  ledQueueHandle = osMessageQueueNew (16, sizeof(uint16_t), &ledQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of MotorTask */
  MotorTaskHandle = osThreadNew(StartMotorTask, NULL, &MotorTask_attributes);

  /* creation of ServoTask */
  ServoTaskHandle = osThreadNew(StartServoTask, NULL, &ServoTask_attributes);

  /* creation of LEDTask */
  LEDTaskHandle = osThreadNew(StartLEDTask, NULL, &LEDTask_attributes);

  /* creation of Key_TASK */
  Key_TASKHandle = osThreadNew(StartKeyTask, NULL, &Key_TASK_attributes);

  /* creation of OLEDtask */
  OLEDtaskHandle = osThreadNew(StartOLEDTask, NULL, &OLEDtask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartMotorTask */
/**
* @brief Function implementing the MotorTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartMotorTask */
//void StartMotorTask(void *argument)
//{
//  /* USER CODE BEGIN StartMotorTask */
//  /* Infinite loop */
//  for(;;)
//  {
//    osDelay(1);
//  }
//  /* USER CODE END StartMotorTask */
//}

///* USER CODE BEGIN Header_StartServoTask */
///**
//* @brief Function implementing the ServoTask thread.
//* @param argument: Not used
//* @retval None
//*/
///* USER CODE END Header_StartServoTask */
//void StartServoTask(void *argument)
//{
//  /* USER CODE BEGIN StartServoTask */
//  /* Infinite loop */
//  for(;;)
//  {
//    osDelay(1);
//  }
//  /* USER CODE END StartServoTask */
//}

///* USER CODE BEGIN Header_StartLEDTask */
///**
//* @brief Function implementing the BreathingTask thread.
//* @param argument: Not used
//* @retval None
//*/
///* USER CODE END Header_StartLEDTask */
//void StartLEDTask(void *argument)
//{
//  /* USER CODE BEGIN StartLEDTask */
//  /* Infinite loop */
//  for(;;)
//  {
//    osDelay(1);
//  }
//  /* USER CODE END StartLEDTask */
//}

///* USER CODE BEGIN Header_StartKeyTask */
///**
//* @brief Function implementing the Key_TASK thread.
//* @param argument: Not used
//* @retval None
//*/
///* USER CODE END Header_StartKeyTask */
//void StartKeyTask(void *argument)
//{
//  /* USER CODE BEGIN StartKeyTask */
//   /* Infinite loop */
//   for(;;)
//   {
// 		printf("key_task1\r\n");
//     osDelay(1);
//   }
//  /* USER CODE END StartKeyTask */
//}

///* USER CODE BEGIN Header_StartOLEDTask */
///**
//* @brief Function implementing the OLEDtask thread.
//* @param argument: Not used
//* @retval None
//*/
///* USER CODE END Header_StartOLEDTask */
//void StartOLEDTask(void *argument)
//{
//  /* USER CODE BEGIN StartOLEDTask */
//  /* Infinite loop */
//  for(;;)
//  {
//    osDelay(1);
//  }
//  /* USER CODE END StartOLEDTask */
//}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

