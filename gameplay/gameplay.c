//#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "collision.h"
#include "gameplay.h"
#include "joueur.h"
#include "../affichage/affichage.h"
#include "../affichage/console.h"
#include "../map/map.h"
#include "../moteur/frames.h"
#include "../moteur/logger.h"
#include "../main.h"

const int MOUV_X = 0;
const int MOUV_Y = 1;

const float V_MAX = 9;
const float VY_MAX = 15;

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


//Actualise tous les mouvements dans le jeu
void actualisationMouvements(joueur *j, map instanceMap)
{
    vecteur nvDelta;
    nvDelta.y = j->positionPrecise.y;
    nvDelta.x = -j->positionPrecise.x;
    char msg[100];

    sprintf(msg, "collision : %d", verifierCollisionY(j, instanceMap));
    newLog(msg);

    if (!verifierCollisionY(j, instanceMap)) {
        j->positionPrecise.y -= valeurAcceleration(j->accelY);
        j->positionPrecise.y -= valeurVitesse(j->vitesseY);
        j->position.y = round(j->positionPrecise.y);
    }

    if(!verifierCollisionX(j, instanceMap)){
        nouveauX(j);
        j->position.x = round(j->positionPrecise.x);
    }

    nvDelta.y -= j->positionPrecise.y;
    nvDelta.x += j->positionPrecise.x;

    j->deltaPos = nvDelta;
    
    sprintf(msg, "dx: %f, dy: %f", j->deltaPos.x, j->deltaPos.y);
    newLog(msg);

    sprintf(msg, "x: %d, y: %d", j->position.x, j->position.y);
    newLog(msg);

    return;

}

void mouvSaut(joueur* j)
{
    ajouterVitesse(j, 20.0, MOUV_Y);
    ajouterAcceleration(j, -g, MOUV_Y);
    afficherMessageConsole("Nouveau mouvement saut", INFOMSG);
}

void mouvDroite(joueur* j)
{
    ajouterVitesse(j, 3.0, MOUV_X);
    ajouterAcceleration(j, -1.5, MOUV_X);
    afficherMessageConsole("Nouveau mouvement droite", INFOMSG);
}

void mouvGauche(joueur* j)
{
    ajouterVitesse(j, -3.0, MOUV_X);
    ajouterAcceleration(j, 1.5, MOUV_X);
    afficherMessageConsole("Nouveau mouvement gauche", INFOMSG);

    char msg[100];
    sprintf(msg, "vx %f", j->vitesseX.valeur);
    newLog(msg);
}

void victoireJoueur(joueur* j)
{
    afficherMsgVictoire();

    //On attend une entrée utilisateur pour recommencer à jouer ou quitter le jeu
    int input;
    nodelay(stdscr, false);
    do {
        input = getch();
    } while(input != '\n' && input != 27);

    if(input == '\n')
    {
        *j = initJoueurSpawn();
        nodelay(stdscr, true);
    }
    else if(input == 27)
    {
        arretJeu();
    }
}

void mortJoueur(joueur* j)
{
    afficherMsgMort();

    //On attend une entrée utilisateur pour recommencer à jouer
    int input;
    nodelay(stdscr, false);
    do {
        input = getch();
    } while(input != '\n' && input != 27);

    if(input == '\n')
    {
        *j = initJoueurSpawn();
        nodelay(stdscr, true);
    }
    else if(input == 27)
    {
        arretJeu();
    }
    nodelay(stdscr, true);
}