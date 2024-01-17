// MANU.h

#ifndef MANU_H
#define MANU_H

/* Custom type for process state management */
typedef enum{
	STOPPED = 0,
	LIVE
}process_state;

void modeManuel(process_state *running);

#endif // MANU_H
