/*
 * Motor.h
 *
 *  Created on: Mar. 25, 2021
 *      Author: Bailiang's Desktop
 */

#ifndef SRC_DEVICE_MOTOR_H_
#define SRC_DEVICE_MOTOR_H_

//Define needs to go ahead of include here for whatever reason....

#define MOTOR_COUNT 8
#define MOTOR_3508_STDID 0x1FF
#define MOTOR_6020_STDID 0x200

#define CAN_RX_ID_START 0x201



#include "main.h"
#include "cmsis_os.h"
#include "can.h"


typedef struct {
	uint32_t stdid;
	uint32_t P_prameter;
	uint32_t I_prameter;
	uint32_t D_prameter;
}Motor_Info;

typedef struct {
	int16_t rx_angle;
	int16_t rx_rpm;
	int16_t rx_current;
	int16_t rx_temp;
} Motor_Feedback_Data_t;


typedef struct {
	Motor_Info motor_info;
	Motor_Feedback_Data_t motor_feedback;
	//Data need to sent to Motor
	int32_t tx_data;

	//Maybe PID data in here too

}Motor;

// first 4th motor will use 0x1FF, last 4th motor will use 0x200
// motor_data[0]: first 	3508
// motor_data[1]: second 	3508
// motor_data[2]: third 	3508

// motor_data[4]: first 	6020
// motor_data[5]: second 	6020


Motor motor_data[MOTOR_COUNT];

void Motor_Data_Read();
void Motor_Data_Sent();

#endif /* SRC_DEVICE_MOTOR_H_ */
