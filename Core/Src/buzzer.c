/*
 * buzzer.c
 *
 *  Created on: Dec 5, 2020
 *      Author: AzureRin
 *      Description: Use spreadsheet to add notes to the autoreload values, they correspond to PWM frequency
 *      Set_compare values correspond to duty cycle, aka volume
 *      Use HAL_Delay instead of OS_delay if you want to use it before free RTOS kicks in
 */

#include "buzzer.h"

void buzzer_init(void){
	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);

}

void buzzer_play_g0(int32_t duration){
	__HAL_TIM_SET_COUNTER(&htim12,0);
	//__HAL_TIM_PRESCALER(&htim12, 35);
	__HAL_TIM_SET_AUTORELOAD(&htim12,9523);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,100);
	osDelay(duration);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,0);
}

void buzzer_play_c1(int32_t duration){
	__HAL_TIM_SET_COUNTER(&htim12,0);
	//__HAL_TIM_PRESCALER(&htim12, 35);
	__HAL_TIM_SET_AUTORELOAD(&htim12,7135);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,100);
	osDelay(duration);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,0);
}


void buzzer_play_cs1(int32_t duration){
	__HAL_TIM_SET_COUNTER(&htim12,0);
	//__HAL_TIM_PRESCALER(&htim12, 35);
	__HAL_TIM_SET_AUTORELOAD(&htim12,6733);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,100);
	osDelay(duration);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,0);
}

void buzzer_play_d1(int32_t duration){
	//__HAL_TIM_PRESCALER(&htim12, 28);
	__HAL_TIM_SET_COUNTER(&htim12,0);
	__HAL_TIM_SET_AUTORELOAD(&htim12,6355);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,100);
	osDelay(duration);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,0);
}

void buzzer_play_ds1(int32_t duration){
	//__HAL_TIM_PRESCALER(&htim12, 28);
	__HAL_TIM_SET_COUNTER(&htim12,0);
	__HAL_TIM_SET_AUTORELOAD(&htim12,5999);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,100);
	osDelay(duration);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,0);
}

void buzzer_play_e1(int32_t duration){
	//__HAL_TIM_PRESCALER(&htim12, 25);
	__HAL_TIM_SET_COUNTER(&htim12,0);
	__HAL_TIM_SET_AUTORELOAD(&htim12,5662);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,100);
	osDelay(duration);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,0);
}

void buzzer_play_f1(int32_t duration){
	//__HAL_TIM_PRESCALER(&htim12, 24);
	__HAL_TIM_SET_COUNTER(&htim12,0);
	__HAL_TIM_SET_AUTORELOAD(&htim12,5345);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,100);
	osDelay(duration);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,0);
}

void buzzer_play_fs1(int32_t duration){
	//__HAL_TIM_PRESCALER(&htim12, 24);
	__HAL_TIM_SET_COUNTER(&htim12,0);
	__HAL_TIM_SET_AUTORELOAD(&htim12,5044);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,100);
	osDelay(duration);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,0);
}

void buzzer_play_g1(int32_t duration){
	//__HAL_TIM_PRESCALER(&htim12, 21);
	__HAL_TIM_SET_COUNTER(&htim12,0);
	__HAL_TIM_SET_AUTORELOAD(&htim12,4761);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,100);
	osDelay(duration);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,0);
}


void buzzer_play_gs1(int32_t duration){
	//__HAL_TIM_PRESCALER(&htim12, 21);
	__HAL_TIM_SET_COUNTER(&htim12,0);
	__HAL_TIM_SET_AUTORELOAD(&htim12,4494);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,100);
	osDelay(duration);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,0);
}

void buzzer_play_a1(int32_t duration){
	//__HAL_TIM_PRESCALER(&htim12, 19);
	__HAL_TIM_SET_COUNTER(&htim12,0);
	__HAL_TIM_SET_AUTORELOAD(&htim12,4241);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,100);
	osDelay(duration);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,0);
}

