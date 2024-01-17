// robot.h

#ifndef ROBOT_H
#define ROBOT_H

#include "mrpiz.h"
#include "../utils.h"
//#include "pilot.h"

/**
 * @brief Structure of speed;
 */
typedef int speed_pct;

/**
 * @brief Enum of wheel;
 */

typedef enum {
	LEFT_WHEEL=0,
	RIGHT_WHEEL=1,
	BOOTH_WHEEL=2
} wheel;

/**
 * @brief Structure of robot status;
 */
typedef struct{	
	int left_encoder;
	int right_encoder;
	int left_sensor;
	int center_sensor;
	int right_sensor;
	int battery;
}robot_status;


/**
 * @brief Enum of wheel;
 */

typedef enum{
	ROBOT_OK =0,
	ROBOT_OBSTACLE=1,
	ROBOT_PROBLEM=2
}notifications;

int robot_start ();
void robot_set_speed(speed_pct ,speed_pct);
int robot_get_wheel_position(wheel);
void robot_reset_wheel_pos();
robot_status robot_get_status();
void robot_signal_event(notifications);
void robot_stop();

#endif // ROBOT_H
