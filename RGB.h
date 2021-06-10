/*
 * @file    RGB.h
 * @brief   RGB lib header file
 * @author	Félix Armenta A - PADTS IECA 3
 * @date	Jun 9th 2021
 * @vers	v0.2
 */

#ifndef RGB_H_
#define RGB_H_

#include "fsl_gpio.h"
#include <stdint.h>

// LED Pins
#define RLED 22u
#define GLED 26u
#define BLED 21u

typedef enum {
	GREEN,
	BLUE,
	PURPLE,
	RED,
	YELLOW,
	WHITE,
}state_name_t;

void RGB_LedOn (uint8_t color);
void RGB_LedOff (void);

#endif /* RGB_H_ */
