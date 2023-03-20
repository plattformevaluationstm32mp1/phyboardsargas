/**
  @page UART_TwoBoards_ComIT UART Two Boards Communication IT example

  @verbatim
  ******************** (C) COPYRIGHT 2019 STMicroelectronics *******************
  * @file    UART/UART_Receive_Transmit_Console/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the UART Receive and Transmit on Console example.
  ******************************************************************************
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics. 
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the 
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  @endverbatim

@par Example Description 

UART transmission (printf/getchar) via console with user interaction.
The UART outputs a message on the HyperTerminal and receives some characters.

Board: STM32MP15x-phyBOARD-Sargas (embeds a STM32MP157CACx device)
Tx Pin: PB10 (CN2, pin 8)
Rx Pin: PB12 (CN2, pin 10)
   _________________________
  |           ______________|                      ________________
  |          |USART3        |                     | Hyperterminal  |
  |          |              |                     |                |
  |          |           TX |_____________________| TXD            |
  |          |              |                     |                |
  |          |              |      UART/USB       |                |
  |          |              |      FTDI link      |                |
  |          |           RX |_____________________| RXD            |
  |          |              |                     |                |
  |          |______________|                     |                |
  |                     3V3 |                     |                |
  |                         |                     |                |
  |                     GND |                     |                |
  |_STM32_Board ____________|                     |_________HOST PC|


The USART is configured as follows:
    - BaudRate = 115200 baud
    - Word Length = 8 Bits (7 data bit + 1 parity bit)
    - One Stop Bit
    - Odd parity
    - Hardware flow control disabled (RTS and CTS signals: not usefull for this example) 
    - Reception and transmission are enabled in the time

The user sees some printf messages on the Hyperterminal console.
He has to type "c" to continue with getchar test.
A menu is displayed, and the user can select:
- "Test1" to execute fast LED1 (green LED on SOM) blink (during 5s)
- "Test2" to execute slow LED1 blink (during 5s)
- "Test3" to quit the example

STM32MP15x-phyBOARD-Sargas board LED is used to monitor:
- LED1 is blinking fastly or slowly during Test1 and Test2.
- LED1 is on at the end of the test (if user selects "Test3")
- If there is an error, LED1 is blinking (2 sec. period).

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the systick.
Then the System clock source is configured by the SystemClock_Config() function in case of Engineering Mode, this clock configuration is done
by the Firmware running on the Cortex-A7 in case of Production Mode.

@note When the parity is enabled, the computed parity is inserted at the MSB
position of the transmitted data.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - UART/UART_Receive_Transmit_Console/Inc/stm32mp1xx_hal_conf.h    HAL configuration file
  - UART/UART_Receive_Transmit_Console/Inc/stm32mp1xx_it.h          IT interrupt handlers header file
  - UART/UART_Receive_Transmit_Console/Inc/main.h                   Header for main.c module  
  - UART/UART_Receive_Transmit_Console/Src/stm32mp1xx_it.c          IT interrupt handlers
  - UART/UART_Receive_Transmit_Console/Src/main.c                   Main program
  - UART/UART_Receive_Transmit_Console/Src/stm32mp1xx_hal_msp.c     HAL MSP module
  - UART/UART_Receive_Transmit_Console/Src/system_stm32mp1xx.c      STM32MP1xx system source file


@par Hardware and Software environment 

  - This example runs on STM32MP157CACx devices.    
  - This example has been tested with a phyBOARD-Sargas board embedding
    a STM32MP157CACx device and can be easily tailored to any other supported device 
    and development board.

  - STM32MP15x-phyBOARD-Sargas set-up
    - Jumper JP16 removed
    - USART3 console connected to HOST PC throught USB OTG cable on X13
    (USART3 is the 2nd serial console accessible on Linux HOST PC over /dev/ttyUSB1)

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
