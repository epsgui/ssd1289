/*
    ChibiOS/RT - Copyright (C) 2006-2013 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for the HY-STM32 proto board.
 */

/*
 * Board identifier.
 */
#define BOARD_HY_STM32
#define BOARD_NAME              "HY-STM32"

/*
 * Board frequencies.
 */
#define STM32_LSECLK            32768
#define STM32_HSECLK            8000000

/*
 * MCU type, supported types are defined in ./os/hal/platforms/hal_lld.h.
 */
#define STM32F103xE
#define STM32F10X_HD

/*
 * IO pins assignments.
 */
#define GPIOA_SPI1NSS           4
#define GPIOB_SPI2NSS           12
#define GPIOA_SPI3NSS           15

//#define GPIOA_USB_P             0
#define GPIOC_USB_DISC          13

#define GPIOE_TFT_RST		1

#define GPIOE_BTN1		5
#define GPIOE_BTN1_MASK		(1 << GPIOE_BTN1)
#define GPIOE_BTN2		4
#define GPIOE_BTN2_MASK		(1 << GPIOE_BTN2)
#define GPIOE_BTN3		3
#define GPIOE_BTN3_MASK		(1 << GPIOE_BTN3)
#define GPIOE_BTN4		2
#define GPIOE_BTN4_MASK		(1 << GPIOE_BTN4)

#define GPIOC_LED1		6
#define GPIOC_LED2		7
#define GPIOD_LED3		13
#define GPIOD_LED4		6

#define GPIOE_BUZZER		0

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 *
 * The digits have the following meaning:
 *   0 - Analog input.
 *   1 - Push Pull output 10MHz.
 *   2 - Push Pull output 2MHz.
 *   3 - Push Pull output 50MHz.
 *   4 - Digital input.
 *   5 - Open Drain output 10MHz.
 *   6 - Open Drain output 2MHz.
 *   7 - Open Drain output 50MHz.
 *   8 - Digital input with PullUp or PullDown resistor depending on ODR.
 *   9 - Alternate Push Pull output 10MHz.
 *   A - Alternate Push Pull output 2MHz.
 *   B - Alternate Push Pull output 50MHz.
 *   C - Reserved.
 *   D - Alternate Open Drain output 10MHz.
 *   E - Alternate Open Drain output 2MHz.
 *   F - Alternate Open Drain output 50MHz.
 * Please refer to the STM32 Reference Manual for details.
 */

/*
 * Port A setup.
 * Everything input with pull-up except:
 * PA0  - GIOP J1.5
 * PA1  - GIOP J1.6
 * PA2  - Alternate output  (USART2 TX MAX3232). / GIOP J1.36
 * PA3  - Normal input      (USART2 RX MAX3232). / GIOP J1.35
 * PA4  - CS M25P16.1 / GIOP J1.3
 * PA5  - TP_DCLK (TFT.40) / SD_SCK (TFT.22) / C M25P16.6
 * PA6  - TP_DOUT (TFT.36) / SD_MISO (TFT.21) / Q M25P16.2
 * PA7  - TP_DIN (TFT.38) / SD_MOSI (TFT.23) / D M25P15.5
 * PA8  - Alternate PP 50M  (PWM1 CON3.4 TIM1_CH1)
 * PA9  - Alternate output  (USART1 TX PL2303). / GIOP J1.32
 * PA10 - Normal input      (USART1 RX PL2303). / GIOP J1.31
 * PA11 - Normal input      (USB DM). / GIOP J1.33
 * PA12 - Normal input      (USB DP). / GIOP J1.34
 * PA13 - SWDIO / JTAG_TMS.7
 * PA14 - SWCLK / JTAG_TCK.9
 * PA15 - JTAG_TDI.5
 */
#define VAL_GPIOACRL            0x88884B88      /*  PA7...PA0 */
#define VAL_GPIOACRH            0x888444BB      /* PA15...PA8 */
#define VAL_GPIOAODR            0xFFFFFFFF

/*
 * Port B setup.
 * Everything input with pull-up except:
 * PB0  - GPIO J1.13
 * PB1  - GPIO J1.16
 * PB2  - GPIO J1.15 / BOOT1
 * PB3  - JTAG_TDO.13
 * PB4  - JTAG_nRTST.3
 * PB5  - GPIO J1.18
 * PB6  - TP_IRQ (TFT.35)
 * PB7  - PP output 50M    TP_CS (TFT.39)
 * PB8  - CAN_RX CON3.1
 * PB9  - CAN_TX CON3.2
 * PB10 - TFT.16
 * PB11 - TFT.18
 * PB12 - GPIO J1.24
 * PB13 - GPIO J1.23
 * PB14 - GPIO J1.26
 * PB15 - GPIO J1.55
 */
#define VAL_GPIOBCRL            0x38888888      /*  PB7...PB0 */
#define VAL_GPIOBCRH            0x88888888      /* PB15...PB8 */
#define VAL_GPIOBODR            0xFFFFFFFF

