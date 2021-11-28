#define TARGET_FPS 60 // nombre de fps visé (defaut : 60)
#define DEVMODE false // active le mode développeur (console + log)

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "affichage/affichage.h"
#include "affichage/console.h"
#include "gameplay/gameplay.h"
#include "map/map.h"
#include "moteur/frames.h"
#include "moteur/logger.h"
#include "moteur/input.h"

int main() 
{
    //Declaration variables
    bool enCours = true;
    map instanceMap;
    
    //Coordonées du point d'apparition
    int spawn_x = 0;
    int spawn_y = 0;

    //Initialise l'affichage et la console
    initscr();
    start_color();
    curs_set(0); //Curseur invisible

    if(DEVMODE)
    {
        initConsole();
        initLogFile();
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

    // autorise l'utilisation des flèches
    keypad(stdscr, true);

    // variable compteur (compte le temps nécessaire au calculs et à l'affichage)
    clock_t start, end;

    while (enCours) 
    {
        start = clock();    // compteur de début

        actualisation(&j);

        affichage(j, instanceMap);

        input = getch();

        inputControle(input, &enCours, &j); // gère l'entrée utilisateur

        end = clock();  // compteur de fin

        napms(ecartFrameMs - (float)(start - end) / CLOCKS_PER_SEC); // attends le temps entre deux frames (moins le temps nécessaire au traitement)

        frameSuivante();
    }
    
    nodelay(stdscr, false);
    getch();

    //Arret du jeu
    if(DEVMODE)
    {
        libererMemoireConsole();
        closeLogFile();
    }
    libererMemoireAffichage();
    libererMemoireMap(instanceMap);
    endwin();

    return 0;
}