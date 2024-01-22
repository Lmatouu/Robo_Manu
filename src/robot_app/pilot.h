// pilot.h

#ifndef PILOT_H
#define PILOT_H

#include "robot.h"
#include "../utils.h"


/**
 * @brief Enumeration representing the status of a move.
 */
typedef enum {
	IDLE,					/**< Move as not started. */
	IN_PROGRESS,      /**< Move is in progress. */
	DONE,					/**< Target is reached. */
	OBSTACLE   			/**< Obstacle encountered. */
} move_status;

/**
 * @brief Enumeration representing the type of a move.
 */
typedef enum {
	FORWARD,
	ROTATION
} move_type;

/**
 * @brief Enumeration representing the rotation angles available.
 */
typedef enum {
	NONE,
	LEFT,
	RIGHT,
	U_TURN
} angle;



/**
 * @brief Structure of a move, members distance or range share an union and are used depending on move_type;
 */
typedef struct {
	move_type type;
	union {
		int distance;
		angle angle;
	}range;
	speed_pct speed;
}move;

/**
 * @brief Initiates a move.
 *
 * @param a_move The move to be initiated.
 */
extern void pilot_start_move(move a_move);

/**
 * @brief Stops the robot when target is reached.
 *
 * @return The status of the move.
 */
extern move_status pilot_stop_at_target(void);

/**
 * @brief Return the current move status.
 *
 * @return The status of the current move.
 */
extern move_status pilot_get_status(void);

/**
 * @brief Stop the robot and change move status to DONE.
 *
 */
extern void pilot_stop(void);

#endif // PILOT_H
