#define TARGET_FPS 60 // nombre de fps visé (defaut : 60)
#define DEVMODE true // active le mode développeur (console + log)

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
#include "gameplay/joueur.h"

//Cette variable est vraie tant que le jeu est en marche
bool enCours = true;

int main()
{
    initCurses();
    
    //Le menu est affiché jusqu'à que le joueur presse une touche
    afficherMenu();
    getch();

    //On débute l'initialisation du jeu en effaçant le menu
    clear();

    //Initialise l'affichage du jeu et la console
    if(DEVMODE)
    {
        initConsole();
        initLogFile();
    }
    initAffichageJeu();

    //Initialise le compteur de frames
    initFrames(TARGET_FPS);

    //Initialise la map
    map instanceMap;
    instanceMap = chargementMap();
    
    //Initialise le joueur
    int spawn_x = 0;
    int spawn_y = 0;
    int x_fin = posFin(instanceMap);
    posSpawnJoueur(&spawn_x, &spawn_y, instanceMap);
    defSpawn(spawn_x, spawn_y);
    joueur j = initJoueurSpawn();

    //Transforme getch en appel non-bloquant
    nodelay(stdscr, true);

    //Autorise l'utilisation des flèches
    keypad(stdscr, true);

    //Variable compteur (compte le temps nécessaire au calculs et à l'affichage)
    clock_t start, end;

    while (enCours) 
    {
        start = clock();    // compteur de début

        actualisationMouvements(&j, instanceMap);

        affichageJeu(j, instanceMap);

        // Envoi puis traitement de l'entrée utilisateur
        inputControle(getch(), &enCours, &j);

        if (j.position.x >= x_fin) {
            victoireJoueur(&j);
        }

        end = clock();  // compteur de fin

        napms(ecartFrameMs - 1000 * (float)(end - start) / CLOCKS_PER_SEC); // attends le temps entre deux frames (moins le temps nécessaire au traitement)
        frameSuivante();
    }

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

void arretJeu()
{
    afficherMessageConsole("Arrêt du jeu...", INFOMSG);
    enCours = false;
}