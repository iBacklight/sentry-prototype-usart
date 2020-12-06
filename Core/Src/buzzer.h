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
void buzzer_play_c(int32_t duration);

#endif /* SRC_BUZZER_H_ */
