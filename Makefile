# Possible Targets:	all clean Debug cleanDebug Release cleanRelease

##############################################################################################
# Settings
#

# General settings
	# See $(GFXLIB)/tools/gmake_scripts/readme.txt for the list of variables
	OPT_OS			= chibios
	OPT_THUMB		= yes
	OPT_LINK_OPTIMIZE	= yes
	OPT_CPU			= stm32m1

# uGFX settings
	# See $(GFXLIB)/tools/gmake_scripts/library_ugfx.mk for the list of variables
	GFXLIB			= C:/ChibiStudio/ugfx
#	GFXDEMO			= 3rdparty/bubbles
	GFXSINGLEMAKE		= no
 
# ChibiOS settings
ifeq ($(OPT_OS),chibios)
	# See $(GFXLIB)/tools/gmake_scripts/os_chibios.mk for the list of variables
	CHIBIOS			= ../../chibios3
	CHIBIOS_VERSION		= 3
	CHIBIOS_CPUCLASS	= ARMCMx
	CHIBIOS_PLATFORM	= STM32
	CHIBIOS_DEVICE_FAMILY	= STM32F1xx
	CHIBIOS_STARTUP		= startup_stm32f1xx
	CHIBIOS_PORT		= v7m
	CHIBIOS_LDSCRIPT	= STM32F103xE.ld
	# We define a non standard board script as this is not a standard ChibiOS supported board
	include HY-STM32/board.mk
endif

GFXINC	+= .
GFXSRC	+= .
GFXDEFS += -DGFX_USE_CHIBIOS=TRUE

include SSD1289/driver.mk
#include $(GFXLIB)/drivers/gdisp/ILI9481/driver.mk
include $(GFXLIB)/drivers/ginput/toggle/Pal/driver.mk

##############################################################################################
# Set these for your project
#
PROJECT = SSD1963

ARCH     = arm-none-eabi-
SRCFLAGS = -ggdb -Os
CFLAGS   =
CXXFLAGS = -fno-rtti
ASFLAGS  =
LDFLAGS  =

SRC      = main.c
OBJS     =
DEFS     =
LIBS     =
INCPATH  = .
LIBPATH  =
LDSCRIPT =

##############################################################################################
# These should be at the end
#

include $(GFXLIB)/tools/gmake_scripts/library_ugfx.mk
include $(GFXLIB)/tools/gmake_scripts/os_$(OPT_OS).mk
include $(GFXLIB)/tools/gmake_scripts/compiler_gcc.mk
# *** EOF ***
