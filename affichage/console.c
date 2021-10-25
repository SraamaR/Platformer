#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

// console : permet d'afficher les messages d'erreurs et de deboguer le programme (version developpement)

bool consoleActive = false;
WINDOW *console;

int ligneMax = 0; //Nombre de ligne console
int ligneConsole = 0; //Ligne actuelle

const int ligneMaxMemoire = 50; //Nombre de ligne maximum en mémoire

char** texteConsole = NULL; //Le texte à afficher

void afficherMessageConsole(char* str)
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

    return;

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

    return;

}

void libererMemoireConsole()
{
    if(consoleActive == true)
    {

        free(texteConsole);

    }

    return;

}
