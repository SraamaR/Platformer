#include <stdbool.h>
#include "../moteur/physics.h"
#include "joueur.h"
#include "../affichage/console.h"

//Initialise un joueur aux positions (x, y)
joueur initJoueur(int x, int y)
{
    joueur j;
    j.position.x = x;
    j.position.y = y;
    j.positionPrecise.x = (float) x;
    j.positionPrecise.y = (float) y;
    j.deltaPos.x = 0.0;
    j.deltaPos.y = 0.0;
    
    j.accelX.valeur = 0;
    j.accelY.valeur = 0;
    j.vitesseX.valeur = 0;
    j.vitesseY.valeur = 0;

    afficherMessageConsole("Initialisation du joueur effectuee", INFOMSG);

    return j;
}
