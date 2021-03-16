/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define RX_BUFFER_SIZE   12
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/**
  * @brief RX buffers for storing received data
  */
uint8_t aRXBufferA[RX_BUFFER_SIZE];
uint8_t aRXBufferB[RX_BUFFER_SIZE];

uint8_t aTextInfoStart[] = "\r\nStarting UART Connection....\r\n";
uint8_t aTextInfoSwap1[] = "\r\n- Current RX buffer is full : ";
uint8_t aTextInfoSwap2[] = "\r\n- Reception will go on in alternate buffer\r\n";

__IO uint32_t     uwNbReceivedChars;
__IO uint32_t     uwBufferReadyIndication;
uint8_t *pBufferReadyForUser;
uint8_t *pBufferReadyForReception;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void StartReception(void);
void PrintData(uint8_t *String, uint32_t Size);
void UserDataTreatment(uint8_t *DataBuffer, uint32_t Size);
void HandleContinuousReception(void);
void USART_CharReception_Callback(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* System interrupt init*/

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */
  /* Initiate Continuous reception */
    StartReception();
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	/* Handle Continuous reception */
	HandleContinuousReception();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_4);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_4)
  {
  }
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
  LL_RCC_MSI_Enable();

   /* Wait till MSI is ready */
  while(LL_RCC_MSI_IsReady() != 1)
  {

  }
  LL_RCC_MSI_EnableRangeSelection();
  LL_RCC_MSI_SetRange(LL_RCC_MSIRANGE_6);
  LL_RCC_MSI_SetCalibTrimming(0);
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_MSI, LL_RCC_PLLM_DIV_1, 40, LL_RCC_PLLR_DIV_2);
  LL_RCC_PLL_EnableDomain_SYS();
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {

  }
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {

  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

  LL_Init1msTick(80000000);

  LL_SetSystemCoreClock(80000000);
  LL_RCC_SetUSARTClockSource(LL_RCC_USART2_CLKSOURCE_PCLK1);
}

/* USER CODE BEGIN 4 */
/**
  * @brief  Send Txt information message on USART Tx line (to PC Com port).
  * @param  None
  * @retval None
  */
void PrintData(uint8_t *String, uint32_t Size)
{
  uint32_t index = 0;
  uint8_t *pchar = String;

  /* Send characters one per one, until last char to be sent */
  for (index = 0; index < Size; index++)
  {
    /* Wait for TXE flag to be raised */
    while (!LL_USART_IsActiveFlag_TXE(USART2))
    {
    }

    /* Write character in Transmit Data register.
       TXE flag is cleared by writing data in TDR register */
    LL_USART_TransmitData8(USART2, *pchar++);
  }

  /* Wait for TC flag to be raised for last char */
  while (!LL_USART_IsActiveFlag_TC(USART2))
  {
  }
}

/**
  * @brief  This function prints user info on PC com port and initiates RX transfer
  * @param  None
  * @retval None
  */
void StartReception(void)
{
  /* Initializes Buffer swap mechanism :
     - 2 physical buffers aRXBufferA and aRXBufferB (RX_BUFFER_SIZE length)

  */
  pBufferReadyForReception = aRXBufferA;
  pBufferReadyForUser      = aRXBufferB;
  uwNbReceivedChars = 0;
  uwBufferReadyIndication = 0;

  /* Print user info on PC com port */
  PrintData(aTextInfoStart, sizeof(aTextInfoStart));

  /* Clear Overrun flag, in case characters have already been sent to USART */
  LL_USART_ClearFlag_ORE(USART2);

  /* Enable RXNE and Error interrupts */
  LL_USART_EnableIT_RXNE(USART2);
  LL_USART_EnableIT_ERROR(USART2);
}

/**
  * @brief  This function monitors buffer filling indication and calls User callbacks when a buffer is full
  * @param  None
  * @retval None
  */
void HandleContinuousReception(void)
{
  /* Checks if Buffer full indication has been set */
  if (uwBufferReadyIndication != 0)
  {
    /* Reset indication */
    uwBufferReadyIndication = 0;

    /* Call user Callback in charge of consuming data from filled buffer */
    UserDataTreatment(pBufferReadyForUser, RX_BUFFER_SIZE);
  }
}

/**
  * @brief  Example of User callback in charge of consuming received data.
  * @param  None
  * @retval None
  */
void UserDataTreatment(uint8_t *DataBuffer, uint32_t Size)
{
  /* Display info message + buffer content on PC com port */
  PrintData(aTextInfoSwap1, sizeof(aTextInfoSwap1));
  PrintData(DataBuffer, Size);
  PrintData(aTextInfoSwap2, sizeof(aTextInfoSwap2));
}


/**
  * @brief  Function called from USART IRQ Handler when RXNE flag is set
  *         Function is in charge of reading character received on USART RX line.
  * @param  None
  * @retval None
  */
void USART_CharReception_Callback(void)
{
uint8_t *ptemp;

  /* Read Received character. RXNE flag is cleared by reading of RDR register */
  pBufferReadyForReception[uwNbReceivedChars++] = LL_USART_ReceiveData8(USART2);

  /* Checks if Buffer full indication has been set */
  if (uwNbReceivedChars >= RX_BUFFER_SIZE)
  {
    /* Set Buffer swap indication */
    uwBufferReadyIndication = 1;

    /* Swap buffers for next bytes to be received */
    ptemp = pBufferReadyForUser;
    pBufferReadyForUser = pBufferReadyForReception;
    pBufferReadyForReception = ptemp;
    uwNbReceivedChars = 0;
  }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  __IO uint32_t isr_reg;

  /* Disable USARTx_IRQn */
  NVIC_DisableIRQ(USART2_IRQn);

  /* Error handling example :
	- Read USART ISR register to identify flag that leads to IT raising
	- Perform corresponding error handling treatment according to flag
  */
  isr_reg = LL_USART_ReadReg(USART2, ISR);
  if (isr_reg & LL_USART_ISR_NE)
  {
	/* case Noise Error flag is raised : Clear NF Flag */
	LL_USART_ClearFlag_NE(USART2);
  }
  else
  {

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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
