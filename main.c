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
    map map;

    //Initialise l'affichage et la console

    initscr();
    start_color();

    if (activerConsole)
    {
        initConsole();
    }
    initAffichage();

    // Initialise le compteur de frames
    initFrames(TARGET_FPS);

    //Initialise la map
    map = chargementMap();
    
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

        affichage(j, map);

        input = getch();

        if (input == 27) { // 27 == ESC
            
            enCours = false;
            afficherMessageConsole("ESC pressée", WARNMSG);

        }


        end = clock(); // compteur de fin

        napms(ecartFrameMs - (float)(start - end) / CLOCKS_PER_SEC); // attends le temps entre deux frames (moins le temps nécessaire au traitement)

        frameSuivante();
    }
    
    //Arret du jeu
    libererMemoireMap(map);

    nodelay(stdscr, false);
    getch();

    endwin();
    return 0;
}