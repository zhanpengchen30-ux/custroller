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
#include "DRK_encoder.h"

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

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId Read_DataHandle;
osThreadId Send_DataHandle;
osThreadId Recieve_DataHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void vTaskreaddata(void const * argument);
void vTasksenddata(void const * argument);
void vTaskrecievedata(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )
{
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
  *ppxTimerTaskStackBuffer = &xTimerStack[0];
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
  /* place for user code */
}
/* USER CODE END GET_TIMER_TASK_MEMORY */

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

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of Read_Data */
  osThreadDef(Read_Data, vTaskreaddata, osPriorityNormal, 0, 128);
  Read_DataHandle = osThreadCreate(osThread(Read_Data), NULL);

  /* definition and creation of Send_Data */
  osThreadDef(Send_Data, vTasksenddata, osPriorityNormal, 0, 128);
  Send_DataHandle = osThreadCreate(osThread(Send_Data), NULL);

  /* definition and creation of Recieve_Data */
  osThreadDef(Recieve_Data, vTaskrecievedata, osPriorityNormal, 0, 128);
  Recieve_DataHandle = osThreadCreate(osThread(Recieve_Data), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_vTaskreaddata */
/**
* @brief Function implementing the Read_Data thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_vTaskreaddata */
void vTaskreaddata(void const * argument)
{
  /* USER CODE BEGIN vTaskreaddata */
  /* Infinite loop */
  for(;;)
  {
		  read_DRK_encoder_value(DRK_encoder_ID_1);
//    osDelay(1);
      read_DRK_encoder_value(DRK_encoder_ID_2);
//    osDelay(1);
      read_DRK_encoder_value(DRK_encoder_ID_3);
//    osDelay(1);
		  read_DRK_encoder_value(DRK_encoder_ID_4);
//    osDelay(1);
      read_DRK_encoder_value(DRK_encoder_ID_5);
////    osDelay(1);
      read_DRK_encoder_value(DRK_encoder_ID_6);
//    osDelay(1);
  }
  /* USER CODE END vTaskreaddata */
}

/* USER CODE BEGIN Header_vTasksenddata */
/**
* @brief Function implementing the Send_Data thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_vTasksenddata */
void vTasksenddata(void const * argument)
{
  /* USER CODE BEGIN vTasksenddata */
  /* Infinite loop */
  for(;;)
  {
        Send_EncoderAngle(&DRK_encoder[0],DRK_encoder_ID_1);
//    osDelay(1);
        Send_EncoderAngle(&DRK_encoder[1],DRK_encoder_ID_2);
//    osDelay(1);
        Send_EncoderAngle(&DRK_encoder[2],DRK_encoder_ID_3);
//    osDelay(1);
        Send_EncoderAngle(&DRK_encoder[3],DRK_encoder_ID_4);
//    osDelay(1);
        Send_EncoderAngle(&DRK_encoder[4],DRK_encoder_ID_5);
//    osDelay(1);
        Send_EncoderAngle(&DRK_encoder[5],DRK_encoder_ID_6);
    osDelay(10);
  }
  /* USER CODE END vTasksenddata */
}

/* USER CODE BEGIN Header_vTaskrecievedata */
/**
* @brief Function implementing the Recieve_Data thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_vTaskrecievedata */
void vTaskrecievedata(void const * argument)
{
  /* USER CODE BEGIN vTaskrecievedata */
  /* Infinite loop */
  for(;;)
  {
//        Receive_EncoderAngle(&DRK_encoder[0]);
//        Receive_EncoderAngle(&DRK_encoder[1]);
//        Receive_EncoderAngle(&DRK_encoder[2]);
    osDelay(1);
  }
  /* USER CODE END vTaskrecievedata */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
