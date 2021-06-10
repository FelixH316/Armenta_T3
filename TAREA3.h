/*
 * @file    TAREA3.h
 * @brief   ISR & PIT definitions for sequence and steps on RGB LED
 * @author	Félix Armenta A - PADTS IECA 3
 * @date	Jun 10th 2021
 * @vers	v0.1
 */

#ifndef TAREA3_H_
#define TAREA3_H_

#include <stdbool.h>
#include "fsl_gpio.h"
#include "fsl_common.h"
#include "fsl_pit.h"

#define SW2 6u
#define SW3 4u
#define STEP_ONE 0u
#define STEP_TWO 1u
#define STEP_THREE 2u

typedef enum{seq1, seq2, seq3, seq4} sequence_t;

void PORTC_IRQHandler(void);
void PORTA_IRQHandler(void);
void PIT0_IRQHandler(void);

sequence_t getCurrentSeq(void);
uint8_t getCurrentStep(void);
void setPitFlag(void);
void clearPitFlag(void);
bool getPitFlag(void);

#endif /* TAREA3_H_ */
