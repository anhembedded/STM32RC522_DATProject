/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "main.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include "MFRC522.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

uint8_t value = 0;
char str1[17] = {'\0'};
char str2[17] = {'\0'};
char str3[17] = {'\0'};
char str4[17] = {'\0'};
char tmp_str[65] = {'\0'};
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI2_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  for (int i = 0; i < 16; i++)
  {
    tmp_str[i] = 'A';
  }
  for (int i = 16; i < 32; i++)
  {
    tmp_str[i] = 'B';
  }
  for (int i = 32; i < 48; i++)
  {
    tmp_str[i] = 'C';
  }
  for (int i = 48; i < 64; i++)
  {
    tmp_str[i] = 'D';
  }
  HAL_GPIO_WritePin(RC522_Rst_GPIO_Port, RC522_Rst_Pin, GPIO_PIN_SET);
  HAL_Delay(100);
  MFRC522_Init();
  HAL_Delay(1000);
  u_char status, cardstr[MAX_LEN + 1];
  u_char card_data[17];
  uint32_t delay_val = 1000; // ms
  uint16_t result = 0;
  u_char UID[5];
  // a private key to scramble data writing/reading to/from RFID card:
  u_char Mx1[7][5] = {{0x12, 0x45, 0xF2, 0xA8}, {0xB2, 0x6C, 0x39, 0x83}, {0x55, 0xE5, 0xDA, 0x18}, {0x1F, 0x09, 0xCA, 0x75}, {0x99, 0xA2, 0x50, 0xEC}, {0x2C, 0x88, 0x7F, 0x3D}};
  u_char SectorKey[7];
  status = Read_MFRC522(VersionReg);
  sprintf(str1,"Running RC522");
  sprintf(str2,"ver:%x", status);
  HAL_Delay(1000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    for (int i = 0; i < 16; i++)
    {
      cardstr[i] = 0;
    }
    status = 0;
    // Find cards
    status = MFRC522_Request(PICC_REQIDL, cardstr);
    if (status == MI_OK)
    {

      result = 0;
      result++;
      sprintf(str1, "Card:%x,%x,%x", cardstr[0], cardstr[1], cardstr[2]);
      //
      // Anti-collision, return card serial number == 4 bytes
      HAL_Delay(1);
      status = MFRC522_Anticoll(cardstr);
      if (status == MI_OK)
      {
        result++;
        sprintf(str2, "UID:%x %x %x %x", cardstr[0], cardstr[1], cardstr[2], cardstr[3]);
        UID[0] = cardstr[0];
        UID[1] = cardstr[1];
        UID[2] = cardstr[2];
        UID[3] = cardstr[3];
        UID[4] = cardstr[4];
        //
        HAL_Delay(1);
        status = MFRC522_SelectTag(cardstr);
        if (status > 0)
        {
          result++;
          //
          SectorKey[0] = ((Mx1[0][0]) ^ (UID[0])) + ((Mx1[0][1]) ^ (UID[1])) + ((Mx1[0][2]) ^ (UID[2])) + ((Mx1[0][3]) ^ (UID[3])); // 0x11; //KeyA[0]
          SectorKey[1] = ((Mx1[1][0]) ^ (UID[0])) + ((Mx1[1][1]) ^ (UID[1])) + ((Mx1[1][2]) ^ (UID[2])) + ((Mx1[1][3]) ^ (UID[3])); // 0x11; //KeyA[0]
          SectorKey[2] = ((Mx1[2][0]) ^ (UID[0])) + ((Mx1[2][1]) ^ (UID[1])) + ((Mx1[2][2]) ^ (UID[2])) + ((Mx1[2][3]) ^ (UID[3])); // 0x11; //KeyA[0]
          SectorKey[3] = ((Mx1[3][0]) ^ (UID[0])) + ((Mx1[3][1]) ^ (UID[1])) + ((Mx1[3][2]) ^ (UID[2])) + ((Mx1[3][3]) ^ (UID[3])); // 0x11; //KeyA[0]
          SectorKey[4] = ((Mx1[4][0]) ^ (UID[0])) + ((Mx1[4][1]) ^ (UID[1])) + ((Mx1[4][2]) ^ (UID[2])) + ((Mx1[4][3]) ^ (UID[3])); // 0x11; //KeyA[0]
          SectorKey[5] = ((Mx1[5][0]) ^ (UID[0])) + ((Mx1[5][1]) ^ (UID[1])) + ((Mx1[5][2]) ^ (UID[2])) + ((Mx1[5][3]) ^ (UID[3])); // 0x11; //KeyA[0]
          HAL_Delay(1);
          status = MFRC522_Auth(0x60, 3, SectorKey, cardstr);
          if (status == MI_OK)
          {
            result++;
            sprintf(str3, "Auth. OK");
            if (1)
            {
              // Clean-Up the Card:
              card_data[0] = 0xFF;
              card_data[1] = 0xFF;
              card_data[2] = 0xFF;
              card_data[3] = 0xFF;
              card_data[4] = 0xFF;
              card_data[5] = 0xFF;
              card_data[6] = 0xFF;  // Access_bits[6]
              card_data[7] = 0x07;  // Access_bits[7]
              card_data[8] = 0x80;  // Access_bits[8]
              card_data[9] = 0x88;  // user_byte[9]
              card_data[10] = 0x88; // user_byte[10]
              card_data[11] = 0x88; // user_byte[11]
              card_data[12] = 0x88; // user_byte[12]
              card_data[13] = 0x88; // user_byte[13]
              card_data[14] = 0x88; // user_byte[14]
              card_data[15] = 0x88; // user_byte[15]
              HAL_Delay(1);
              status = MFRC522_Write(3, card_data);
              if (status == MI_OK)
              {
                result++;
                sprintf(str3, "                ");
                sprintf(str4, "Card Cleared!");
                delay_val = 2000;
              }
            }
          }
          else
          {
            for (int i = 0; i < 16; i++)
            {
              cardstr[i] = 0;
            }
            status = 0;
            // Find cards
            HAL_Delay(1);
            status = MFRC522_Request(PICC_REQIDL, cardstr);
            HAL_Delay(1);
            status = MFRC522_Anticoll(cardstr);
            HAL_Delay(1);
            status = MFRC522_SelectTag(cardstr);
            SectorKey[0] = 0xFF;
            SectorKey[1] = 0xFF;
            SectorKey[2] = 0xFF;
            SectorKey[3] = 0xFF;
            SectorKey[4] = 0xFF;
            SectorKey[5] = 0xFF;
            HAL_Delay(1);
            status = MFRC522_Auth(0x60, 3, SectorKey, cardstr);
            if (status == MI_OK)
            {
              if (1)
              {
                card_data[0] = ((Mx1[0][0]) ^ (UID[0])) + ((Mx1[0][1]) ^ (UID[1])) + ((Mx1[0][2]) ^ (UID[2])) + ((Mx1[0][3]) ^ (UID[3])); // 0x11; //KeyA[0]
                card_data[1] = ((Mx1[1][0]) ^ (UID[0])) + ((Mx1[1][1]) ^ (UID[1])) + ((Mx1[1][2]) ^ (UID[2])) + ((Mx1[1][3]) ^ (UID[3])); // 0x11; //KeyA[0]
                card_data[2] = ((Mx1[2][0]) ^ (UID[0])) + ((Mx1[2][1]) ^ (UID[1])) + ((Mx1[2][2]) ^ (UID[2])) + ((Mx1[2][3]) ^ (UID[3])); // 0x11; //KeyA[0]
                card_data[3] = ((Mx1[3][0]) ^ (UID[0])) + ((Mx1[3][1]) ^ (UID[1])) + ((Mx1[3][2]) ^ (UID[2])) + ((Mx1[3][3]) ^ (UID[3])); // 0x11; //KeyA[0]
                card_data[4] = ((Mx1[4][0]) ^ (UID[0])) + ((Mx1[4][1]) ^ (UID[1])) + ((Mx1[4][2]) ^ (UID[2])) + ((Mx1[4][3]) ^ (UID[3])); // 0x11; //KeyA[0]
                card_data[5] = ((Mx1[5][0]) ^ (UID[0])) + ((Mx1[5][1]) ^ (UID[1])) + ((Mx1[5][2]) ^ (UID[2])) + ((Mx1[5][3]) ^ (UID[3])); // 0x11; //KeyA[0]
                card_data[6] = 0xFF;                                                                                                      // Access_bits[6]
                card_data[7] = 0x07;                                                                                                      // Access_bits[7]
                card_data[8] = 0x80;                                                                                                      // Access_bits[8]
                card_data[9] = 0x88;                                                                                                      // user_byte[9]
                card_data[10] = 0x88;                                                                                                     // user_byte[10]
                card_data[11] = 0x88;                                                                                                     // user_byte[11]
                card_data[12] = 0x88;                                                                                                     // user_byte[12]
                card_data[13] = 0x88;                                                                                                     // user_byte[13]
                card_data[14] = 0x88;                                                                                                     // user_byte[14]
                card_data[15] = 0x88;                                                                                                     // user_byte[15]
                HAL_Delay(1);
                status = MFRC522_Write(3, card_data);
                if (status == MI_OK)
                {
                  result++;
                  sprintf(str3, "Card Set!");
                  delay_val = 2000;
                }
              }
              else
              {

                sprintf(str4, "New Card!");
              }
            }
            else if (status != MI_OK)
            {
              sprintf(str3, "Auth. Error");
            }
          }
          HAL_Delay(1);
          MFRC522_StopCrypto1();
        }
      }
      HAL_Delay(1);
      MFRC522_Halt();


      HAL_Delay(delay_val);
      delay_val = 1000;
      sprintf(str1, "                ");
      sprintf(str2, "                ");
      sprintf(str3, "                ");
      sprintf(str4, "                ");
    }
    else
    {
      sprintf(str1, "Waiting for Card");

      sprintf(str2, "                ");

      sprintf(str3, "                ");

      sprintf(str4, "                ");

    }
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
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
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
