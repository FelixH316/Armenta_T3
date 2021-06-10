/*
 * @file    main.c
 * @brief   T3 - RGB LED state machine with ISR & PIT on FRDM-K64F
 * @author	Félix Armenta A - PADTS IECA 3
 * @date	June 8th, 2021
 */

/* TODO: insert other include files here. */
#include "fsl_clock.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_common.h"
#include "fsl_pit.h"

#include <stdint.h>
#include <stdbool.h>
#include "RGB.h"
#include "TAREA3.h"

/* TODO: insert other definitions and declarations here. */

#define TPIN 2u
#define DEBUGtest false

uint8_t main(void){
	/*** LOCAL STRUCTs CONFIG ***/
	gpio_pin_config_t led_config = {
			kGPIO_DigitalOutput,
			1,					// Initial output value
	};

	gpio_pin_config_t sw_config = {
			kGPIO_DigitalInput,
			0,
	};

	const port_pin_config_t input_config = {
			kPORT_PullUp,
			kPORT_FastSlewRate,
			kPORT_PassiveFilterEnable,
			kPORT_OpenDrainDisable,
			kPORT_HighDriveStrength,
			kPORT_MuxAsGpio,
			kPORT_UnlockRegister,
	};


	/*** LED CONFIG ***/
	// LED Clock Gating
	CLOCK_EnableClock(kCLOCK_PortB);
	CLOCK_EnableClock(kCLOCK_PortE);

	// LEDs as GPIO
	PORT_SetPinMux(PORTB, RLED, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTE, GLED, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTB, BLED, kPORT_MuxAsGpio);

	// LEDs as outputs and start value
	GPIO_PinInit(GPIOB, RLED, &led_config);
	GPIO_PinInit(GPIOE, GLED, &led_config);
	GPIO_PinInit(GPIOB, BLED, &led_config);


	#if DEBUGtest
	/*** LOGIC TEST PIN CONFIG ***/
	// PORTB_2 as GPIO
	PORT_SetPinMux(PORTB, TPIN, kPORT_MuxAsGpio);

	// PORTB_2 as outputs and start value
	GPIO_PinInit(GPIOB, TPIN, &led_config);
	#endif

	/*** SW CONFIG ***/
	// SW Clock Gating
	CLOCK_EnableClock(kCLOCK_PortC);
	CLOCK_EnableClock(kCLOCK_PortA);

	// SWs config
	PORT_SetPinConfig(PORTC, SW2, &input_config);
	PORT_SetPinConfig(PORTA, SW3, &input_config);

	// SWs as extern ISR
	PORT_SetPinInterruptConfig(PORTC, SW2, kPORT_InterruptRisingEdge);
	PORT_SetPinInterruptConfig(PORTA, SW3, kPORT_InterruptRisingEdge);

	// SWs as inputs
	GPIO_PinInit(GPIOC, SW2, &sw_config);
	GPIO_PinInit(GPIOA, SW3, &sw_config);

	// SWs ISR enable and priorities
	NVIC_SetPriority(PORTC_IRQn, 3);
	NVIC_SetPriority(PORTA_IRQn, 3);
	NVIC_EnableIRQ(PORTC_IRQn);
	NVIC_EnableIRQ(PORTA_IRQn);

	/*** PIT CONFIG ***/

	// PIT Default config
	pit_config_t pitConfig;
	PIT_GetDefaultConfig(&pitConfig);
	PIT_Init(PIT, &pitConfig);

	// Setting PIT clock
	uint32_t freq;
	freq = CLOCK_GetFreq(kCLOCK_BusClk);

	// Setting PIT period for Ch0
	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, USEC_TO_COUNT(1000000U, freq));

	// Enable timer ISR for Ch0
	PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);

	// PIT NVIC enable and priority
	NVIC_EnableIRQ(PIT0_IRQn);
	NVIC_SetPriority(PIT0_IRQn, 0);

	// Start PIT Ch0
	PIT_StartTimer(PIT, kPIT_Chnl_0);


	/*** INITAL SYSTEM PARAMETERS ***/
	RGB_LedOff();
	setPitFlag();
	#if !DEBUGtest
	bool defaultStatus = true;
	#endif

    while(1){
    	if (getPitFlag())
    	{
    		switch (getCurrentSeq())
    		{
    		case seq1:
    			if (getCurrentStep() == STEP_ONE)
    			{
    				RGB_LedOn(YELLOW);
    			}
    			else if (getCurrentStep() == STEP_TWO)
    			{
    				RGB_LedOn(RED);
    			}
    			else if(getCurrentStep() == STEP_THREE)
    			{
    				RGB_LedOn(PURPLE);
    			}
    			break;
			#if !DEBUGtest
    		case seq2:
    			if (getCurrentStep() == STEP_ONE)
    			{
    				RGB_LedOn(GREEN);
    			}
    			else if (getCurrentStep() == STEP_TWO)
    			{
    				RGB_LedOn(BLUE);
    			}
    			else if(getCurrentStep() == STEP_THREE)
    			{
    				RGB_LedOn(RED);
    			}
    			break;
    		case seq3:
    			if (getCurrentStep() == STEP_ONE)
    			{
    				RGB_LedOn(BLUE);
    			}
    			else if (getCurrentStep() == STEP_TWO)
    			{
    				RGB_LedOn(WHITE);
    			}
    			else if(getCurrentStep() == STEP_THREE)
    			{
    				RGB_LedOn(RED);
    			}
    			break;
    		case seq4:
    			if (getCurrentStep() == STEP_ONE)
    			{
    				RGB_LedOn(GREEN);
    			}
    			else if (getCurrentStep() == STEP_TWO)
    			{
    				RGB_LedOn(PURPLE);
    			}
    			else if(getCurrentStep() == STEP_THREE)
    			{
    				RGB_LedOn(YELLOW);
    			}
    			break;
			#endif
    		default:
				#if DEBUGtest
    			RGB_LedOff();
    			GPIO_PortToggle(GPIOB, 1u << TPIN);
				#else
    			if (defaultStatus)
    			{
    				RGB_LedOn(RED);
    				defaultStatus = false;
    			}
    			else{
    				RGB_LedOff();
    				defaultStatus = true;
    			}
				#endif
    		}
    		clearPitFlag();
    	}
    }
    return 0;
}
