/*
 * buzzer.h
 *
 *  Created on: Dec 5, 2020
 *      Author: AzureRin
 */

#ifndef SRC_BUZZER_H_
#define SRC_BUZZER_H_

#include "main.h"
#include "cmsis_os.h"


void buzzer_init(void);
void buzzer_play_scale(int32_t duration);
void buzzer_play_chromatic(int32_t duration);
void buzzer_play_o_canada(int32_t bpm);
void buzzer_play_mario(int32_t bpm);

#endif /* SRC_BUZZER_H_ */
