#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../gameplay/joueur.h"
#include "./console.h"

WINDOW *jeu;


void affichage(joueur j)
{
    int xMax, yMax;
    getmaxyx(jeu, yMax, xMax);

    mvwprintw(jeu, yMax / 2, xMax / 2 - 5, "Affichage");

    wrefresh(jeu);
}


// Initialise l'affichage
void initAffichage()
{
    //On choisit la bonne taille en fonction de la présence de la console
    if(consoleActive == true)
    {

        jeu = subwin(stdscr, LINES - ligneMax - 1, COLS, ligneMax + 1, 0);

    }
    
    else
    {

        jeu = subwin(stdscr, LINES, COLS, 0, 0);

    }

    //Contour blanc
    box(jeu, ACS_VLINE, ACS_HLINE);
    
    int xMax = getmaxx(jeu);
    mvwprintw(jeu, 1, xMax / 2 - 5, "Platformer");

    afficherMessageConsole("Initialisation de l'affichage effectuee", INFOMSG);

    return;

}
