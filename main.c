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

#include "ch.h"
#include "hal.h"
#include "gfx.h"
#include "board_SSD1289.h"
#include "ginput_lld_toggle_board.h"

/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  /*
   * This initialization requires the OS already active because it uses delay
   * APIs inside.
   *
   * Initialize uGFX and the underlying system
   */
  gfxInit();

  // Initialize LED3 and LED4 pins
  palSetPadMode(GPIOD, GPIOD_LED3, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOD, GPIOD_LED4, PAL_MODE_OUTPUT_PUSHPULL);
  // and take it OFF
  palClearPad(GPIOD, GPIOD_LED3);
  palClearPad(GPIOD, GPIOD_LED4);

  /*
   * Activates the serial driver 1 using the driver default configuration.
   */
  sdStart(&SD1, NULL);

  /*
   * Code here
   */

  /*
   * simple graphics demo
   */

  coord_t i, j;
  // Get the screen size
  coord_t width = gdispGetWidth();
  coord_t height = gdispGetHeight();

  gdispDrawBox(0, 0, width-1, height-1, Green);
  gdispDrawBox(10, 10, width/2, height/2, Yellow);
  gdispFillArea(width/2, height/2, width/2-10, height/2-10, Blue);
  gdispDrawLine(5, 5, width-6, height-6, Red);

  for(i = 5, j = 0; i < width && j < height; i += 7, j += i/20){
    gdispDrawPixel(i, j, Green);
  }

  font_t font = gdispOpenFont("DejaVuSans24");

  gdispDrawString(16, 16, "STM32F103V + SSD1289", font, White);
  gdispDrawString(16, 64, "GDISP_ROTATE_DEFAULT", font, Red);

  gdispDrawStringBox(0, (height/2)-20, width, 40, "ChibiOS/RT + uGFX", font, White, justifyCenter);

  sdPut(&SD1, '\n');

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state.
   */
  while (TRUE) {
    if (palReadPad(GPIOE, GPIOE_BTN1)){
        sdPut(&SD1, 'A');
    }
    chThdSleepMilliseconds(500);
  }
}
