// manu.C
/**
 * @file manu.c
 * @authors Mathis VEBER & Kilian GUÉRY
 * @brief Classe permettant de contrôler avec le clavier le Robot sur le Simulateur
 * @version 0.3
 * @date 2024-01-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <ctype.h>
#include <termios.h>
#include <unistd.h>
#include <pilot.h>
#include <manu.h>
#include <sys/select.h> // Pour select(), FD_ZERO(), FD_SET(), fd_set
#include <sys/time.h>   // Pour struct timeval

#define SENSOR_THRESHOLD 120

int etat_verrouillage = 0; // Booleen pour le bouton verrouiller

static robot_status my_status;

static move_forward_state state_forward = ARRET; // Booleen pour l'état du déplacement

static detect_obstacle_state state_obstacle = NOTHING;

// Mouvement pour aller tout droit
move tab_move_forward[1] = {
    {FORWARD, {3}, 60}};

// Mouvement pour tourner à droite
move tab_move_right[1] = {
    {ROTATION, {RIGHT}, 50}};

// Mouvement pour tourner à gauche
move tab_move_left[1] = {
    {ROTATION, {LEFT}, 50}};

// Mouvement pour faire demi-tour
move tab_u_turn[1] = {
    {ROTATION, {U_TURN}, 50}};

/**
 * @version 3
 * 
 * @brief Permet de faire avancer le robot tout droit avce obstacle
 */
void manu_go_forward()
{
    printf("La touche Z a été appuyée.\n");
    //===== Déplacement du Robot =====
    if (state_forward == ARRET) // Vérifie si le Robot était à l'arrêt
    {
        state_forward = MARCHE;                // Changement d'état
        pilot_start_move(tab_move_forward[0]); // Déplacer le Robot
    }
    else // Vérifie si le Robot était en marche
    {
        pilot_stop();
        state_forward = ARRET;
    }
}

/**
 * @version 2
 * 
 * @brief Permet de faire tourner le robot à 90° à gauche
 */
void manu_turn_left()
{
    pilot_stop(); // Arrêter le Robot pour pouvoir le faire tourner
    printf("La touche Q a été appuyée.\n");
    pilot_start_move(tab_move_left[0]); // Faire tourner le Robot à gauche

    // ===== Tourner à 90° à gauche =====
    while (pilot_get_status() != DONE)
    {
        pilot_stop_at_target();
    }

    if (state_forward == MARCHE) // Si le Robot était en marche, continuer son déplacement
    {
        pilot_start_move(tab_move_forward[0]);
    }
}

/**
 * @version 2
 * 
 * @brief Permet de faire tourner le robot à 180° à droite
 */
void manu_U_turn()
{
    pilot_stop(); // Arrêter le Robot pour pouvoir le faire tourner
    printf("La touche S a été appuyée.\n");
    pilot_start_move(tab_u_turn[0]); // Faire tourner le Robot pour faire demi-tour

    // ===== Tourner à 180° =====
    while (pilot_get_status() != DONE)
    {
        pilot_stop_at_target();
    }

    if (state_forward == MARCHE) // Si le Robot était en marche, continuer son déplacement
    {
        pilot_start_move(tab_move_forward[0]);
    }
}

/**
 * @version 2
 * 
 * @brief Permet de faire tourner le robot à 90° à droite
 */
void manu_turn_right()
{
    pilot_stop(); // Arrêter le Robot pour pouvoir le faire tourner
    printf("La touche D a été appuyée.\n");
    pilot_start_move(tab_move_right[0]); // Faire tourner le Robot à droite

    // ===== Tourner à 90° à droite =====
    while (pilot_get_status() != DONE)
    {
        pilot_stop_at_target();
    }

    if (state_forward == MARCHE) // Si le Robot était en marche, continuer son déplacement
    {
        pilot_start_move(tab_move_forward[0]);
    }
}

/**
 * @version 1
 * 
 * @brief Permet d'activer ou désactiver l'arrêt d'urgence
 */
void manu_lock(int *etat_verrouillage)
{
    // ===== Bouton Verrouillage =====
    if (*etat_verrouillage == 1) // Désactive le bouton verrouillage
    {
        *etat_verrouillage = 0;
        printf("Désactivé. Etat : %d\n", *etat_verrouillage);
    }
    else // Active le bouton verrouillage
    {
        *etat_verrouillage = 1;
        printf("Activé. Etat : %d\n", *etat_verrouillage);
    }
}

/**
 * @version 1
 * 
 * @brief Permet d'afficher les différentes informations du Robot
 */