/*
 * Port C setup.
 * Everything input with pull-up except:
 * PC0  - Analog Input CON3.6 (ADC_IN10).
 * PC1  - Analog Input CON3.5 (ADC_IN11).
 * PC2  - GPIO J1.7        (ADC_IN12).
 * PC3  - GPIO J1.8        (ADC_IN13).
 * PC4  - TFT.25           (ADC_IN14).
 * PC5  - TFT.26           (ADC_IN15).
 * PC6  - LED1 / TP_BUSY (TFT.37)
 * PC7  - LED2 / GPIO J1.27
 * PC8  - Alternate PP 50M (SD_D0 / GPIO J1.30).
 * PC9  - Alternate PP 50M (SD_D1 / GPIO J1.29).
 * PC10 - Alternate PP 50M (SD_D2 / GPIO J1.21).
 * PC11 - Alternate PP 50M (SD_D3 / GPIO J1.22).
 * PC12 - Alternate PP 50M (SD_CLK / GPIO J1.19).
 * PC13 - PP output 50M    (USB Pull-UP / TFT.3)
 * PC14 - Normal input	   (XTAL).
 * PC15 - Normal input	   (XTAL).
 */
#define VAL_GPIOCCRL            0x88880000      /*  PC7...PC0 */
#define VAL_GPIOCCRH            0x443BBBBB      /* PC15...PC8 */
#define VAL_GPIOCODR            0xFFFFFFFF

/*
 * Port D setup.
 * Everything input with pull-up except:
 * PD0  - Alternate PP 50M (FSMC_DB2)
 * PD1  - Alternate PP 50M (FSMC_DB3)
 * PD2  - Alternate PP 50M (SDIO_CMD / GPIO J1.20)
 * PD3  - GPIO             (J1.17)
 * PD4  - Alternate PP 50M (TFT_RD)
 * PD5  - Alternate PP 50M (TFT_WR)
 * PD6  - PP output 50M    (SD_CS1, LED4)
 * PD7  - Alternate PP 50M (TFT_CS)
 * PD8  - Alternate PP 50M (FSMC_DB13)
 * PD9  - Alternate PP 50M (FSMC_DB14)
 * PD10 - Alternate PP 50M (FSMC_DB15)
 * PD11 - Alternate PP 50M (TFT_RS - Data/Command)
 * PD12 - Alternate PP 50M (PWM2 CON3.3 TIM4_CH1)
 * PD13 - PP output 50M    (LED3)
 * PD14 - Alternate PP 50M (FSMC_DB0)
 * PD15 - Alternate PP 50M (FSMC_DB1)
 */
#define VAL_GPIODCRL            0xB3BB8BBB      /*  PD7...PD0 */
#define VAL_GPIODCRH            0xBB3BBBBB      /* PD15...PD8 */
#define VAL_GPIODODR            0xFFFFFFFF

/*
 * Port E setup.
 * Everything input with pull-up except:
 * PE0  - Digital Output   (BUZZER J2 / GPIO J1.4)
 * PE1  - Digital Output   (TFT_RESET)
 * PE2  - Digital input    (KEY_S4 / GPIO J1.14)
 * PE3  - Digital input    (KEY_S3 / GPIO J1.11)
 * PE4  - Digital input    (KEY_S2 / GPIO J1.12)
 * PE5  - Digital input    (KEY_S1 / GPIO J1.9)
 * PE6  - GPIO             (J1.10)
 * PE7  - Alternate PP 50M (FSMC_DB4)
 * PE8  - Alternate PP 50M (FSMC_DB5)
 * PE9  - Alternate PP 50M (FSMC_DB6)
 * PE10 - Alternate PP 50M (FSMC_DB7)
 * PE11 - Alternate PP 50M (FSMC_DB8)
 * PE12 - Alternate PP 50M (FSMC_DB9)
 * PE13 - Alternate PP 50M (FSMC_DB10)
 * PE14 - Alternate PP 50M (FSMC_DB11)
 * PE15 - Alternate PP 50M (FSMC_DB12)
 */
#define VAL_GPIOECRL            0xB8444433      /*  PE7...PE0 */
#define VAL_GPIOECRH            0xBBBBBBBB      /* PE15...PE8 */
#define VAL_GPIOEODR            0xFFFFFFFF

/*
 * Port F setup.
 * Everything input with pull-up expect:
 */
#define VAL_GPIOFCRL            0x88888888      /*  PF7...PF0 */
#define VAL_GPIOFCRH            0x88888888      /* PF15...PF8 */
#define VAL_GPIOFODR            0xFFFFFFFF

/*
 * Port G setup.
 * Everything input with pull-up expect:
 */
#define VAL_GPIOGCRL            0x88888888      /*  PG7...PG0 */
#define VAL_GPIOGCRH            0x88888888      /* PG15...PG8 */
#define VAL_GPIOGODR            0xFFFFFFFF

/*
 * USB bus activation macro, required by the USB driver.
 */
#define usb_lld_connect_bus(usbp) palClearPad(GPIOC, GPIOC_USB_DISC)

/*
 * USB bus de-activation macro, required by the USB driver.
 */
#define usb_lld_disconnect_bus(usbp) palSetPad(GPIOC, GPIOC_USB_DISC)

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
