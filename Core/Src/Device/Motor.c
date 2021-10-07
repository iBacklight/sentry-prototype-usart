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

	destination->motor_info.P_parameter = origin->motor_info.P_parameter;
	destination->motor_info.I_parameter = origin->motor_info.I_parameter;
	destination->motor_info.D_parameter = origin->motor_info.D_parameter;
}


//PID Function, expects a POINTER to motor structure, target ABSOLUTE angle in DEGREES (between 0 and 360), and P/I/D parameters
void Motor_pid_set_angle(Motor* motor, double angle, int32_t p, int32_t i, int32_t d){
	Motor temp_motor_buffer;
	int16_t rx_angle;
	int16_t input_angle;
	int16_t current_error;
	int16_t target_angle;
	int16_t min_speed=1000;
	int16_t tolerance=20;
	int16_t direction=1;
	double velocity=0;
	double speed=0;

	input_angle=round(angle/360*8192);

	get_Motor_buffer(motor, &temp_motor_buffer);


	temp_motor_buffer.motor_info.P_parameter=p;
	temp_motor_buffer.motor_info.I_parameter=i;
	temp_motor_buffer.motor_info.D_parameter=d;
	rx_angle=temp_motor_buffer.motor_feedback.rx_angle;

	target_angle=input_angle;
	/*if (target_angle % 8192 !=0){
		target_angle=target_angle%8192;
	}*/

	current_error=abs(target_angle-rx_angle);

	//Few decisions to make with statements below
	//If error is small enough, then velocity=0 (motor doesn't turn)
	//If error is not small, but motor turns less than 180 degrees, turn as per usual using p*error
	//If error is not small, but motor needs to turn more than 180 degrees, reverse direction, and error is the error "the other way"
	//In cases where error is not small, set minimum speed so that the motor doesnt stop turning due to friction

	////----------------------------This seciton will likely need to be modified if we try to add in I and D control--------------------////
	if (current_error<tolerance){
		velocity=0;
	}
	else{
		if (current_error<=4096){
			direction=1;

			speed=p*current_error;

			if (speed<min_speed){
				speed=min_speed;
			}

			velocity=direction*speed;
		}
		else{
			current_error=abs(current_error-8192);
			direction=-1;

			speed=p*current_error;

			if (speed<min_speed){
				speed=min_speed;
			}

			velocity=direction*speed;
		}

	}

	////----------------------------This seciton will likely need to be modified if we try to add in I and D control--------------------////
	//current_error=3000;



	temp_motor_buffer.tx_data=velocity;
	set_Motor_buffer(&temp_motor_buffer,motor);

}

//Sets a raw value to a motor - look at datasheets to see what values the motor supports
void Motor_set_raw_value(Motor* motor, double value){
	Motor temp_motor_buffer;
	get_Motor_buffer(motor, &temp_motor_buffer);
	temp_motor_buffer.tx_data=value;
	set_Motor_buffer(&temp_motor_buffer,motor);
}
