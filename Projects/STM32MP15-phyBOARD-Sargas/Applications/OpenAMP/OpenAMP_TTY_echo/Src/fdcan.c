/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    fdcan.c
  * @brief   This file provides code for the configuration
  *          of the FDCAN instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "fdcan.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

FDCAN_HandleTypeDef hfdcan2;

/* FDCAN2 init function */
void MX_FDCAN2_Init(void)
{

  /* USER CODE BEGIN FDCAN2_Init 0 */

  /* USER CODE END FDCAN2_Init 0 */

  /* USER CODE BEGIN FDCAN2_Init 1 */

  /* USER CODE END FDCAN2_Init 1 */
  hfdcan2.Instance = FDCAN2;
  hfdcan2.Init.FrameFormat = FDCAN_FRAME_FD_NO_BRS;
  hfdcan2.Init.Mode = FDCAN_MODE_NORMAL;
  hfdcan2.Init.AutoRetransmission = ENABLE;
  hfdcan2.Init.TransmitPause = DISABLE;
  hfdcan2.Init.ProtocolException = ENABLE;
  hfdcan2.Init.NominalPrescaler = 3;
  hfdcan2.Init.NominalSyncJumpWidth = 1;
  hfdcan2.Init.NominalTimeSeg1 = 5;
  hfdcan2.Init.NominalTimeSeg2 = 2;
  hfdcan2.Init.DataPrescaler = 3;
  hfdcan2.Init.DataSyncJumpWidth = 1;
  hfdcan2.Init.DataTimeSeg1 = 5;
  hfdcan2.Init.DataTimeSeg2 = 2;
  hfdcan2.Init.MessageRAMOffset = 0;
  hfdcan2.Init.StdFiltersNbr = 0;
  hfdcan2.Init.ExtFiltersNbr = 0;
  hfdcan2.Init.RxFifo0ElmtsNbr = 8;
  hfdcan2.Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_64;
  hfdcan2.Init.RxFifo1ElmtsNbr = 0;
  hfdcan2.Init.RxFifo1ElmtSize = FDCAN_DATA_BYTES_64;
  hfdcan2.Init.RxBuffersNbr = 8;
  hfdcan2.Init.RxBufferSize = FDCAN_DATA_BYTES_64;
  hfdcan2.Init.TxEventsNbr = 2;
  hfdcan2.Init.TxBuffersNbr = 8;
  hfdcan2.Init.TxFifoQueueElmtsNbr = 8;
  hfdcan2.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
  hfdcan2.Init.TxElmtSize = FDCAN_DATA_BYTES_64;
  if (HAL_FDCAN_Init(&hfdcan2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN FDCAN2_Init 2 */

  /* USER CODE END FDCAN2_Init 2 */

}

//void HAL_FDCAN_MspInit(FDCAN_HandleTypeDef* fdcanHandle)
//{
//
//  GPIO_InitTypeDef GPIO_InitStruct = {0};
//  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
//  if(fdcanHandle->Instance==FDCAN2)
//  {
//  /* USER CODE BEGIN FDCAN2_MspInit 0 */
//
//  /* USER CODE END FDCAN2_MspInit 0 */
//  if(IS_ENGINEERING_BOOT_MODE())
//  {
//  /** Initializes the peripherals clock
//  */
//    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;
//    PeriphClkInit.FdcanClockSelection = RCC_FDCANCLKSOURCE_HSE;
//    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
//    {
//      Error_Handler();
//    }
//
//  }
//
//    /* FDCAN2 clock enable */
//    __HAL_RCC_FDCAN_CLK_ENABLE();
//
//    __HAL_RCC_GPIOB_CLK_ENABLE();
//    /**FDCAN2 GPIO Configuration
//    PB5     ------> FDCAN2_RX
//    PB13     ------> FDCAN2_TX
//    */
//    GPIO_InitStruct.Pin = GPIO_PIN_5;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN2;
//    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//
//    GPIO_InitStruct.Pin = GPIO_PIN_13;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//    GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN2;
//    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//
//  /* USER CODE BEGIN FDCAN2_MspInit 1 */
//
//  /* USER CODE END FDCAN2_MspInit 1 */
//  }
//}

//void HAL_FDCAN_MspDeInit(FDCAN_HandleTypeDef* fdcanHandle)
//{
//
//  if(fdcanHandle->Instance==FDCAN2)
//  {
//  /* USER CODE BEGIN FDCAN2_MspDeInit 0 */
//
//  /* USER CODE END FDCAN2_MspDeInit 0 */
//    /* Peripheral clock disable */
//    __HAL_RCC_FDCAN_CLK_DISABLE();
//
//    /**FDCAN2 GPIO Configuration
//    PB5     ------> FDCAN2_RX
//    PB13     ------> FDCAN2_TX
//    */
//    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_5|GPIO_PIN_13);
//
//  /* USER CODE BEGIN FDCAN2_MspDeInit 1 */
//
//  /* USER CODE END FDCAN2_MspDeInit 1 */
//  }
//}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
