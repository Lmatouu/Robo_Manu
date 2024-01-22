// pilot.c

#include "pilot.h"
#include "stdio.h"

#define FORWARD_STEP 142
#define ANGLE_STEP 221

#define SENSOR_THRESHOLD 120

static move_status robot_moving = DONE;
static int target_pos = 0;
static wheel reference_wheel = LEFT_WHEEL;

extern void pilot_start_move(move my_move)
{

	if (robot_moving != IN_PROGRESS)
	{
		switch (my_move.type)
		{
		case FORWARD:
			/*TODO: choose a reference encoder, compute the adequate target encoder value, set the robot in motion */

			reference_wheel = LEFT_WHEEL;
			target_pos = my_move.range.distance * FORWARD_STEP + robot_get_wheel_position(reference_wheel);
			robot_set_speed(my_move.speed, my_move.speed);
			break;

		case ROTATION:
			switch (my_move.range.angle)
			{
			case NONE:
				return;
				break;

			case LEFT:
				reference_wheel = RIGHT_WHEEL;
				target_pos = ANGLE_STEP + robot_get_wheel_position(reference_wheel);
				robot_set_speed(-my_move.speed, my_move.speed);
				break;

			case RIGHT:
				reference_wheel = LEFT_WHEEL;
				target_pos = ANGLE_STEP + robot_get_wheel_position(reference_wheel);
				robot_set_speed(my_move.speed, -my_move.speed);
				break;

			case U_TURN:
				reference_wheel = RIGHT_WHEEL;
				target_pos = ANGLE_STEP * 2 + robot_get_wheel_position(reference_wheel);
				robot_set_speed(-my_move.speed, my_move.speed);
				break;
			}
			break;

		default:
			TRACE("default case reached");
			break;
		}
		switch (robot_moving)
		{
		case IDLE:
			TRACE("move status cannot be IDLE");
			break;
		case DONE:
			robot_signal_event(ROBOT_OK);
			break;
		case OBSTACLE:
			robot_signal_event(ROBOT_OBSTACLE);
			break;
		case IN_PROGRESS:
			TRACE("move status cannot be IN_PROGRESS here");
			break;
		default:
			TRACE("default case reached");
			break;
		}
		robot_moving = IN_PROGRESS;
	}
}

extern move_status pilot_stop_at_target(void)
{
	robot_status my_status = robot_get_status();
	if (my_status.center_sensor < SENSOR_THRESHOLD)
	{
		robot_moving = OBSTACLE;
	}
	if (robot_get_wheel_position(reference_wheel) > target_pos && pilot_get_status() != DONE)
	{
		robot_stop();
		robot_moving = DONE;
	}
	return robot_moving;
}

extern move_status pilot_get_status(void)
{
	return robot_moving;
}

extern void pilot_stop(void)
{
	{
		robot_stop();
		robot_moving = DONE;
	}
}