/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    OpenAMP/OpenAMP_TTY_echo/Inc/main.c
  * @author  MCD Application Team
  * @brief   Main program body.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics. 
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the 
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
//#include "dma.h"
#include "fdcan.h"
#include "ipcc.h"
//#include "openamp.h"
#include "usart.h"
#include "gpio.h"
#include "fdcanutil.h"
#include "stdint.h";
#include "stdbool.h";
/* Private includes ----------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
#define MAX_BUFFER_SIZE RPMSG_BUFFER_SIZE


/* Private macro -------------------------------------------------------------*/


/* Private const -------------------------------------------------------------*/
const char m_szCMD_START[] = "start";
const char m_szCMD_STOPT[] = "stop";


/* Private variables ---------------------------------------------------------*/
//FDCAN_TxHeaderTypeDef TxHeader;
FDCAN_RxHeaderTypeDef m_stRxHeader;

uint8_t m_au8RxData[64];
uint8_t m_au8CanFdTrace[233]; //--> remove last only 0 termination for printf --> do not use printf use uart send

VIRT_UART_HandleTypeDef huart0;
VIRT_UART_HandleTypeDef huart1;

__IO FlagStatus VirtUart0RxMsg = RESET;
uint8_t VirtUart0ChannelBuffRx[MAX_BUFFER_SIZE];
uint16_t VirtUart0ChannelRxSize = 0;

__IO FlagStatus VirtUart1RxMsg = RESET;
uint8_t VirtUart1ChannelBuffRx[MAX_BUFFER_SIZE];
uint16_t VirtUart1ChannelRxSize = 0;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
bool bCreateCanFdTrace(FDCAN_RxHeaderTypeDef *pstRxHeader, uint32_t u32RxCount, uint8_t au8RxData[64], uint8_t au8TraceData[233]);

#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

#ifdef __GNUC__
#define GETCHAR_PROTOTYPE int __io_getchar (void)
#else
#define GETCHAR_PROTOTYPE int fgetc(FILE * f)
#endif /* __GNUC__ */

void VIRT_UART0_RxCpltCallback(VIRT_UART_HandleTypeDef *huart);
void VIRT_UART1_RxCpltCallback(VIRT_UART_HandleTypeDef *huart);
/* USER CODE END PFP */



uint8_t u8GetDataLength(uint32_t u32DataLengthCode) {
	uint8_t u8DataLength = 0;
	switch(u32DataLengthCode) {
	case FDCAN_DLC_BYTES_0:
		u8DataLength = 0;
		break;

	case FDCAN_DLC_BYTES_1:
		u8DataLength = 1;
		break;

	case FDCAN_DLC_BYTES_2:
		u8DataLength = 2;
		break;

	case FDCAN_DLC_BYTES_3:
		u8DataLength = 3;
		break;

	case FDCAN_DLC_BYTES_4:
		u8DataLength = 4;
		break;

	case FDCAN_DLC_BYTES_5:
		u8DataLength = 5;
		break;

	case FDCAN_DLC_BYTES_6:
		u8DataLength = 6;
		break;

	case FDCAN_DLC_BYTES_7:
		u8DataLength = 7;
		break;

	case FDCAN_DLC_BYTES_8:
		u8DataLength = 8;
		break;

	case FDCAN_DLC_BYTES_12:
		u8DataLength = 12;
		break;

	case FDCAN_DLC_BYTES_16:
		u8DataLength = 16;
		break;

	case FDCAN_DLC_BYTES_20:
		u8DataLength = 20;
		break;

	case FDCAN_DLC_BYTES_32:
		u8DataLength = 32;
		break;

	case FDCAN_DLC_BYTES_48:
		u8DataLength = 48;
		break;

	case FDCAN_DLC_BYTES_64:
		u8DataLength = 64;
		break;

	default:
		u8DataLength = 0;
		break;

	return u8DataLength;
	}
}