void manu_display_info()
{
    my_status = robot_get_status();
    printf("\033[1;4mInformations du Robot :\033[0m\n");

    // Information sur les codeurs des roues : gauche et droite
    fprintf(stdout, "Codeurs: g = %d, d = %d\n", my_status.left_encoder, my_status.right_encoder);
    // Information sur les proxys/capteurs : gauche, centre et droite
    fprintf(stdout, "Proxy: g = %d, c = %d, d = %d\n", my_status.left_sensor, my_status.center_sensor, my_status.right_sensor);
    // Information sur la batterie
    fprintf(stdout, "Batterie: %d %%\n", my_status.battery);
}

/**
 * @version 1
 * 
 * @brief Permet d'afficher les différentes interactions possibles avec la console en mode Manuel
 */
void manu_display_menu()
{
    // ===== Affichage du Menu =====
    printf("\n=================MENU=================\n");
    printf("\033[1;4mDéplacement du Robot\033[0m\n");
    printf("\033[1m'Z'\033[0m permet de faire avancer le Robot\n");
    printf("\033[1m'Q'\033[0m permet de faire tourner le Robot de 90° à gauche\n");
    printf("\033[1m'D'\033[0m permet de faire tourner le Robot de 90° à droite\n");
    printf("\033[1m'S'\033[0m permet de faire tourner le Robot de 180°\n");
    printf("\033[1;4mAffichage d'information\033[0m\n");
    printf("\033[1m'M'\033[0m permet d'afficher les différentes interactions possibles avec la console\n");
    printf("\033[1m'I'\033[0m permet d'afficher les informations liées au Robot'\n");
    printf("\033[1;4mModification\033[0m\n");
    printf("\033[1m'V'\033[0m permet de modifier la vitesse du Robot\n");
}

/**
 * @author Intelligence Artificielle
 *
 * @version 1
 * 
 * @brief Permet de configurer le mode sans tampon
 */
void setBufferedInput(int enable)
{
    static struct termios oldt, newt;
    static int isFirstCall = 1; // Variable pour suivre le premier appel

    if (!enable && isFirstCall)
    {
        printf("Bonjour, vous entrez en mode Manuel.\nPour plus d'information, cliquez sur 'M'\n");
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        isFirstCall = 0; // Met à jour la variable pour indiquer que le premier appel a été fait
    }
    else if (enable)
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}

/**
 * @author Intelligence Artificielle
 *
 * @version 1
 * 
 * @brief Permet de lire un caractère sans bloquer
 *
 * @return int caractère voulue sinon -1
 */
int non_blocking_getc(void)
{
    struct timeval tv = {0L, 50000L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    if (select(1, &fds, NULL, NULL, &tv))
    {
        return getchar();
    }
    else
    {
        return -1;
    }
}

/**
 * @authors Mathis VEBER & Kilian GUÉRY
 *
 * @version 1
 * 
 * @brief Permet de lancer le mode manuel
 */

void modeManuel(process_state *running)
{
    char key;

    setBufferedInput(0); // Désactive le tampon d'entrée pour obtenir un caractère immédiatement

    key = toupper(non_blocking_getc());

    robot_status my_status = robot_get_status();
    if (my_status.center_sensor < SENSOR_THRESHOLD)
    {
        state_obstacle = PRESENCE;

        if (state_forward == MARCHE)
        {
            pilot_stop();
            state_forward = ARRET;
        }
    }
    else
    {
        state_obstacle = NOTHING;
    }

    switch (key)
    {
    case 'Z': // Touche Z pour aller devant
        if (etat_verrouillage == 0  && state_obstacle == NOTHING)
        {
            manu_go_forward();
        }
        break;

    case 'Q': // Touche Q pour mode verrouillage
        if (etat_verrouillage == 0)
        {
            manu_turn_left();
        }
        break;

    case 'S': // Touche S pour faire le debut tour
        if (etat_verrouillage == 0)
        {
            manu_U_turn();
        }
        break;

    case 'D': // Touche D pour mode verrouillage
        if (etat_verrouillage == 0)
        {
            manu_turn_right();
        }
        break;

    case ' ': // Touche Esc pour mode verrouillage
        manu_lock(&etat_verrouillage);
        break;

    case 'O':                // Touche O pour quitter le mode manuel
        setBufferedInput(1); // Réactive le tampon d'entrée pour obtenir un caractère immédiatement
        *running = 0;        // Met à jour la variable running dans la classe principale
        break;

    case 'M': // Touche M pour afficher le menu
        manu_display_menu();
        break;

    case 'I': // Touche M pour afficher le menu
        manu_display_info();
        break;

    default:
        break;
    }
}