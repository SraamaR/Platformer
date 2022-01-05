#include <stdbool.h>

#include "../moteur/physics.h"
#include "joueur.h"
#include "../affichage/console.h"


int spawn_x = 0;
int spawn_y = 0;


/* Définit les coordonées du spawn */
void defSpawn(int x, int y) {

    spawn_x = x;
    spawn_y = y;

    return;

}

/* Initialise un joueur aux coordonnées du spawn */
joueur initJoueurSpawn() {

    joueur j;

    j.position.x = spawn_x;
    j.position.y = spawn_y;

    j.positionPrecise.x = (float) spawn_x;
    j.positionPrecise.y = (float) spawn_y;

    j.deltaPos.x = 0.0;
    j.deltaPos.y = 0.0;
    
    j.accelX.valeur = 0;
    j.accelX.tempsModif = 0;

    j.accelY.valeur = 0;
    j.accelY.tempsModif = 0;

    j.vitesseX.valeur = 0;
    j.vitesseX.tempsModif = 0;

    j.vitesseY.valeur = 0;
    j.vitesseY.tempsModif = 0;

    afficherMessageConsole("Initialisation du joueur effectuee", INFOMSG);

    return j;

}