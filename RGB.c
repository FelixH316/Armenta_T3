/*
 * @file    RGB.c
 * @brief   RGB lib source file
 * @author	Félix Armenta A - PADTS IECA 3
 * @date	Jun 9th 2021
 * @vers	v0.2
 */
#include "RGB.h"

void RGB_LedOn (state_name_t color)
{
	switch (color)
	{
	case GREEN:
		GPIO_PortSet(GPIOB, 1u << RLED);
		GPIO_PortClear(GPIOE, 1u << GLED);
		GPIO_PortSet(GPIOB, 1u << BLED);
		break;
	case BLUE:
		GPIO_PortSet(GPIOB, 1u << RLED);
		GPIO_PortSet(GPIOE, 1u << GLED);
		GPIO_PortClear(GPIOB, 1u << BLED);
		break;
	case PURPLE:
		GPIO_PortClear(GPIOB, 1u << RLED);
		GPIO_PortSet(GPIOE, 1u << GLED);
		GPIO_PortClear(GPIOB, 1u << BLED);
		break;
	case RED:
		GPIO_PortClear(GPIOB, 1u << RLED);
		GPIO_PortSet(GPIOE, 1u << GLED);
		GPIO_PortSet(GPIOB, 1u << BLED);
		break;
	case YELLOW:
		GPIO_PortClear(GPIOB, 1u << RLED);
		GPIO_PortClear(GPIOE, 1u << GLED);
		GPIO_PortSet(GPIOB, 1u << BLED);
		break;
	case WHITE:
		GPIO_PortClear(GPIOB, 1u << RLED);
		GPIO_PortClear(GPIOE, 1u << GLED);
		GPIO_PortClear(GPIOB, 1u << BLED);
		break;
	default:
		// RED
		GPIO_PortClear(GPIOB, 1u << RLED);
		GPIO_PortSet(GPIOE, 1u << GLED);
		GPIO_PortSet(GPIOB, 1u << BLED);
	}
}

void RGB_LedOff (void)
{
	GPIO_PortSet(GPIOB, 1u << RLED);
	GPIO_PortSet(GPIOE, 1u << GLED);
	GPIO_PortSet(GPIOB, 1u << BLED);
}