void buzzer_play_as1(int32_t duration){
	//__HAL_TIM_PRESCALER(&htim12, 19);
	__HAL_TIM_SET_COUNTER(&htim12,0);
	__HAL_TIM_SET_AUTORELOAD(&htim12,4003);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,100);
	osDelay(duration);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,0);
}

void buzzer_play_b1(int32_t duration){
	//__HAL_TIM_PRESCALER(&htim12, 17);
	__HAL_TIM_SET_COUNTER(&htim12,0);
	__HAL_TIM_SET_AUTORELOAD(&htim12,3778);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,100);
	osDelay(duration);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,0);
}

void buzzer_play_c2(int32_t duration){
	//__HAL_TIM_PRESCALER(&htim12, 16);
	__HAL_TIM_SET_COUNTER(&htim12,0);
	__HAL_TIM_SET_AUTORELOAD(&htim12,3566);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,100);
	osDelay(duration);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,0);
}

void buzzer_play_cs2(int32_t duration){
	//__HAL_TIM_PRESCALER(&htim12, 16);
	__HAL_TIM_SET_COUNTER(&htim12,0);
	__HAL_TIM_SET_AUTORELOAD(&htim12,3366);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,100);
	osDelay(duration);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,0);
}

void buzzer_play_d2(int32_t duration){
	//__HAL_TIM_PRESCALER(&htim12, 16);
	__HAL_TIM_SET_COUNTER(&htim12,0);
	__HAL_TIM_SET_AUTORELOAD(&htim12,3177);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,100);
	osDelay(duration);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,0);
}

void buzzer_play_ds2(int32_t duration){
	//__HAL_TIM_PRESCALER(&htim12, 16);
	__HAL_TIM_SET_COUNTER(&htim12,0);
	__HAL_TIM_SET_AUTORELOAD(&htim12,2999);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,100);
	osDelay(duration);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,0);
}

void buzzer_play_e2(int32_t duration){
	//__HAL_TIM_PRESCALER(&htim12, 16);
	__HAL_TIM_SET_COUNTER(&htim12,0);
	__HAL_TIM_SET_AUTORELOAD(&htim12,2830);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,100);
	osDelay(duration);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,0);
}

void buzzer_play_as2(int32_t duration){
	//__HAL_TIM_PRESCALER(&htim12, 16);
	__HAL_TIM_SET_COUNTER(&htim12,0);
	__HAL_TIM_SET_AUTORELOAD(&htim12,2001);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,100);
	osDelay(duration);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,0);
}

void buzzer_play_g2(int32_t duration){
	//__HAL_TIM_PRESCALER(&htim12, 16);
	__HAL_TIM_SET_COUNTER(&htim12,0);
	__HAL_TIM_SET_AUTORELOAD(&htim12,2380);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,100);
	osDelay(duration);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,0);
}

void buzzer_play_gs2(int32_t duration){
	//__HAL_TIM_PRESCALER(&htim12, 16);
	__HAL_TIM_SET_COUNTER(&htim12,0);
	__HAL_TIM_SET_AUTORELOAD(&htim12,2246);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,100);
	osDelay(duration);
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,0);
}

void buzzer_rest(int32_t duration){
	osDelay(duration);
}

void buzzer_play_scale(int32_t duration){
	buzzer_play_c1(duration);
	buzzer_play_d1(duration);
	buzzer_play_e1(duration);
	buzzer_play_f1(duration);
	buzzer_play_g1(duration);
	buzzer_play_a1(duration);
	buzzer_play_b1(duration);
	buzzer_play_c2(duration);
}

void buzzer_play_chromatic(int32_t duration){
	buzzer_play_c1(duration);
	buzzer_play_cs1(duration);
	buzzer_play_d1(duration);
	buzzer_play_ds1(duration);
	buzzer_play_e1(duration);
	buzzer_play_f1(duration);
	buzzer_play_fs1(duration);
	buzzer_play_g1(duration);
	buzzer_play_gs1(duration);
	buzzer_play_a1(duration);
	buzzer_play_as1(duration);
	buzzer_play_b1(duration);
	buzzer_play_c2(duration);
}

