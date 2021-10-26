#define TARGET_FPS 60

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "affichage/affichage.h"
#include "affichage/console.h"
#include "gameplay/gameplay.h"
#include "map/map.h"
#include "moteur/frames.h"


int main() 
{
    //Declaration variables
    bool enCours = true;
    bool activerConsole = true;
    char* map = NULL;

    // Initialise le compteur de frames
    initFrames(TARGET_FPS);

    //Initialise l'affichage et la console

    initscr();
    if (activerConsole)
    {
        initConsole();
    }
    initAffichage();

    //Initialise la map
    chargementMap(map);
    
    //Initialise un joueur
    joueur j = initJoueur();

    // stocke l'entrée utilisateur
    int input;

    // transforme getch en appel non-bloquant
    nodelay(stdscr, true);

    // variable compteur (compte le temps nécessaire au calculs et à l'affichage)
    clock_t start, end;

    while (enCours) 
    {
        start = clock(); // compteur de début

        affichage(j);

        input = getch();

        if (input == 27) { // 27 == ESC
            
            enCours = false;

        }


        end = clock(); // compteur de fin

        napms(ecartFrameMs - (float)(start - end) / CLOCKS_PER_SEC); // attends le temps entre deux frames (moins le temps nécessaire au traitement)

        frameSuivante();
    }
    
    //Arret du jeu

    if (map != NULL)
    {
        free(map);
    }

    libererMemoireConsole();

    endwin();
    return 0;
}