bool bCreateCanFdTrace(FDCAN_RxHeaderTypeDef *pstRxHeader, uint32_t u32RxCount, uint8_t au8RxData[64], uint8_t au8TraceData[233]) {
	memset(au8TraceData, 0x00, sizeof(au8TraceData));

	/*Field 0 - Message number: start at position 0, right align, max. 7 places*/
	snprintf((void*)&(au8TraceData[0]), 8, "%07u", u32RxCount);

	/*Field 1 - TimeOffset[ms]: start at position 8, right align, max. 9 places for [s] max 3 places for [ms]*/
	uint32_t u32Timestamp1s = pstRxHeader->RxTimestamp / 1000u;
	uint32_t u32Timestamp1ms = pstRxHeader->RxTimestamp % 1000u;
	snprintf((void*)&(au8TraceData[8]), 10, "%09u", u32Timestamp1s);
	au8TraceData[17] = '.';
	snprintf((void*)&(au8TraceData[18]), 4, "%03u", u32Timestamp1ms);

	/*Field 2 - Type:  start at position 22, 2 places */
	snprintf((void*)&(au8TraceData[22]), 3, "%s", "FB");

	/*Field 3 - CanId:  start at position 25, right align, max 8 places */
	snprintf((void*)&(au8TraceData[25]), 9, "%08X", pstRxHeader->Identifier);


	/*Field 4 - Rx/Tx:  start at position 34, 2 places */
	snprintf((void*)&(au8TraceData[34]), 3, "%s", "Rx");

	/*Field 5 - Data length: start at position 37, 2 places */
	snprintf((void*)&(au8TraceData[37]), 3, "%02u", u8GetDataLength(pstRxHeader->DataLength));

	/*Field 6 - Data: start at position 41, 192 places */
	for(int i = 0; i < 64; i++) {
		LxUtilities_vUint8ToHex(au8RxData[i], (void*)&(au8TraceData[40 + 3*i]));
	}

	/* replace null termination from snprintf with space*/
	for(uint32_t i = 0; i < 233; i++) {
		if(au8TraceData[i] == 0x00) {
			au8TraceData[i] = 32;
		}
	}

	/*Line End 1 places*/
	au8TraceData[232] = '\n';

	return true;
}



/* Private user code ---------------------------------------------------------*/


/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	uint32_t u32Tickstart;


  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initialize the Systick. */
  HAL_Init();


  /* USER CODE BEGIN Init */
  if(IS_ENGINEERING_BOOT_MODE())
  {
    /* Configure the system clock */
    HAL_RCC_DeInit();
    SystemClock_Config();
  }

  log_info("Cortex-M4 boot successful with STM32Cube FW version: v%ld.%ld.%ld \r\n",
                                            ((HAL_GetHalVersion() >> 24) & 0x000000FF),
                                            ((HAL_GetHalVersion() >> 16) & 0x000000FF),
                                            ((HAL_GetHalVersion() >> 8) & 0x000000FF));


  MX_USART3_UART_Init();
  MX_FDCAN2_Init();

  BSP_LED_Init(LED_GREEN);
  BSP_LED_Init(LED_RED);
  BSP_LED_Off(LED_GREEN);
  BSP_LED_Off(LED_RED);
  /* USER CODE END Init */

  /*HW semaphore Clock enable*/
  __HAL_RCC_HSEM_CLK_ENABLE();
  /* IPCC initialisation */
   MX_IPCC_Init();
  /* OpenAmp initialisation ---------------------------------*/
  MX_OPENAMP_Init(RPMSG_REMOTE, NULL);



  /*##-2 Start FDCAN controller (continuous listening CAN bus) ##############*/
  if (HAL_FDCAN_Start(&hfdcan2) != HAL_OK)
  {
    Error_Handler();
  }



  /* USER CODE BEGIN 2 */
  /*
   * Create Virtual UART device
   * defined by a rpmsg channel attached to the remote device
   */
  log_info("Virtual UART0 OpenAMP-rpmsg channel creation\r\n");
  if (VIRT_UART_Init(&huart0) != VIRT_UART_OK) {
    log_err("VIRT_UART_Init UART0 failed.\r\n");
    Error_Handler();
  }

  log_info("Virtual UART1 OpenAMP-rpmsg channel creation\r\n");
  if (VIRT_UART_Init(&huart1) != VIRT_UART_OK) {
    log_err("VIRT_UART_Init UART1 failed.\r\n");
    Error_Handler();
  }

  /*Need to register callback for message reception by channels*/
  if(VIRT_UART_RegisterCallback(&huart0, VIRT_UART_RXCPLT_CB_ID, VIRT_UART0_RxCpltCallback) != VIRT_UART_OK)
  {
   Error_Handler();
  }
  if(VIRT_UART_RegisterCallback(&huart1, VIRT_UART_RXCPLT_CB_ID, VIRT_UART1_RxCpltCallback) != VIRT_UART_OK)
  {
    Error_Handler();
  }

  uint32_t u32RxCount = 0;
  while(1) {
    u32Tickstart = HAL_GetTick();
    if (HAL_FDCAN_GetRxFifoFillLevel(&hfdcan2, FDCAN_RX_FIFO0) != 0)
    {
    	BSP_LED_On(LED_GREEN);
    	u32RxCount++;
      	/* Retrieve message from Rx FIFO 0 */
    	memset(m_au8RxData, 0u, sizeof(m_au8RxData));
    	memset(m_au8CanFdTrace, 0u, sizeof(m_au8CanFdTrace));

      	if (HAL_FDCAN_GetRxMessage(&hfdcan2, FDCAN_RX_FIFO0, &m_stRxHeader, m_au8RxData) == HAL_OK) {

      		m_stRxHeader.RxTimestamp = HAL_GetTick();
      		bCreateCanFdTrace(&m_stRxHeader, u32RxCount, m_au8RxData, m_au8CanFdTrace);

      		HAL_UART_Transmit(&huart3, m_au8CanFdTrace, sizeof(m_au8CanFdTrace), 0xFFFF);

  		    if (VIRT_UART_Transmit(&huart1, m_au8CanFdTrace, sizeof(m_au8CanFdTrace)) != VIRT_UART_OK) {
  				BSP_LED_On(LED_RED);
  				} else  {
  				BSP_LED_Off(LED_RED);
  		    }
      	} else {

      	}
  	}
	BSP_LED_Off(LED_GREEN);



    OPENAMP_check_for_message();

    /* USER CODE END WHILE */
    if (VirtUart0RxMsg) {
      VirtUart0RxMsg = RESET;
      VIRT_UART_Transmit(&huart0, VirtUart0ChannelBuffRx, VirtUart0ChannelRxSize);
    }

    if (VirtUart1RxMsg) {
      VirtUart1RxMsg = RESET;
      VIRT_UART_Transmit(&huart1, VirtUart1ChannelBuffRx, VirtUart1ChannelRxSize);
    }

  }
}



