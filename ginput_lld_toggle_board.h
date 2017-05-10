/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GDISP_LLD_TOGGLE_BOARD_H
#define _GDISP_LLD_TOGGLE_BOARD_H

// The below are example values
// The total number of toggle inputs
#define GINPUT_TOGGLE_NUM_PORTS		4
// The total number of GToggleConfig entries
#define GINPUT_TOGGLE_CONFIG_ENTRIES	1

#define GINPUT_TOGGLE_SW1		0
#define GINPUT_TOGGLE_SW2		1
#define GINPUT_TOGGLE_SW3		2
#define GINPUT_TOGGLE_SW4		3

#define GINPUT_TOGGLE_DECLARE_STRUCTURE() \
	const GToggleConfig GInputToggleConfigTable[GINPUT_TOGGLE_CONFIG_ENTRIES] = { \
		{GPIOE,	/* Switch 1 - Switch 4 */ \
			GPIOE_BTN1_MASK|GPIOE_BTN2_MASK|GPIOE_BTN3_MASK|GPIOE_BTN4_MASK, \
			GPIOE_BTN1_MASK|GPIOE_BTN2_MASK|GPIOE_BTN3_MASK|GPIOE_BTN4_MASK, \
			PAL_MODE_INPUT}, \
	}

#endif /* _GDISP_LLD_TOGGLE_BOARD_H */
