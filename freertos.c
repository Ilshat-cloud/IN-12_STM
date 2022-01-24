/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#include "tim.h"
#include "adc.h"
#include "dma.h"
#include "iwdg.h"
#include "rtc.h"
#include "gpio.h"
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
//==================================================================variables===============================================//
RTC_TimeTypeDef CurTime = {0};
uint32_t button=0;
uint8_t flag=0,PWM=10;
uint16_t EncoderVal,dma,i;
//--------------------------------------------------------------------------------------------------------------------------//
/* USER CODE END Variables */
/* Definitions for main */
osThreadId_t mainHandle;
const osThreadAttr_t main_attributes = {
  .name = "main",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for indication */
osThreadId_t indicationHandle;
const osThreadAttr_t indication_attributes = {
  .name = "indication",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartTask02(void *argument);

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

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of main */
  mainHandle = osThreadNew(StartDefaultTask, NULL, &main_attributes);

  /* creation of indication */
  indicationHandle = osThreadNew(StartTask02, NULL, &indication_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the main thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
  HAL_TIM_IC_Start_DMA(&htim4,TIM_CHANNEL_2,&button,1);  
  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
  EncoderVal=__HAL_TIM_GET_COUNTER(&htim3);
  /* Infinite loop */
  for(;;)
  {
    HAL_IWDG_Refresh(&hiwdg);
    if (flag==0)
    {
      HAL_RTC_GetTime(&hrtc, &CurTime, RTC_FORMAT_BIN);    
    }
    
    if ((button>500)&(flag==0))
      {
        flag=1;         //activate setting hours
        __HAL_TIM_SET_COUNTER(&htim3,CurTime.Hours);
        button=0;
      }
    if (flag!=0)
      {   
        if (button>500)
          {
            flag=0;             //close settings
            HAL_RTC_SetTime(&hrtc, &CurTime, RTC_FORMAT_BIN);
            button=0;
          }
        if (flag==1)
          {
            if(button>100)
              {
                __HAL_TIM_SET_COUNTER(&htim3,CurTime.Minutes);
                flag=2;
                button=0;
              }
          }
        if (flag==2)
          {
            if (button>100)
              {
                __HAL_TIM_SET_COUNTER(&htim3,CurTime.Hours);
                flag=1;
                button=0;
              }    
          } 

      }  

    
    osDelay(500);

  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the indication thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
  osDelay(500);
  uint8_t migalka=0,digit_set=0,digit;
  /* Infinite loop */
  for(;;)
  {
    HAL_ADC_Stop(&hadc1);
    HAL_ADC_Stop_DMA(&hadc1);
 //   PWM=87;
   //==================================PWM============================//
    if ((dma<voltage)&(PWM<93))
      {
         PWM++; 
      }
    else if ((dma>voltage)&(PWM>7))
      {
         PWM--;  
      }
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, PWM);
    //----------------------------------------------------------------//
    //==========================time management=======================//
    switch (flag)
    {
    case 1:
        CurTime.Hours=EncoderVal%24;
       break;
    case 2:
        CurTime.Minutes=EncoderVal%60;
       break;
    }
    //-----------------------------------------------------------------//
    
    EncoderVal=__HAL_TIM_GET_COUNTER(&htim3);
    HAL_GPIO_WritePin(Digit_1_GPIO_Port,Digit_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Digit_2_GPIO_Port,Digit_2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Digit_3_GPIO_Port,Digit_3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Digit_4_GPIO_Port,Digit_4_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Dot_GPIO_Port,Dot_Pin,GPIO_PIN_RESET );

    osDelay(1); //some delay becouse of lamps so slow
    
     //==========================time management=======================//
    switch (digit_set)
    {
    case 0:
       digit=CurTime.Hours/10;
       break;
    case 1:
       digit=CurTime.Hours%10; 
       break;
    case 2:
       digit=CurTime.Minutes/10;               
       break;
    case 3:
       digit=CurTime.Minutes%10; 
       break;

    }
    
    if (digit<10)                               //insurance
    {
      HAL_GPIO_WritePin(OUT_A0_GPIO_Port,OUT_A0_Pin, digit&0x01);
      HAL_GPIO_WritePin(OUT_A1_GPIO_Port,OUT_A1_Pin, digit&0x02);
      HAL_GPIO_WritePin(OUT_A2_GPIO_Port,OUT_A2_Pin, digit&0x04);
      HAL_GPIO_WritePin(OUT_A3_GPIO_Port,OUT_A3_Pin, digit&0x08);
    }else{digit=0;}

    //-----------------------------------------------------------------//   
    
        switch (digit_set)
    {
    case 0:
       HAL_GPIO_WritePin(Digit_1_GPIO_Port,Digit_1_Pin, GPIO_PIN_SET);
       break;
    case 1:
       HAL_GPIO_WritePin(Digit_2_GPIO_Port,Digit_2_Pin, GPIO_PIN_SET); 
       break;
    case 2:              
       HAL_GPIO_WritePin(Digit_3_GPIO_Port,Digit_3_Pin, GPIO_PIN_SET);
       break;
    case 3:
       HAL_GPIO_WritePin(Digit_4_GPIO_Port,Digit_4_Pin, GPIO_PIN_SET); 
       break;
    case 4:
      if (migalka>100)
        {
          HAL_GPIO_WritePin(Dot_GPIO_Port,Dot_Pin,GPIO_PIN_SET);
        }
      break;
    }
    
    //=========================blynk on the settings page and dot=============================//
    if (migalka>100)
      {
        if (flag==1)
          {
              HAL_GPIO_WritePin(Digit_1_GPIO_Port,Digit_1_Pin, GPIO_PIN_RESET);
              HAL_GPIO_WritePin(Digit_2_GPIO_Port,Digit_2_Pin, GPIO_PIN_RESET);
          }
        else if (flag==2)
          {
              HAL_GPIO_WritePin(Digit_3_GPIO_Port,Digit_3_Pin, GPIO_PIN_RESET);
              HAL_GPIO_WritePin(Digit_4_GPIO_Port,Digit_4_Pin, GPIO_PIN_RESET);
          }
        
      }
    if (migalka>200)
        {
        migalka=0;
        //digit++;                //debug
        }
    //--------------------------------------------------------------------------------//
    migalka++;
    //digit_set=1;                //debug
    digit_set++;
    digit_set=(digit_set>4)?0:digit_set;
    HAL_ADC_Start_DMA(&hadc1,(uint32_t*)&dma,1);
    osDelay(3);
  }
  /* USER CODE END StartTask02 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
