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
    map instanceMap;
    
    //Coordonées du point d'apparition
    int spawn_x = 0;
    int spawn_y = 0;

    //Initialise l'affichage et la console
    initscr();
    start_color();

    if(activerConsole == true)
    {
        initConsole();
    }
    initAffichage();

    // Initialise le compteur de frames
    initFrames(TARGET_FPS);

    //Initialise la map
    instanceMap = chargementMap();
    
    //Initialise un joueur
    posSpawnJoueur(&spawn_x, &spawn_y, instanceMap);
    joueur j = initJoueur(spawn_x, spawn_y);

    // stocke l'entrée utilisateur
    int input;

    // transforme getch en appel non-bloquant
    nodelay(stdscr, true);

    // variable compteur (compte le temps nécessaire au calculs et à l'affichage)
    clock_t start, end;

    while (enCours) 
    {
        start = clock();    // compteur de début

        affichage(j, instanceMap);

        input = getch();

        if (input == 27)    // 27 == ESC    
        { 
            enCours = false;
            afficherMessageConsole("ESC pressée", WARNMSG);
        }

        end = clock();  // compteur de fin

        napms(ecartFrameMs - (float)(start - end) / CLOCKS_PER_SEC); // attends le temps entre deux frames (moins le temps nécessaire au traitement)

        frameSuivante();
    }
    
    nodelay(stdscr, false);
    getch();

    //Arret du jeu
    if(activerConsole == true)
    {
        libererMemoireConsole();
    }
    libererMemoireAffichage();
    libererMemoireMap(instanceMap);
    endwin();

    return 0;
}