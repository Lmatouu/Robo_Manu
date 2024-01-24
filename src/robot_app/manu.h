// manu.h

#ifndef MANU_H
#define MANU_H

/**
 * @brief Énumération représentant l'état d'un processus.
 */
typedef enum
{
    STOPPED = 0, /**< Le processus n'est pas en cours d'exécution. */
    LIVE         /**< Le processus est en cours d'exécution. C'est l'état initial */
} process_state;

/**
 * @brief Énumération représentant l'état du mouvement vers l'avant.
 */
typedef enum
{
    ARRET = 0, /**< L'état indiquant qu'il n'y a pas de mouvement vers l'avant. */
    MARCHE     /**< L'état indiquant qu'un mouvement vers l'avant est en cours. */
} move_forward_state;

/**
 * @brief Énumération représentant l'état de la détection d'obstacle.
 */
typedef enum
{
    NOTHING = 0, /**< L'état indiquant qu'aucun obstacle n'est détecté. */
    PRESENCE     /**< L'état indiquant qu'un obstacle est détecté. */
} detect_obstacle_state;

void modeManuel(process_state *running); // Fonction général qui gère le mode manuel

#endif //
