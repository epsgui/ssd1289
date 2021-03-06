/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#include "gfx.h"

#if GFX_USE_GDISP

#if defined(GDISP_SCREEN_HEIGHT)
  #warning "GDISP: This low level driver does not support setting a screen size. It is being ignored."
  #undef GISP_SCREEN_HEIGHT
#endif
#if defined(GDISP_SCREEN_WIDTH)
  #warning "GDISP: This low level driver does not support setting a screen size. It is being ignored."
  #undef GDISP_SCREEN_WIDTH
#endif

#define GDISP_DRIVER_VMT      GDISPVMT_ILI9481
#include "gdisp_lld_config.h"
//#include "../../../src/gdisp/gdisp_driver.h"
#include "src/gdisp/gdisp_driver.h"

#include "board_ILI9481.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

#ifndef GDISP_SCREEN_HEIGHT
  #define GDISP_SCREEN_HEIGHT    480
#endif
#ifndef GDISP_SCREEN_WIDTH
  #define GDISP_SCREEN_WIDTH    320
#endif
#ifndef GDISP_INITIAL_CONTRAST
  #define GDISP_INITIAL_CONTRAST  50
#endif
#ifndef GDISP_INITIAL_BACKLIGHT
  #define GDISP_INITIAL_BACKLIGHT  100
#endif

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

// Some common routines and macros
#define dummy_read(g)  { volatile uint16_t dummy; dummy = read_data(g); (void) dummy; }
#define write_reg(g, reg, data)  { write_index(g, reg); write_data(g, data); }
#define write_reg2x16(g, reg, data1, data2)  { write_index(g, reg); write_data(g, (data1)>>8); write_data(g, (uint8_t)(data1)); write_data(g, (data2)>>8); write_data(g, (uint8_t)(data2));}

