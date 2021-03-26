#include "Motor.h"

void Motor_Data_Read() {

	uint8_t motorStatus2[8];
	for (int i=0; i<MOTOR_COUNT; i++) {
		can_filter_enable(&hcan1);

		memcpy(motorStatus2, can_rx_buffer,8);
		motor_data[i].motor_feedback.rx_angle	=(int16_t)(motorStatus2[0] << 8 | motorStatus2[1]);
		motor_data[i].motor_feedback.rx_rpm		=(int16_t)(motorStatus2[2] << 8 | motorStatus2[3]);
		motor_data[i].motor_feedback.rx_current 	=(int16_t)(motorStatus2[4] << 8 | motorStatus2[5]);
		motor_data[i].motor_feedback.rx_temp		=(int16_t)(motorStatus2[6]);
		//Current angle is absolute
		osDelay(1);

		can_filter_disable(&hcan1);
	}
}
