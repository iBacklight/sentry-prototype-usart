#include "Motor.h"


/**
 * This function will read all data from
 */
void Motor_Data_Read() {

	uint8_t motorStatus2[8];
	for (int i=0; i<MOTOR_COUNT; i++) {
		can_filter_enable(&hcan1);

		memcpy(motorStatus2, can_rx_buffer[i],8);
		motor_data[i].motor_feedback.rx_angle	=(int16_t)(motorStatus2[0] << 8 | motorStatus2[1]);
		motor_data[i].motor_feedback.rx_rpm		=(int16_t)(motorStatus2[2] << 8 | motorStatus2[3]);
		motor_data[i].motor_feedback.rx_current =(int16_t)(motorStatus2[4] << 8 | motorStatus2[5]);
		motor_data[i].motor_feedback.rx_temp	=(int16_t)(motorStatus2[6]);
		//Current angle is absolute
		osDelay(1);

		can_filter_disable(&hcan1);
	}
}

/**
 * This function will sent all motor inputs from Motor_data array with two iteration
 * The first iteration is sent to motors with StdID of 0x1FF as Motor 3508
 * The second iteration is sent to motors with StdID of 0x200 as Motor 6020
 */
void Motor_Data_Sent() {
    uint8_t chassis_can_send_data[8];
    uint32_t send_mail_box;
    CAN_TxHeaderTypeDef  chassis_tx_message;

    chassis_tx_message.IDE = CAN_ID_STD;
    chassis_tx_message.RTR = CAN_RTR_DATA;
    chassis_tx_message.DLC = 0x08;

	for (int i=0; i<2; i++) {
		if (i == 0) {
			chassis_tx_message.StdId = MOTOR_3508_STDID;

		    chassis_can_send_data[0] = motor_data[0].tx_data >> 8;
		    chassis_can_send_data[1] = motor_data[0].tx_data;
		    chassis_can_send_data[2] = motor_data[1].tx_data >> 8;
		    chassis_can_send_data[3] = motor_data[1].tx_data;
		    chassis_can_send_data[4] = motor_data[2].tx_data >> 8;
		    chassis_can_send_data[5] = motor_data[2].tx_data;
		    chassis_can_send_data[6] = motor_data[3].tx_data >> 8;
		    chassis_can_send_data[7] = motor_data[3].tx_data;
		}
		else {
			chassis_tx_message.StdId = MOTOR_6020_STDID;

		    chassis_can_send_data[0] = motor_data[4].tx_data >> 8;
		    chassis_can_send_data[1] = motor_data[4].tx_data;
		    chassis_can_send_data[2] = motor_data[5].tx_data >> 8;
		    chassis_can_send_data[3] = motor_data[5].tx_data;
		    chassis_can_send_data[4] = motor_data[6].tx_data >> 8;
		    chassis_can_send_data[5] = motor_data[6].tx_data;
		    chassis_can_send_data[6] = motor_data[7].tx_data >> 8;
		    chassis_can_send_data[7] = motor_data[7].tx_data;
		}

	    HAL_CAN_AddTxMessage(&hcan1, &chassis_tx_message, chassis_can_send_data, &send_mail_box);
	}
}

/**
 * copy destination to origin
 */
void get_Motor_buffer(Motor* origin, Motor* destination) {
	Motor_Data_Replacement(origin, destination);
}
/**
 * copy origin to destination
 */
void set_Motor_buffer(Motor* origin, Motor* destination) {
	Motor_Data_Replacement(origin, destination);
}

/**
 * copy origin to destination this can be done by memcopy
 * need to implement critical section or Mutex
 */
void Motor_Data_Replacement(Motor* origin, Motor* destination) {
	destination->tx_data = origin->tx_data;

	destination->motor_feedback.rx_angle = origin->motor_feedback.rx_angle;
	destination->motor_feedback.rx_current = origin->motor_feedback.rx_current;
	destination->motor_feedback.rx_rpm = origin->motor_feedback.rx_rpm;
	destination->motor_feedback.rx_temp = origin->motor_feedback.rx_temp;

	destination->motor_info.stdid = origin->motor_info.stdid;

	destination->motor_info.P_prameter = origin->motor_info.P_prameter;
	destination->motor_info.I_prameter = origin->motor_info.I_prameter;
	destination->motor_info.D_prameter = origin->motor_info.D_prameter;
}
