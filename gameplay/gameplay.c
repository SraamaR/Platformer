//#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>

#include "joueur.h"
#include "../affichage/affichage.h"
#include "../affichage/console.h"
#include "../map/map.h"
#include "../moteur/frames.h"
#include "../moteur/logger.h"

//Initialise un joueur aux positions (x, y)
joueur initJoueur(int x, int y)
{
    joueur j;
    j.position.x = x;
    j.position.y = y;

    j.mouvementEnCours = false;

    afficherMessageConsole("Initialisation du joueur effectuee", INFOMSG);
    /*Tests
    mvprintw(LINES / 2 - 1, 1, "x = %d", x);
    mvprintw(LINES / 2    , 1, "y = %d", y);
    */

    return j;
}

// crée un nouveau mouvement avec un vecteur vitesse de composantes vx et vy
void nouveauMouvement(joueur *j, float vx, float vy)
{

    j->mouvementEnCours = true;
    j->frameDebutMouvement = compteurFrame;
    j->mouvement.x = vx;
    j->mouvement.y = vy;
    j->positionInitiale = j->position;

    return;

}

// actualise tout les mouvement dans le jeu
void actualisation(joueur *j)
{

    if (j->mouvementEnCours == true)
    {
        coords nouvellePos = calculPosition(j->frameDebutMouvement, j->mouvement);
        nouvellePos.x = j->positionInitiale.x + nouvellePos.x;
        nouvellePos.y = j->positionInitiale.y - nouvellePos.y;
        j->position.x = nouvellePos.x;
        j->position.y = nouvellePos.y;
    }

    char msg[100];
    sprintf(msg, "x: %d, y: %d", j->position.x, j->position.y);
    newLog(msg);

    return;

}
