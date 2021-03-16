/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins
     PE2   ------> SAI1_MCLK_A
     PE4   ------> SAI1_FS_A
     PE5   ------> SAI1_SCK_A
     PE6   ------> SAI1_SD_A
     PC3   ------> LCD_VLCD
     PA6   ------> LCD_SEG3
     PA7   ------> LCD_SEG4
     PC4   ------> LCD_SEG22
     PC5   ------> LCD_SEG23
     PB0   ------> LCD_SEG5
     PB1   ------> LCD_SEG6
     PE7   ------> SAI1_SD_B
     PE9   ------> SAI1_FS_B
     PE10   ------> QUADSPI_CLK
     PE11   ------> QUADSPI_NCS
     PE12   ------> QUADSPI_BK1_IO0
     PE13   ------> QUADSPI_BK1_IO1
     PE14   ------> QUADSPI_BK1_IO2
     PE15   ------> QUADSPI_BK1_IO3
     PB10   ------> I2C2_SCL
     PB11   ------> I2C2_SDA
     PB12   ------> LCD_SEG12
     PB13   ------> LCD_SEG13
     PB14   ------> LCD_SEG14
     PB15   ------> LCD_SEG15
     PD8   ------> LCD_SEG28
     PD9   ------> LCD_SEG29
     PD10   ------> LCD_SEG30
     PD11   ------> LCD_SEG31
     PD12   ------> LCD_SEG32
     PD13   ------> LCD_SEG33
     PD14   ------> LCD_SEG34
     PD15   ------> LCD_SEG35
     PC6   ------> LCD_SEG24
     PC7   ------> LCD_SEG25
     PC8   ------> LCD_SEG26
     PA8   ------> LCD_COM0
     PA9   ------> LCD_COM1
     PA10   ------> LCD_COM2
     PA11   ------> USB_OTG_FS_DM
     PA12   ------> USB_OTG_FS_DP
     PA15 (JTDI)   ------> LCD_SEG17
     PD1   ------> SPI2_SCK
     PD3   ------> SPI2_MISO
     PD4   ------> SPI2_MOSI
     PB4 (NJTRST)   ------> LCD_SEG8
     PB5   ------> LCD_SEG9
     PB6   ------> I2C1_SCL
     PB7   ------> I2C1_SDA
     PB9   ------> LCD_COM3