/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /**Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_MEDIUMHIGH);

  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE
                |RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS_DIG;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.HSIDivValue = RCC_HSI_DIV1;

  /**PLL1 Config
  */
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLL12SOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 3;
  RCC_OscInitStruct.PLL.PLLN = 81;
  RCC_OscInitStruct.PLL.PLLP = 1;
  RCC_OscInitStruct.PLL.PLLQ = 1;
  RCC_OscInitStruct.PLL.PLLR = 1;
  RCC_OscInitStruct.PLL.PLLFRACV = 0x800;
  RCC_OscInitStruct.PLL.PLLMODE = RCC_PLL_FRACTIONAL;
  RCC_OscInitStruct.PLL.RPDFN_DIS = RCC_RPDFN_DIS_DISABLED;
  RCC_OscInitStruct.PLL.TPDFN_DIS = RCC_TPDFN_DIS_DISABLED;

    /**PLL2 Config
    */
  RCC_OscInitStruct.PLL2.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL2.PLLSource = RCC_PLL12SOURCE_HSE;
  RCC_OscInitStruct.PLL2.PLLM = 3;
  RCC_OscInitStruct.PLL2.PLLN = 66;
  RCC_OscInitStruct.PLL2.PLLP = 2;
  RCC_OscInitStruct.PLL2.PLLQ = 1;
  RCC_OscInitStruct.PLL2.PLLR = 1;
  RCC_OscInitStruct.PLL2.PLLFRACV = 0x1400;
  RCC_OscInitStruct.PLL2.PLLMODE = RCC_PLL_FRACTIONAL;
  RCC_OscInitStruct.PLL2.RPDFN_DIS = RCC_RPDFN_DIS_DISABLED;
  RCC_OscInitStruct.PLL2.TPDFN_DIS = RCC_TPDFN_DIS_DISABLED;

    /**PLL3 Config
    */
  RCC_OscInitStruct.PLL3.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL3.PLLSource = RCC_PLL3SOURCE_HSE;
  RCC_OscInitStruct.PLL3.PLLM = 2;
  RCC_OscInitStruct.PLL3.PLLN = 34;
  RCC_OscInitStruct.PLL3.PLLP = 2;
  RCC_OscInitStruct.PLL3.PLLQ = 17;
  RCC_OscInitStruct.PLL3.PLLR = 37;
  RCC_OscInitStruct.PLL3.PLLRGE = RCC_PLL3IFRANGE_1;
  RCC_OscInitStruct.PLL3.PLLFRACV = 0x1A04;
  RCC_OscInitStruct.PLL3.PLLMODE = RCC_PLL_FRACTIONAL;
  RCC_OscInitStruct.PLL3.RPDFN_DIS = RCC_RPDFN_DIS_DISABLED;
  RCC_OscInitStruct.PLL3.TPDFN_DIS = RCC_TPDFN_DIS_DISABLED;

    /**PLL4 Config
    */
  RCC_OscInitStruct.PLL4.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL4.PLLSource = RCC_PLL4SOURCE_HSE;
  RCC_OscInitStruct.PLL4.PLLM = 4;
  RCC_OscInitStruct.PLL4.PLLN = 99;
  RCC_OscInitStruct.PLL4.PLLP = 6;
  RCC_OscInitStruct.PLL4.PLLQ = 8;
  RCC_OscInitStruct.PLL4.PLLR = 8;
  RCC_OscInitStruct.PLL4.PLLRGE = RCC_PLL4IFRANGE_0;
  RCC_OscInitStruct.PLL4.PLLFRACV = 0;
  RCC_OscInitStruct.PLL4.PLLMODE = RCC_PLL_INTEGER;
  RCC_OscInitStruct.PLL4.RPDFN_DIS = RCC_RPDFN_DIS_DISABLED;
  RCC_OscInitStruct.PLL4.TPDFN_DIS = RCC_TPDFN_DIS_DISABLED;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
  Error_Handler();
  }
  /**RCC Clock Config
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_ACLK
                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                |RCC_CLOCKTYPE_PCLK3|RCC_CLOCKTYPE_PCLK4
                |RCC_CLOCKTYPE_PCLK5|RCC_CLOCKTYPE_MPU;
  RCC_ClkInitStruct.MPUInit.MPU_Clock = RCC_MPUSOURCE_PLL1;
  RCC_ClkInitStruct.MPUInit.MPU_Div = RCC_MPU_DIV2;
  RCC_ClkInitStruct.AXISSInit.AXI_Clock = RCC_AXISSOURCE_PLL2;
  RCC_ClkInitStruct.AXISSInit.AXI_Div = RCC_AXI_DIV1;
  RCC_ClkInitStruct.MCUInit.MCU_Clock = RCC_MCUSSOURCE_PLL3;
  RCC_ClkInitStruct.MCUInit.MCU_Div = RCC_MCU_DIV1;
  RCC_ClkInitStruct.APB4_Div = RCC_APB4_DIV2;
  RCC_ClkInitStruct.APB5_Div = RCC_APB5_DIV4;
  RCC_ClkInitStruct.APB1_Div = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2_Div = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB3_Div = RCC_APB3_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct) != HAL_OK)
  {
  Error_Handler();
  }

  /**Set the HSE division factor for RTC clock
  */
  __HAL_RCC_RTC_HSEDIV(24);
}


