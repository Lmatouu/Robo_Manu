// robot.c

#include "robot.h"
#include "mrpiz.h"



extern int robot_start (){
	return mrpiz_init();
}

extern void robot_set_speed( speed_pct left,speed_pct right){
	mrpiz_motor_set(MRPIZ_MOTOR_LEFT, left);
	mrpiz_motor_set(MRPIZ_MOTOR_RIGHT, right);
}

extern int robot_get_wheel_position(wheel wheell){
	return mrpiz_motor_encoder_get(wheell);
}

extern void robot_reset_wheel_pos(){
	mrpiz_motor_encoder_reset(MRPIZ_MOTOR_BOTH);
}

extern robot_status robot_get_status(){
	robot_status resultat;

	resultat.left_encoder=mrpiz_motor_encoder_get(MRPIZ_MOTOR_LEFT);
	resultat.right_encoder=mrpiz_motor_encoder_get(MRPIZ_MOTOR_RIGHT);
	resultat.left_sensor=mrpiz_proxy_sensor_get(MRPIZ_PROXY_SENSOR_FRONT_LEFT);
	resultat.center_sensor=mrpiz_proxy_sensor_get(MRPIZ_PROXY_SENSOR_FRONT_CENTER);
	resultat.right_sensor=mrpiz_proxy_sensor_get(MRPIZ_PROXY_SENSOR_FRONT_RIGHT);
	resultat.battery=mrpiz_battery_level();

	return resultat;
}

extern void robot_signal_event (notifications event){
	switch (event)
	{
	case ROBOT_OK:
		mrpiz_led_rgb_set(MRPIZ_LED_GREEN );
		break;
		
	case ROBOT_OBSTACLE:
		mrpiz_led_rgb_set(MRPIZ_LED_BLUE	);
		break;

	/* ROBOT_PROBLEM */
	default: 
		mrpiz_led_rgb_set(MRPIZ_LED_RED);
		break;
	}
	
}

extern void robot_stop(){
	mrpiz_motor_set(MRPIZ_MOTOR_BOTH, 0);
}