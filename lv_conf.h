/**
 * @file lv_conf.h
 * Configuration file for LVGL v8.3
 */

#ifndef LV_CONF_H
#define LV_CONF_H

#include <stdint.h>

/*====================
   COLOR SETTINGS
 *====================*/

/*Color depth: 1 (1 byte per pixel), 8 (RGB332), 16 (RGB565), 32 (ARGB8888)*/
#define LV_COLOR_DEPTH 16

/*Swap the 2 bytes of RGB565 color. Useful if the display has an 8-bit interface (e.g., SPI)*/
#define LV_COLOR_16_SWAP 0

/*Enable features to draw on transparent background.
 *It's required if opa, and transform_* style properties are used.*/
#define LV_COLOR_SCREEN_TRANSP 0

/*====================
   MEMORY SETTINGS
 *====================*/

/*Size of the memory available for `lv_mem_alloc()` in bytes (>= 2kB)*/
#define LV_MEM_SIZE (64 * 1024U)

/*Set an address for the memory pool instead of allocating it as a normal array.*/
#define LV_MEM_ADR 0

/*Number of the intermediate memory buffer used during rendering and other internal processing mechanisms.
 *You will see an error log message if there wasn't enough buffers.*/
#define LV_MEM_BUF_MAX_NUM 16

/*====================
   HAL SETTINGS
 *====================*/

/*Default display refresh period. LVG will redraw changed areas with this period time*/
#define LV_DISP_DEF_REFR_PERIOD 30

/*Input device read period in milliseconds*/
#define LV_INDEV_DEF_READ_PERIOD 30

/*Use a custom tick source that tells the elapsed time in milliseconds.*/
#define LV_TICK_CUSTOM 1
#if LV_TICK_CUSTOM
extern uint32_t custom_tick_get(void);
#define LV_TICK_CUSTOM_INCLUDE "Arduino.h"
#define LV_TICK_CUSTOM_SYS_TIME_EXPR (millis())
#endif

/*Default Dot Per Inch. Used to initialize default sizes such as widgets sized, style paddings.
 *(Not so important, you can adjust it to modify default sizes and spaces)*/
#define LV_DPI_DEF 130

/*===================
 * FEATURE CONFIGURATION
 *===================*/

/*-------------
 * Drawing
 *-----------*/

/*Enable/Disable styles*/
#define LV_USE_STYLE 1

/*Enable and setup the built-in styles*/
#define LV_USE_BUILTIN_STYLE 1

/*Enable anti-aliasing (lines, and radiuses will be smoothed)*/
#define LV_USE_ANTIALIAS 1

/*Default cache size in bytes.
 *Used by image decoders such as `lv_img_decoder_get_cache_size()`*/
#define LV_IMG_CACHE_DEF_SIZE 1

/*Number of stops in gradient. A larger value means smoother gradients.*/
#define LV_GRADIENT_MAX_STOPS 16

/*Maximum buffer size to allocate for rotation.*/
#define LV_DISP_ROT_MAX_BUF (10*1024)

/*-------------
 * Others
 *-----------*/

/*1: Show CPU usage and FPS count in the right bottom corner*/
#define LV_USE_PERF_MONITOR 0

/*1: Show the used memory and the memory fragmentation in the left bottom corner
 * Requires LV_MEM_CUSTOM = 0*/
#define LV_USE_MEM_MONITOR 0

/*1: Draw random colored rectangles over the redrawn areas*/
#define LV_USE_REFR_DEBUG 0

/*===================
 * EXAMPLES, DEMOS, BENCHMARKS
 *===================*/

/*Show some widget. It might be required to increase `LV_MEM_SIZE` */
#define LV_USE_DEMO_WIDGETS 0
#define LV_USE_DEMO_KEYPAD_AND_ENCODER 0
#define LV_USE_DEMO_BENCHMARK 0
#define LV_USE_DEMO_STRESS 0
#define LV_USE_DEMO_MUSIC 0

/*===================
 * WIDGETS
 *===================*/

