#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../moteur/frames.h"
#include "../moteur/logger.h"

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

int nbLigneConsole = 0; // Nombre de ligne console
int ligneDernierMsg = 0; // Ligne du dernier message

messageConsole messageList[5]; // on stocke les messages (5 lignes max)

void afficherMessageConsole(char* str, int msgType)
{
    if(!consoleActive)
    {
        return;
    }

    // Si on a atteint le max de la console, on décale d'un rang les messages
    if (ligneDernierMsg == 5)
    {
        for(int i = 0; i < 4; i++)
        {
            messageList[i].messageType = messageList[i+1].messageType;
            messageList[i].timeFrame = messageList[i+1].timeFrame;
            strncpy(messageList[i].msg, messageList[i+1].msg, COLS * sizeof(char));
        }
    }


    if (ligneDernierMsg < 5) 
    {
        ligneDernierMsg++;
    }

    // ajoute le message dans le log
    newLog(str);

    strncpy(messageList[ligneDernierMsg - 1].msg, str, COLS * sizeof(char));
    messageList[ligneDernierMsg - 1].timeFrame = compteurFrame;
    messageList[ligneDernierMsg - 1].messageType = msgType;

    // On nettoie la fenêtre
    wclear(console);


    for (int i = 0; i < ligneDernierMsg; i++)
    {
        wattron(console, COLOR_PAIR(messageList[i].messageType));
        wprintw(console, "%d : %s", messageList[i].timeFrame, messageList[i].msg);
        wprintw(console, "\n");
        wattroff(console, COLOR_PAIR(messageList[i].messageType));

        wrefresh(console);
    }


    return;
}

void initConsole()
{
    nbLigneConsole = LINES / 6;

    if (nbLigneConsole > 5)
    {
        nbLigneConsole = 5; // on limite la taille de la console a 5 messages (peut être moins si l'écran est petit)
    }

    for (int i = 0; i < 5; i++)
    {
        messageList[i].msg = malloc(COLS * sizeof(char)); // on prepare des strings du nombre de caractère que peut contenir l'écran
    }

    console = subwin(stdscr, nbLigneConsole, COLS, 0, 0);

    init_pair(INFOMSG, COLOR_CYAN, COLOR_BLACK);
    init_pair(ERRMSG, COLOR_RED, COLOR_BLACK);
    init_pair(WARNMSG, COLOR_YELLOW, COLOR_BLACK);

    consoleActive = true;
    afficherMessageConsole("Initialisation de la console effectuee", INFOMSG);

    return;
}

void libererMemoireConsole()
{
    delwin(console);

    return;
}
