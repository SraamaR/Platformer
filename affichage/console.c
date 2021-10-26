#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../moteur/frames.h"

// console : permet d'afficher les messageList d'erreurs et de deboguer le programme (version developpement)

const int INFOMSG = 50;
const int ERRMSG = 51;
const int WARNMSG = 52;


typedef struct messageConsole {

    int timeFrame;
    int messageType;
    char *msg;

} messageConsole;


bool consoleActive = false;
WINDOW *console;


int ligneMax = 0; // Nombre de ligne console
int ligneConsole = 0; // Ligne actuelle
const int ligneMaxMemoire = 50; // Nombre de ligne maximum en mémoire

messageConsole messageList[50];


void afficherMessageConsole(char* str, int msgType)
{

    if(consoleActive == false)
    {

        return;

    }

    // On nettoie la fenêtre
    wclear(console);

    // On détermine le nombre de lignes à afficher
    int nbreLigneAffichage = ligneMax;

    if(ligneConsole < ligneMax)
    {

        nbreLigneAffichage = ligneConsole;

    }

    messageList[ligneConsole].msg = str;
    messageList[ligneConsole].timeFrame = compteurFrame;
    messageList[ligneConsole].messageType = msgType;

    for (int i = 0; i <= nbreLigneAffichage; i++)
    {
        wattron(console, COLOR_PAIR(messageList[ligneConsole - nbreLigneAffichage + i].messageType));

        wprintw(console, "%d : %s", messageList[ligneConsole - nbreLigneAffichage + i].timeFrame, messageList[ligneConsole - nbreLigneAffichage + i].msg);

        wprintw(console, "\n");

        wattroff(console, COLOR_PAIR(messageList[ligneConsole - nbreLigneAffichage + i].messageType));
        wrefresh(console);

    }
   
    ligneConsole++;
    

    return;

}


void initConsole()
{

    ligneMax = LINES / 6;
    console = subwin(stdscr, ligneMax + 1, COLS, 0, 0);

    init_pair(INFOMSG, COLOR_CYAN, COLOR_BLACK);
    init_pair(ERRMSG, COLOR_RED, COLOR_BLACK);
    init_pair(WARNMSG, COLOR_YELLOW, COLOR_BLACK);

    int xMax = getmaxx(console);

    consoleActive = true;
    afficherMessageConsole("Initialisation de la console effectuee", INFOMSG);

    return;

}