/*Documented widgets*/
#define LV_USE_ARC 1
#define LV_USE_BAR 1
#define LV_USE_BTN 1
#define LV_USE_BTNMATRIX 1
#define LV_USE_CANVAS 1
#define LV_USE_CHECKBOX 1
#define LV_USE_DROPDOWN 1
#define LV_USE_IMG 1
#define LV_USE_LABEL 1
#define LV_USE_LINE 1
#define LV_USE_ROLLER 1
#define LV_USE_SLIDER 1
#define LV_USE_SWITCH 1
#define LV_USE_TEXTAREA 1
#define LV_USE_TABLE 1

/*Extra widgets*/
#define LV_USE_ANIMIMG 1
#define LV_USE_CALENDAR 1
#define LV_USE_CHART 1
#define LV_USE_COLORWHEEL 1
#define LV_USE_IMGBTN 1
#define LV_USE_KEYBOARD 1
#define LV_USE_LED 1
#define LV_USE_LIST 1
#define LV_USE_MENU 1
#define LV_USE_METER 1
#define LV_USE_MSGBOX 1
#define LV_USE_SPAN 1
#define LV_USE_SPINBOX 1
#define LV_USE_SPINNER 1
#define LV_USE_TABVIEW 1
#define LV_USE_TILEVIEW 1
#define LV_USE_WIN 1

/*==================
 * THEME USAGE
 *==================*/

#define LV_USE_THEME_DEFAULT 1
#define LV_USE_THEME_BASIC 1
#define LV_USE_THEME_MONO 0

/*==================
 * FONT USAGE
 *==================*/

/*Montserrat fonts with ASCII range and some symbols using bpp = 4*/
#define LV_FONT_MONTSERRAT_8  1
#define LV_FONT_MONTSERRAT_10 1
#define LV_FONT_MONTSERRAT_12 1
#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_MONTSERRAT_16 1
#define LV_FONT_MONTSERRAT_18 1
#define LV_FONT_MONTSERRAT_20 1
#define LV_FONT_MONTSERRAT_22 1
#define LV_FONT_MONTSERRAT_24 1
#define LV_FONT_MONTSERRAT_26 1
#define LV_FONT_MONTSERRAT_28 1
#define LV_FONT_MONTSERRAT_30 1
#define LV_FONT_MONTSERRAT_32 1
#define LV_FONT_MONTSERRAT_34 1
#define LV_FONT_MONTSERRAT_36 1
#define LV_FONT_MONTSERRAT_38 1
#define LV_FONT_MONTSERRAT_40 1
#define LV_FONT_MONTSERRAT_42 1
#define LV_FONT_MONTSERRAT_44 1
#define LV_FONT_MONTSERRAT_46 1
#define LV_FONT_MONTSERRAT_48 1

/*Declare the custom (user defined) fonts*/
#define LV_FONT_CUSTOM_DECLARE

/*Enable subpixel rendering*/
#define LV_USE_FONT_SUBPX 0
#if LV_USE_FONT_SUBPX
/*Set the pixel order of the display. Physical order of RGB channels.*/
#define LV_FONT_SUBPX_BGR 0
#endif

/*==================
 * OTHERS
 *==================*/

/*Enable the GPU to accelerate the drawing.*/
#define LV_USE_GPU_STM32_DMA2D 0
#define LV_USE_GPU_ARM2D 0

/*Use SDL to open window on PC and handle mouse and keyboard*/
#define LV_USE_SDL 0

/*Enable PXP for CPU off-load on NXP RTxxx platforms*/
#define LV_USE_PXP 0

/*Enable file system (might be required for images)*/
#define LV_USE_FS_STDIO 0
#define LV_FS_STDIO_LETTER '\0'

/*==================
 * OBSOLETE SETTINGS
 *==================*/

/*For backward compatibility*/
#define LV_USE_GROUP 1
#define LV_USE_ANIMATION 1
#define LV_USE_SHADOW 1
#define LV_USE_OUTLINE 1
#define LV_USE_PATTERN 1
#define LV_USE_VALUE_STR 1
#define LV_USE_BLEND_MODES 1

#endif  /*LV_CONF_H*/