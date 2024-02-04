/**
 * hello robot main program
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

#include "robot_app/robot.h"
#include "robot_app/pilot.h"
#include "robot_app/manu.h"

#define TEMPO 2000000

#define POLLING_PERIOD 10000

static void robot_loop(void);

/* global variable used for program clean exit */
static process_state running = LIVE;

/**
 * Function for CTRL+C signal management
 */
static void sigint_handler(int dummy)
{
	running = STOPPED;
}

int main(void)
{

	if (robot_start() == -1)
	{
		return EXIT_FAILURE;
	}

	/* Interception d'un Ctrl+C pour arrêter le programme proprement. */
	signal(SIGINT, sigint_handler);

	/* Procédure hello de manipulation du robot. */
	robot_loop();

	/* Arrêt du robot. */
	robot_stop();

	return EXIT_SUCCESS;
}

/**
 * Robot control function
 *
 * Send commands to the robot and display status data with a specific period
 */
static void robot_loop()
{
	while (running)
	{
		modeManuel(&running);
	}
}
