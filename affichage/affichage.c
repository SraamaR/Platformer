#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../gameplay/joueur.h"

WINDOW *jeu;

//Console
bool consoleActive = false;
WINDOW *console;

int ligneMax = 0; //Nombre de ligne console
int ligneConsole = 0; //Ligne actuelle

const int ligneMaxMemoire = 50; //Nombre de ligne maximum en mémoire

char** texteConsole = NULL; //Le texte à afficher

void afficherMessageConsole(const char* str)
{
    if(consoleActive == false)
    {
        return;
    }

    //On nettoie la fenêtre
    wclear(console);

    //On détermine le nombre de lignes à afficher
    int nbreLigneAffichage = ligneMax;
    if(ligneConsole < ligneMax)
    {
        nbreLigneAffichage = ligneConsole;
    }

    texteConsole[ligneConsole] = str;
    for (int i = 0; i <= nbreLigneAffichage; i++)
    {
        wprintw(console, texteConsole[ligneConsole - nbreLigneAffichage + i]);
        wprintw(console, "\n");
    }
   
    ligneConsole++;
    wrefresh(console);
}

void initConsole()
{
    ligneMax = LINES / 6;
    console = subwin(stdscr, ligneMax + 1, COLS, 0, 0);

    int xMax = getmaxx(console);
    
    texteConsole = malloc(ligneMaxMemoire * (xMax * sizeof(char)));
    if(texteConsole == NULL)
    {
        afficherMessageConsole("Erreur d'allocation mémoire");
        return;
    }

    consoleActive = true;
    afficherMessageConsole("Initialisation de la console effectuee");
}

void affichage(joueur j)
{
    int xMax, yMax;
    getmaxyx(jeu, yMax, xMax);

    mvwprintw(jeu, yMax / 2, xMax / 2 - 5, "Affichage");

    wrefresh(jeu);
}

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

    afficherMessageConsole("Initialisation de l'affichage effectuee");
}

void libererMemoireAffichage()
{
    if(consoleActive == true)
    {
        free(texteConsole);
    }
}