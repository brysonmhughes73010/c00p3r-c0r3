#ifndef LV_CONF_H
#define LV_CONF_H

#include <stdint.h>

/*====================
   Graphical settings
 *====================*/

/* Maximal horizontal and vertical resolution to support by the library.*/
#define LV_HOR_RES_MAX          (480)
#define LV_VER_RES_MAX          (320)

/* Color depth:
 * - 1:  1 byte per pixel
 * - 8:  RGB233
 * - 16: RGB565
 * - 32: ARGB8888
 */
#define LV_COLOR_DEPTH     16

/*=========================
   Memory manager settings
 *=========================*/

/* Size of the memory used by `lv_mem_alloc` in bytes (>= 2kB)*/
#define LV_MEM_SIZE    (32U * 1024U)          /*[bytes]*/

/*=======================
   Input device settings
 *=======================*/

/* Input device read period in milliseconds */
#define LV_INDEV_DEF_READ_PERIOD          30

/*==================
 * Feature usage
 *==================*/

/*1: Enable the Animations */
#define LV_USE_ANIMATION        1

/*1: Enable shadow drawing*/
#define LV_USE_SHADOW           1

/*1: Enable object groups (for keyboards)*/
#define LV_USE_GROUP            1

/*1: Enable GPU interface*/
#define LV_USE_GPU              1

/*1: Enable file system (might be required for images)*/
#define LV_USE_FILESYSTEM       1

/*1: Add a `user_data` to drivers and objects*/
#define LV_USE_USER_DATA        1

#endif /*LV_CONF_H*/