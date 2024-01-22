//manu.C

#include <stdio.h>
#include <ctype.h>
#include <termios.h>
#include <unistd.h>
#include <pilot.h>
#include <manu.h>


// Test Mathis GitHub
int etat_verrouillage = 0;
static robot_status my_status;


move tab_move_forward[1]={
{FORWARD,{3},60}
};
move tab_move_right[1]={
{ROTATION,{RIGHT},50}
};
move tab_move_left[1]={
{ROTATION,{LEFT},50}
};
move tab_u_turn[1]={
{ROTATION,{U_TURN},50}
};




/**
 * @brief Permet de faire avancer le robot tout droit
 *
 */
void manu_go_forward() {
    printf("La touche Z a été appuyée.\n");
    // Ajoutez ici le code que vous souhaitez exécuter pour la touche Z
	pilot_start_move( tab_move_forward[0] );

	while(pilot_get_status() != DONE){
	pilot_stop_at_target();
    
}
}

/**
 * @brief Permet de faire tourner le robot à 90° à gauche
 *
 */
void manu_turn_left() {
    printf("La touche Q a été appuyée.\n");
    // Ajoutez ici le code que vous souhaitez exécuter pour la touche Q
	pilot_start_move( tab_move_left[0] );

	while(pilot_get_status() != DONE){
	pilot_stop_at_target();
}
}

/**
 * @brief Permet de faire tourner le robot à 180° à droite
 *
 */
void manu_U_turn() {
printf("La touche S a été appuyée.\n");
// Ajoutez ici le code que vous souhaitez exécuter pour la touche S

pilot_start_move( tab_u_turn[0]);

while(pilot_get_status() != DONE){
pilot_stop_at_target();
}
}

/**
 * @brief Permet de faire tourner le robot à 90° à droite
 *
 */
void manu_turn_right() {
    printf("La touche D a été appuyée.\n");
    // Ajoutez ici le code que vous souhaitez exécuter pour la touche D
	pilot_start_move( tab_move_right[0]);

	while(pilot_get_status() != DONE){
	pilot_stop_at_target();
}
}

/**
 * @brief Permet d'activer ou désactiver l'arrêt d'urgence
 *
 */
void manu_lock(int *etat_verrouillage) {
    if(*etat_verrouillage == 1){
        *etat_verrouillage = 0;
        printf("Désactivé. Etat : %d\n", *etat_verrouillage);
    } else {
        *etat_verrouillage = 1;
        printf("Activé. Etat : %d\n", *etat_verrouillage);
    }
}

/**
 * @brief Permet d'afficher les différentes informations du Robot
 *
 */
void manu_display_info() {
    my_status = robot_get_status();
    printf("\033[1;4mInformations du Robot :\033[0m\n");
    fprintf(stdout, "Codeurs: g = %d, d = %d\n", my_status.left_encoder, my_status.right_encoder);
    fprintf(stdout, "Proxy: g = %d, c = %d, d = %d\n", my_status.left_sensor, my_status.center_sensor, my_status.right_sensor);
    fprintf(stdout, "Batterie: %d %%\n", my_status.battery);
}

// /**
//  * @brief Permet de modifier la valeur de la vitesse
//  * PROBLEME LIE AU L'INITIALISATION
//  */
// void manu_change_speed(int *vitesse) {
//     int value = 0;
//     int min = 0;
//     int max = 100;
//     do {
//         printf("Vous avez demandé le changement de la vitesse.\n");
//         printf("Vitesse actuelle %d.\n",&vitesse);
//         printf("Veuillez entrer la nouvelle vitesse comprise entre %d et %d\n", min, max);
//         scanf("%d", &value); // version cracra et non sécurisée
//         getchar();           // pour se débarasser du retour ligne
//         if((value < min) || (value > max)){
//             printf("Valeur non correct.");
//         }
//     } while ((value < min) || (value > max));
//     printf("La nouvelle valeur de la vitesse est %d",&vitesse);
//     *vitesse = value;
// }

/**
 * @brief Permet d'afficher les différentes interactions possibles avec la console en mode Manuel
 *
 */
void manu_display_menu() {
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
 * @brief Permet de configurer le mode sans tampon
 *
 */
void setBufferedInput(int enable) {
    static struct termios oldt, newt;
    static int isFirstCall = 1;  // Variable pour suivre le premier appel

    if (!enable && isFirstCall) {
        printf("Bonjour, vous entrez en mode Manuel.\nPour plus d'information, cliquez sur 'M'\n");
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        isFirstCall = 0;  // Met à jour la variable pour indiquer que le premier appel a été fait
    } else if (enable) {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}


/**
 * @brief Permet de lancer le mode manuel 
 *
 */

void modeManuel(process_state *running){
    char key;

    setBufferedInput(0); // Désactive le tampon d'entrée pour obtenir un caractère immédiatement

    key = toupper(getchar());

    switch (key) {
        case 'Z': // Touche Z pour aller devant
        if(etat_verrouillage == 0){
            manu_go_forward();
        }
            break;

        case 'Q': // Touche Q pour mode verrouillage
        if(etat_verrouillage == 0){
            manu_turn_left();
        }  
            break;

		case 'S': // Touche S pour faire le debut tour
		if(etat_verrouillage == 0){
		manu_U_turn();
		}
			break;
		
        case 'D': // Touche D pour mode verrouillage
        if(etat_verrouillage == 0){
            manu_turn_right();
        }
            break;

        case ' ': // Touche Esc pour mode verrouillage
            manu_lock(&etat_verrouillage);
            break;

		case 'O': // Touche O pour quitter le mode manuel
			setBufferedInput(1); // Réactive le tampon d'entrée pour obtenir un caractère immédiatement
			*running = 0; // Met à jour la variable running dans la classe principale
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