*/
void MX_GPIO_Init(void)
{

  LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOE);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOH);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOD);

  /**/
  LL_GPIO_ResetOutputPin(GPIOE, AUDIO_RST_Pin|LD_G_Pin|XL_CS_Pin);

  /**/
  LL_GPIO_ResetOutputPin(GPIOB, LD_R_Pin|M3V3_REG_ON_Pin);

  /**/
  LL_GPIO_ResetOutputPin(OTG_FS_VBUS_GPIO_Port, OTG_FS_VBUS_Pin);

  /**/
  LL_GPIO_ResetOutputPin(GYRO_CS_GPIO_Port, GYRO_CS_Pin);

  /**/
  LL_GPIO_SetOutputPin(OTG_FS_PowerSwitchOn_GPIO_Port, OTG_FS_PowerSwitchOn_Pin);

  /**/
  GPIO_InitStruct.Pin = SAI1_MCK_Pin|SAI1_FS_Pin|SAI1_SCK_Pin|SAI1_SD_Pin
                          |AUDIO_DIN_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_13;
  LL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = AUDIO_RST_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(AUDIO_RST_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_0|MAG_INT_Pin|MAG_DRDY_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = VLCD_Pin|SEG22_Pin|SEG1_Pin|SEG14_Pin
                          |SEG9_Pin|SEG13_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_11;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = JOY_CENTER_Pin|JOY_LEFT_Pin|JOY_RIGHT_Pin|JOY_UP_Pin
                          |JOY_DOWN_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = SEG23_Pin|SEG0_Pin|COM0_Pin|COM1_Pin
                          |COM2_Pin|SEG10_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_11;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = SEG21_Pin|SEG2_Pin|SEG20_Pin|SEG3_Pin
                          |SEG19_Pin|SEG4_Pin|SEG11_Pin|SEG12_Pin
                          |COM3_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_11;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LD_R_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(LD_R_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LD_G_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(LD_G_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = AUDIO_CLK_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_13;
  LL_GPIO_Init(AUDIO_CLK_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = QSPI_CLK_Pin|QSPI_CS_Pin|QSPI_D0_Pin|QSPI_D1_Pin
                          |QSPI_D2_Pin|QSPI_D3_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_10;
  LL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = MFX_I2C_SLC_Pin|MFX_I2C_SDA_Pin|I2C1_SCL_Pin|I2C1_SDA_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = SEG18_Pin|SEG5_Pin|SEG17_Pin|SEG6_Pin
                          |SEG16_Pin|SEG7_Pin|SEG15_Pin|SEG8_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_11;
  LL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = OTG_FS_PowerSwitchOn_Pin|OTG_FS_VBUS_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = OTG_FS_DM_Pin|OTG_FS_DP_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_10;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = MEMS_SCK_Pin|MEMS_MISO_Pin|MEMS_MOSI_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_5;
  LL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = GYRO_CS_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GYRO_CS_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = M3V3_REG_ON_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(M3V3_REG_ON_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = XL_CS_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(XL_CS_GPIO_Port, &GPIO_InitStruct);

  /**/
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE13);

  /**/
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA, LL_SYSCFG_EXTI_LINE4);

  /**/
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE10);

  /**/
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTD, LL_SYSCFG_EXTI_LINE0);

  /**/
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTD, LL_SYSCFG_EXTI_LINE2);

  /**/
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE8);

  /**/
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTE, LL_SYSCFG_EXTI_LINE1);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_13;
  EXTI_InitStruct.Line_32_63 = LL_EXTI_LINE_NONE;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_EVENT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_4;
  EXTI_InitStruct.Line_32_63 = LL_EXTI_LINE_NONE;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_EVENT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_10;
  EXTI_InitStruct.Line_32_63 = LL_EXTI_LINE_NONE;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_EVENT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_0;
  EXTI_InitStruct.Line_32_63 = LL_EXTI_LINE_NONE;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_EVENT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_2;
  EXTI_InitStruct.Line_32_63 = LL_EXTI_LINE_NONE;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_EVENT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_8;
  EXTI_InitStruct.Line_32_63 = LL_EXTI_LINE_NONE;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_EVENT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_1;
  EXTI_InitStruct.Line_32_63 = LL_EXTI_LINE_NONE;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_EVENT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  LL_GPIO_SetPinPull(MFX_IRQ_OUT_GPIO_Port, MFX_IRQ_OUT_Pin, LL_GPIO_PULL_NO);

  /**/
  LL_GPIO_SetPinPull(MFX_WAKEUP_GPIO_Port, MFX_WAKEUP_Pin, LL_GPIO_PULL_NO);

  /**/
  LL_GPIO_SetPinPull(OTG_FS_OverCurrent_GPIO_Port, OTG_FS_OverCurrent_Pin, LL_GPIO_PULL_NO);

  /**/
  LL_GPIO_SetPinPull(EXT_RST_GPIO_Port, EXT_RST_Pin, LL_GPIO_PULL_NO);

  /**/
  LL_GPIO_SetPinPull(GYRO_INT1_GPIO_Port, GYRO_INT1_Pin, LL_GPIO_PULL_NO);

  /**/
  LL_GPIO_SetPinPull(GYRO_INT2_GPIO_Port, GYRO_INT2_Pin, LL_GPIO_PULL_NO);

  /**/
  LL_GPIO_SetPinPull(XL_INT_GPIO_Port, XL_INT_Pin, LL_GPIO_PULL_NO);

  /**/
  LL_GPIO_SetPinMode(MFX_IRQ_OUT_GPIO_Port, MFX_IRQ_OUT_Pin, LL_GPIO_MODE_INPUT);

  /**/
  LL_GPIO_SetPinMode(MFX_WAKEUP_GPIO_Port, MFX_WAKEUP_Pin, LL_GPIO_MODE_INPUT);

  /**/
  LL_GPIO_SetPinMode(OTG_FS_OverCurrent_GPIO_Port, OTG_FS_OverCurrent_Pin, LL_GPIO_MODE_INPUT);

  /**/
  LL_GPIO_SetPinMode(EXT_RST_GPIO_Port, EXT_RST_Pin, LL_GPIO_MODE_INPUT);

  /**/
  LL_GPIO_SetPinMode(GYRO_INT1_GPIO_Port, GYRO_INT1_Pin, LL_GPIO_MODE_INPUT);

  /**/
  LL_GPIO_SetPinMode(GYRO_INT2_GPIO_Port, GYRO_INT2_Pin, LL_GPIO_MODE_INPUT);

  /**/
  LL_GPIO_SetPinMode(XL_INT_GPIO_Port, XL_INT_Pin, LL_GPIO_MODE_INPUT);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