int Serial_Scanf(char *ptr, int len)
{

  int DataIdx = 0;
  uint8_t thechar;
  thechar= ' ';
  while(thechar!= '\n' && thechar != '\r' && DataIdx<len)
  {
#ifdef __GNUC__
    thechar = __io_getchar();

#else
    thechar = fgetc(NULL);
#endif
  if ( thechar  >= 0xFF)
  {
    printf("\n\r  !!! Please enter a valid ASCII character \n");
    return 0xFF;
  }
  *ptr++ =thechar;
  DataIdx+=1;
  }
  return DataIdx;
}
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART3 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}


GETCHAR_PROTOTYPE
{
  uint8_t ch = 0;
  /* Clear the Overrun flag just before receiving the first character */
  __HAL_UART_CLEAR_OREFLAG(&huart3);

  HAL_UART_Receive(&huart3, (uint8_t *)&ch, 1, 0xFFFF);
  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xFFFF);
  return ch;
}

void VIRT_UART0_RxCpltCallback(VIRT_UART_HandleTypeDef *huart)
{

    log_info("Msg received on VIRTUAL UART0 channel:  %s \n\r", (char *) huart->pRxBuffPtr);

    /* copy received msg in a variable to sent it back to master processor in main infinite loop*/
    VirtUart0ChannelRxSize = huart->RxXferSize < MAX_BUFFER_SIZE? huart->RxXferSize : MAX_BUFFER_SIZE-1;
    memcpy(VirtUart0ChannelBuffRx, huart->pRxBuffPtr, VirtUart0ChannelRxSize);
    VirtUart0RxMsg = SET;
}

void VIRT_UART1_RxCpltCallback(VIRT_UART_HandleTypeDef *huart)
{

    log_info("Msg received on VIRTUAL UART1 channel:  %s \n\r", (char *) huart->pRxBuffPtr);

    /* copy received msg in a variable to sent it back to master processor in main infinite loop*/
    VirtUart1ChannelRxSize = huart->RxXferSize < MAX_BUFFER_SIZE? huart->RxXferSize : MAX_BUFFER_SIZE-1;
    memcpy(VirtUart1ChannelBuffRx, huart->pRxBuffPtr, VirtUart1ChannelRxSize);
    VirtUart1RxMsg = SET;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  log_err("Error_Handler");
  BSP_LED_Off(LED1);
  while(1)
  {
	  BSP_LED_Toggle(LED_RED);
	  HAL_Delay(50);
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  log_err("OOOps: file %s, line %d\r\n", __FILE__, __LINE__);
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