void buzzer_play_o_canada(int32_t bpm){
	int32_t quarter=(double)60/bpm*1000;
	int32_t quarter_dot=(double)60/bpm*1000*1.5;
	int32_t eighth=(double)60/bpm*1000*0.5;
	int32_t eighth_dot=(double)60/bpm*1000*0.5*1.5;
	int32_t sixteenth=(double)60/bpm*0.25*1000;
	int32_t sixteenth_dot=(double)60/bpm*0.25*1000*1.5;
	int32_t half=(double)60/bpm*2*1000;
	int32_t half_dot=(double)60/bpm*2*1000*1.5;
	int32_t whole=(double)60/bpm*4*1000;

	buzzer_play_a1(half);
	buzzer_play_c2(quarter_dot);
	buzzer_play_c2(eighth);
	buzzer_play_f1(half_dot);
	buzzer_play_g1(quarter);
	buzzer_play_a1(quarter);
	buzzer_play_as1(quarter);
	buzzer_play_c2(quarter);
	buzzer_play_d2(quarter);
	buzzer_play_g1(half_dot);



}

void buzzer_play_mario(int32_t bpm){
	int32_t quarter=(double)60/bpm*1000;
	int32_t quarter_dot=(double)60/bpm*1000*1.5;
	int32_t eighth=(double)60/bpm*1000*0.5;
	int32_t eighth_dot=(double)60/bpm*1000*0.5*1.5;
	int32_t sixteenth=(double)60/bpm*0.25*1000;
	int32_t sixteenth_dot=(double)60/bpm*0.25*1000*1.5;
	int32_t half=(double)60/bpm*2*1000;
	int32_t half_dot=(double)60/bpm*2*1000*1.5;
	int32_t whole=(double)60/bpm*4*1000;

	buzzer_play_e1(eighth);
	buzzer_play_e1(eighth);
	buzzer_rest(eighth);
	buzzer_play_e1(eighth);
	buzzer_rest(eighth);
	buzzer_play_c1(eighth);
	buzzer_play_e1(quarter);
	buzzer_play_g1(quarter);
	buzzer_rest(quarter);
	buzzer_play_g0(quarter);


}

