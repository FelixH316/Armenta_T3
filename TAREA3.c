/*
 * @file    TAREA3.c
 * @brief   ISR & PIT implementation for sequence and steps on RGB LED
 * @author	Félix Armenta A - PADTS IECA 3
 * @date	Jun 10th, 2021
 * @vers	v0.1
 */
#include "TAREA3.h"

volatile sequence_t currentSeq = seq1;
volatile uint8_t currentStep = STEP_ONE;
volatile bool pitFlag = false;
volatile bool sw2Flag = false;
volatile bool sw3Flag = false;

void PORTC_IRQHandler(void)
{
	GPIO_PortClearInterruptFlags(GPIOC, 1u << SW2);
	sw2Flag = true;
	SDK_ISR_EXIT_BARRIER;
}

void PORTA_IRQHandler(void)
{
	GPIO_PortClearInterruptFlags(GPIOA, 1u << SW3);
	sw3Flag = true;
	SDK_ISR_EXIT_BARRIER;
}

void PIT0_IRQHandler(void)
{
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
	if (currentStep == STEP_THREE)
	{
		currentStep = STEP_ONE;
		if ((sw2Flag == true) && (currentSeq == seq1))
		{
			currentSeq = seq2;
			sw2Flag = false;
			sw3Flag = false;
		}
		else if ((sw3Flag == true) && (currentSeq == seq2))
		{
			currentSeq = seq3;
			sw2Flag = false;
			sw3Flag = false;
		}
		else if ((sw3Flag == true) && (currentSeq == seq3))
		{
			currentSeq = seq4;
			sw2Flag = false;
			sw3Flag = false;
		}
		else if ((sw2Flag == true) && (currentSeq == seq4))
		{
			currentSeq = seq1;
			sw2Flag = false;
			sw3Flag = false;
		}
	}
	else{
		currentStep++;
	}
	pitFlag = true;
	__DSB();
}

sequence_t getCurrentSeq(void)
{
	return currentSeq;
}

uint8_t getCurrentStep(void)
{
	return currentStep;
}

void setPitFlag(void)
{
	pitFlag = true;
}

void clearPitFlag(void)
{
	pitFlag = false;
}

bool getPitFlag(void)
{
	return pitFlag;
}

