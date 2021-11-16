#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdbool.h>

extern const int ERRMSG;
extern const int WARNMSG;
extern const int INFOMSG;

extern bool consoleActive;
extern int nbLigneConsole;

void afficherMessageConsole(char str[], int msgType);

void initConsole();

void libererMemoireConsole();

#endif