void buzzer_play_ynk(int32_t bpm){
	int32_t quarter=(double)60/bpm*1000;
	int32_t quarter_dot=(double)60/bpm*1000*1.5;
	int32_t eighth=(double)60/bpm*1000*0.5;
	int32_t eighth_dot=(double)60/bpm*1000*0.5*1.5;
	int32_t sixteenth=(double)60/bpm*0.25*1000;
	int32_t sixteenth_dot=(double)60/bpm*0.25*1000*1.5;
	int32_t half=(double)60/bpm*2*1000;
	int32_t half_dot=(double)60/bpm*2*1000*1.5;
	int32_t whole=(double)60/bpm*4*1000;

	/* end of m41 */
		buzzer_play_ds2(eighth);
		buzzer_play_d2(eighth);
		buzzer_play_as1(eighth);

		/*m42*/
		buzzer_play_as1(eighth_dot);
		buzzer_play_c2(eighth_dot);
		buzzer_play_g1(eighth);
		buzzer_play_f1(eighth);
		buzzer_play_ds1(eighth);
		buzzer_play_f1(eighth);
		buzzer_play_c2(eighth);

		/*m43*/
		buzzer_play_as1(eighth);
		buzzer_play_f1(sixteenth);
		buzzer_play_g1(eighth);
		buzzer_play_ds1(sixteenth);
		buzzer_play_f1(sixteenth);
		buzzer_play_ds1(quarter);
		buzzer_play_ds1(eighth);
		buzzer_play_as1(eighth);

		/*m44*/
		buzzer_play_gs1(eighth);
		buzzer_play_g1(eighth);
		buzzer_play_f1(eighth);
		buzzer_play_ds1(eighth);
		buzzer_play_d1(eighth);
		buzzer_play_ds1(eighth);
		buzzer_play_f1(eighth);
		buzzer_play_gs1(eighth);

		/*m45*/
		buzzer_play_g1(eighth);
		buzzer_play_f1(sixteenth);
		buzzer_play_g1(eighth_dot);
		buzzer_play_c2(eighth);
		buzzer_play_as1(quarter);
		buzzer_play_g1(eighth);
		buzzer_play_as1(eighth);

		//m46
		buzzer_play_c2(eighth_dot);
		buzzer_play_gs1(eighth_dot);
		buzzer_play_g1(eighth);
		buzzer_play_f1(eighth);
		buzzer_play_ds1(eighth);
		buzzer_play_f1(eighth);
		buzzer_play_c2(eighth);

		//m47
		buzzer_play_as1(eighth);
		buzzer_play_c2(sixteenth);
		buzzer_play_g1(eighth_dot);
		buzzer_play_f1(eighth);
		buzzer_play_ds1(eighth);
		buzzer_rest(eighth);
		buzzer_play_c1(eighth);
		buzzer_play_d1(eighth);

		//m48
		buzzer_play_ds1(eighth);
		buzzer_play_c1(eighth);
		buzzer_play_ds1(eighth);
		buzzer_play_f1(eighth);
		buzzer_play_g1(eighth);
		buzzer_play_ds1(eighth);
		buzzer_play_g1(eighth);
		buzzer_play_c1(eighth);

		//m49
		buzzer_play_b1(eighth);
		buzzer_rest(eighth);
		buzzer_play_g1(eighth);
		buzzer_play_g1(eighth);
		buzzer_play_ds2(eighth);
		buzzer_play_d2(eighth);
		buzzer_play_as1(eighth);

		//m50
		buzzer_play_as1(eighth_dot);
		buzzer_play_c2(eighth_dot);
		buzzer_play_g1(eighth);
		buzzer_play_f1(eighth);
		buzzer_play_ds1(eighth);
		buzzer_play_f1(eighth);
		buzzer_play_c2(eighth);

		//m51
		buzzer_play_as1(eighth);
		buzzer_play_c2(sixteenth);
		buzzer_play_g1(eighth_dot);
		buzzer_play_f1(eighth);
		buzzer_play_ds1(eighth);
		buzzer_rest(eighth);
		buzzer_play_ds1(eighth);
		buzzer_play_as1(eighth);

		//m52
		buzzer_play_gs1(eighth);
		buzzer_play_g1(eighth);
		buzzer_play_f1(eighth);
		buzzer_play_ds1(eighth);
		buzzer_play_d1(eighth);
		buzzer_play_ds1(eighth);
		buzzer_play_f1(eighth);
		buzzer_play_gs1(eighth);

		//m53
		buzzer_play_g1(eighth);
		buzzer_play_f1(sixteenth);
		buzzer_play_g1(eighth_dot);
		buzzer_play_c2(eighth);
		buzzer_play_as1(quarter);
		buzzer_play_g1(eighth);
		buzzer_play_as1(eighth);

		//m54
		buzzer_play_c2(eighth_dot);
		buzzer_play_gs1(eighth_dot);
		buzzer_play_g1(eighth);
		buzzer_play_f1(eighth);
		buzzer_play_d2(eighth);
		buzzer_play_c2(eighth);
		buzzer_play_as1(eighth);

		//m55
		buzzer_play_as1(eighth);
		buzzer_play_c2(eighth);
		buzzer_play_d2(eighth);
		buzzer_play_ds2(quarter);
		buzzer_play_g1(eighth);
		buzzer_play_f1(eighth);
		buzzer_play_ds1(eighth);

		//m56
		buzzer_rest(eighth);
		buzzer_play_c1(eighth);
		buzzer_play_ds1(eighth);
		buzzer_play_gs1(sixteenth);
		buzzer_play_g1(eighth);
		buzzer_rest(sixteenth);
		buzzer_play_ds1(eighth);
}