static void set_viewport(GDisplay* g) {
  write_reg2x16(g, 0x2A, g->p.x, g->p.x + g->p.cx - 1);
  write_reg2x16(g, 0x2B, g->p.y, g->p.y + g->p.cy - 1);
  write_index(g, 0x2C);
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

LLDSPEC bool_t gdisp_lld_init(GDisplay *g) {
  /* No private area for this controller */
  g->priv = 0;

  /* Initialise the board interface */
  init_board(g);

  /* Hardware reset */
  setpin_reset(g, TRUE);
  gfxSleepMilliseconds(20);
  setpin_reset(g, FALSE);
  gfxSleepMilliseconds(20);

  /* Get the bus for the following initialisation commands */
  acquire_bus(g);

  /* Exit_sleep_mode */
  write_index(g, 0x11);
  gfxSleepMilliseconds(20);

  /* Power_Setting */
  write_index(g, 0xD0);
  write_data(g, 0x07);
  write_data(g, 0x42);
  write_data(g, 0x18);

  /* VCOM Control  */  
  write_index(g, 0xD1);
  write_data(g, 0x00);
  write_data(g, 0x07);
  write_data(g, 0x10);
  
  /* Power_Setting for Normal Mode */
  write_index(g, 0xD2);
  write_data(g, 0x01);
  write_data(g, 0x02);

  /* Panel Driving Setting */  
  write_index(g, 0xC0);
  write_data(g, 0x10);
  write_data(g, 0x3B);
  write_data(g, 0x00);
  write_data(g, 0x02);
  write_data(g, 0x11);
  
  /* Frame Rate and Inversion Control */
  write_index(g, 0xC5);
  write_data(g, 0x03);

  /* Gamma Setting */  
  write_index(g, 0xC8);
  write_data(g, 0x00);
  write_data(g, 0x32);
  write_data(g, 0x36);
  write_data(g, 0x45);
  write_data(g, 0x06);
  write_data(g, 0x16);
  write_data(g, 0x37);
  write_data(g, 0x75);
  write_data(g, 0x77);
  write_data(g, 0x54);
  write_data(g, 0x0C);
  write_data(g, 0x00);
  
  /* Set_address_mode */
  write_index(g, 0x36);
  write_data(g, 0x0A); /* BGR Order. Horizontal Flip. */
  
  /* Set_pixel_format */
  write_index(g, 0x3A);
  write_data(g, 0x55);

  /* Set_column_address */
  write_index(g, 0x2A);
  write_data(g, 0x00);
  write_data(g, 0x00);
  write_data(g, 0x01);
  write_data(g, 0x3F);

  /* Set_page_address */  
  write_index(g, 0x2B);
  write_data(g, 0x00);
  write_data(g, 0x00);
  write_data(g, 0x01);
  write_data(g, 0xE0);
  gfxSleepMilliseconds(120);

  /* Set_display_on */
  write_index(g, 0x29);

  /* Finish Init */
  post_init_board(g);

  /* Release the bus */
  release_bus(g);
  
  /* Turn on the back-light */
  set_backlight(g, GDISP_INITIAL_BACKLIGHT);

  /* Initialise the GDISP structure */
  g->g.Width = GDISP_SCREEN_WIDTH;
  g->g.Height = GDISP_SCREEN_HEIGHT;
  g->g.Orientation = GDISP_ROTATE_0;
  g->g.Powermode = powerOn;
  g->g.Backlight = GDISP_INITIAL_BACKLIGHT;
  g->g.Contrast = GDISP_INITIAL_CONTRAST;
  return TRUE;
}

#if GDISP_HARDWARE_STREAM_WRITE
  LLDSPEC  void gdisp_lld_write_start(GDisplay *g) {
    acquire_bus(g);
    set_viewport(g);
  }
  LLDSPEC  void gdisp_lld_write_color(GDisplay *g) {
    write_data(g, gdispColor2Native(g->p.color));
  }
  LLDSPEC  void gdisp_lld_write_stop(GDisplay *g) {
    release_bus(g);
  }
#endif

#if GDISP_HARDWARE_STREAM_READ
  LLDSPEC  void gdisp_lld_read_start(GDisplay *g) {
    acquire_bus(g);
    set_viewport(g);
    setreadmode(g);
    dummy_read(g);
  }
  LLDSPEC  color_t gdisp_lld_read_color(GDisplay *g) {
    uint16_t  data;

    data = read_data(g);
    return gdispNative2Color(data);
  }
  LLDSPEC  void gdisp_lld_read_stop(GDisplay *g) {
    setwritemode(g);
    release_bus(g);
  }
#endif

#if GDISP_NEED_CONTROL && GDISP_HARDWARE_CONTROL
  LLDSPEC void gdisp_lld_control(GDisplay *g) {
    switch(g->p.x) {
    case GDISP_CONTROL_POWER:
      if (g->g.Powermode == (powermode_t)g->p.ptr)
        return;
      switch((powermode_t)g->p.ptr) {
      case powerOff:
        acquire_bus(g);
        write_reg(g, 0x0010, 0x0001);  /* enter sleep mode */
        release_bus(g);
        break;
      case powerOn:
        acquire_bus(g);
        write_reg(g, 0x0010, 0x0000);  /* leave sleep mode */
        release_bus(g);
        if (g->g.Powermode != powerSleep)
          gdisp_lld_init(g);
        break;
      case powerSleep:
        acquire_bus(g);
        write_reg(g, 0x0010, 0x0001);  /* enter sleep mode */
        release_bus(g);
        break;
      default:
        return;
      }
      g->g.Powermode = (powermode_t)g->p.ptr;
      return;

    case GDISP_CONTROL_ORIENTATION:
      if (g->g.Orientation == (orientation_t)g->p.ptr)
        return;
      switch((orientation_t)g->p.ptr) {
      case GDISP_ROTATE_0:
        acquire_bus(g);

        write_reg(g, 0x36, 0x0A);

        release_bus(g);
        g->g.Height = GDISP_SCREEN_HEIGHT;
        g->g.Width = GDISP_SCREEN_WIDTH;
        break;
      case GDISP_ROTATE_90:
        acquire_bus(g);

        write_reg(g, 0x36, 0x68);

        release_bus(g);
        g->g.Height = GDISP_SCREEN_WIDTH;
        g->g.Width = GDISP_SCREEN_HEIGHT;
        break;
      case GDISP_ROTATE_180:
        acquire_bus(g);

        write_reg(g, 0x36, 0xC9);

        release_bus(g);
        g->g.Height = GDISP_SCREEN_HEIGHT;
        g->g.Width = GDISP_SCREEN_WIDTH;
        break;
      case GDISP_ROTATE_270:
        acquire_bus(g);

        write_reg(g, 0x36, 0xAB);

        release_bus(g);
        g->g.Height = GDISP_SCREEN_WIDTH;
        g->g.Width = GDISP_SCREEN_HEIGHT;
        break;
      default:
        return;
      }
      g->g.Orientation = (orientation_t)g->p.ptr;
      return;
        //case GDISP_CONTROL_BACKLIGHT:
    //case GDISP_CONTROL_CONTRAST:
        default:
            return;
    }
  }
#endif

#endif /* GFX_USE_GDISP */
