#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../moteur/frames.h"
#include "../moteur/logger.h"

bool consoleActive = false;
WINDOW* console;

int nbLigneConsole = 0;  // Nombre de ligne console
int ligneDernierMsg = 0; // Ligne du dernier message

const int INFOMSG = 50;
const int ERRMSG = 51;
const int WARNMSG = 52;
const int CRASHMSG = 53;

const int LONGUEUR_MAX_MSG = 256;

typedef struct messageConsole {

    int timeFrame;
    int messageType;
    char *msg;

} messageConsole;

messageConsole messageList[5]; // on stocke les messages (5 lignes max)

/* Nettoie le contenu des messages de la console */
void clearConsole(){

    ligneDernierMsg = 0;
    wclear(console);

    for (int i = 0; i < 5; i++)
    {
        messageList[i].msg[0] = '\0';
        for(int k = 1; k < LONGUEUR_MAX_MSG - 1; k++)
        {
            messageList[i].msg[k] = ' ';
        }
    }

}

/* Initialise la fenêtre ncurses de la console */
void initFenetreConsole() {

    nbLigneConsole = LINES / 6;

    if (nbLigneConsole > 5) {
        nbLigneConsole = 5; // on limite la taille de la console a 5 messages (peut être moins si l'écran est petit)
    }

    console = subwin(stdscr, nbLigneConsole, COLS, 3, 0);

    ligneDernierMsg = 0;

    return;

}

/* Initialise la console */
void initConsole() {

    for (int i = 0; i < 5; i++) {
    
        messageList[i].msg = malloc(LONGUEUR_MAX_MSG * sizeof(char)); // on prepare des strings du nombre de caractère que peut contenir l'écran
        messageList[i].msg[0] = '\0';
    
    }
    clearConsole();

    init_pair(INFOMSG, COLOR_CYAN, COLOR_BLACK);
    init_pair(ERRMSG, COLOR_RED, COLOR_BLACK);
    init_pair(WARNMSG, COLOR_YELLOW, COLOR_BLACK);

    consoleActive = true;

    initFenetreConsole();

    return;
}


/* Affiche un message dans la console 
Préconditions : 
- La chaîne de charactères termine par la sentinelle 
- Longueur du message (sentinelle incluse) <= LONGUEUR_MAX_CONSOLE
*/
void afficherMessageConsole(char *str, int msgType) {

    // Affichage des messages de crash
    if (msgType == CRASHMSG) {
    
        clear();
    
        printw(str);
        printw("\n");
    
        refresh();
    
        return;
    
    }

    if (!consoleActive) {
        return;
    }

    // Calcule la longueur du message pour éviter un dépassement de tableau
    if(strlen(str) >= LONGUEUR_MAX_MSG) {
        afficherMessageConsole("Message trop long", WARNMSG);
    }

    // Si on a atteint le max de la console, on décale d'un rang les messages
    if (ligneDernierMsg == nbLigneConsole) {
    
        ligneDernierMsg = nbLigneConsole;
        for (int i = 0; i < nbLigneConsole - 1; i++) {
        
            messageList[i].messageType = messageList[i + 1].messageType;
            messageList[i].timeFrame = messageList[i + 1].timeFrame;
            strncpy(messageList[i].msg, messageList[i + 1].msg, LONGUEUR_MAX_MSG * sizeof(char));
        
        }
        
    }
    else if (ligneDernierMsg < nbLigneConsole) {
        ligneDernierMsg++;
    }

    // Ajoute le message dans le log
    nouveauLog(str);

    strncpy(messageList[ligneDernierMsg - 1].msg, str, COLS * sizeof(char));
    messageList[ligneDernierMsg - 1].timeFrame = compteurFrame;
    messageList[ligneDernierMsg - 1].messageType = msgType;

    // On nettoie la fenêtre
    werase(console);

    for (int i = 0; i < nbLigneConsole; i++) {
    
        if(messageList[i].msg[0] != '\0') {
        
            wattron(console, COLOR_PAIR(messageList[i].messageType));
            wprintw(console, "%d : %s", messageList[i].timeFrame, messageList[i].msg);
            wprintw(console, "\n");
            wattroff(console, COLOR_PAIR(messageList[i].messageType));
        
        }
    
    }

    wrefresh(console);

    return;
}

/* Libère la mémoire de la console */
void libererMemoireConsole() {

    delwin(console);
    for (int i = 0; i < 5; i++) {
        free(messageList[i].msg);
    }

    return;

}
