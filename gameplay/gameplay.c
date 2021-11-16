//#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "joueur.h"
#include "../affichage/affichage.h"
#include "../affichage/console.h"
#include "../map/map.h"
#include "../moteur/frames.h"
#include "../moteur/logger.h"

const int MOUV_X = 0;
const int MOUV_Y = 1;

const float V_MAX = 6;
const float VY_MAX = 15;

//Initialise un joueur aux positions (x, y)
joueur initJoueur(int x, int y)
{
    joueur j;
    j.position.x = x;
    j.position.y = y;
    j.positionPrecise.x = x;
    j.positionPrecise.y = y;

    j.accelX.valeur = 0;
    j.accelY.valeur = 0;
    j.vitesseX.valeur = 0;
    j.vitesseY.valeur = 0;

    afficherMessageConsole("Initialisation du joueur effectuee", INFOMSG);
    /*Tests
    mvprintw(LINES / 2 - 1, 1, "x = %d", x);
    mvprintw(LINES / 2    , 1, "y = %d", y);
    */

    return j;
}

// crée un nouveau mouvement avec un vecteur vitesse de composantes vx et vy
void ajouterVitesse(joueur *j, float valeur, int type)
{

    if (type == MOUV_X)
    {
        j->vitesseX.valeur += valeur;

        // la vitesse est nulle si on change de sens subitement
        if ((j->vitesseX.valeur < 0 && valeur > 0) || (j->vitesseX.valeur > 0 && valeur < 0))
        {
            j->vitesseX.valeur = 0;
        }

        // on limite la vitesse, si supérieure on la met au max
        if (j->vitesseX.valeur > V_MAX) 
        {
            j->vitesseX.valeur = V_MAX;
        }
        if (j-> vitesseX.valeur < -V_MAX)
        {
            j->vitesseX.valeur = -V_MAX;
        }


        j->vitesseX.tempsModif = compteurFrame;
    } 
    else if (type == MOUV_Y)
    {
            j->vitesseY.valeur = valeur;
            j->vitesseY.tempsModif = compteurFrame;

            if ((j->vitesseY.valeur < 0 && valeur > 0) || (j->vitesseY.valeur > 0 && valeur < 0))
            {
                j->vitesseY.valeur = 0;
            }

            // on limite la vitesse, si supérieure on la met au max
            if (j->vitesseY.valeur > VY_MAX) 
            {
                j->vitesseY.valeur = VY_MAX;
            }
            if (j-> vitesseY.valeur < -VY_MAX)
            {
                j->vitesseY.valeur = -VY_MAX;
            }
    }

    return;

}

void ajouterAcceleration(joueur *j, float valeur, int type)
{
    if (type == MOUV_X)
    {
        j->accelX.valeur = valeur;
        j->accelX.tempsModif = compteurFrame;
    }
    else if (type == MOUV_Y && j->accelY.valeur == 0)
    {
        j->accelY.valeur = valeur;
        j->accelY.tempsModif = compteurFrame;
    }

    return;
}


void nouveauX(joueur *j){

    float vx = valeurVitesse(j->vitesseX);
    float ax = valeurAcceleration(j->accelX);

    if (vx > 0){
        if (vx + ax > 0) // si la décélération + le mouvement crée par la vitesse va toujours dans le sens du mouvement, on continue
        {
            j->positionPrecise.x += vx + ax;
        } else { // sinon on arrête le mouvement
            j->vitesseX.valeur = 0;
            j->accelX.valeur = 0;
        }
    } else if (vx < 0)
    {
        if (vx + ax < 0) // si la décélération + le mouvement crée par la vitesse va toujours dans le sens du mouvement, on continue
        {
            j->positionPrecise.x += vx + ax;
        } else { // sinon on arrête le mouvement
            j->vitesseX.valeur = 0;
            j->accelX.valeur = 0;
        }
    }

}

void checkCollision(joueur *j)
{

    // TODO : vérifier si collision et arrêter les mouvement correspondants

}

// actualise tout les mouvement dans le jeu
void actualisation(joueur *j)
{

    j->positionPrecise.y -= valeurVitesse(j->vitesseY);
    j->positionPrecise.y -= valeurAcceleration(j->accelY);

    nouveauX(j);

    j->position.x = round(j->positionPrecise.x);
    j->position.y = round(j->positionPrecise.y);

    checkCollision(j);

    char msg[100];
    sprintf(msg, "x: %d, y: %d", j->position.x, j->position.y);
    newLog(msg);

    return;

}
