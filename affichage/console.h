#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdbool.h>


extern bool consoleActive;
extern int ligneMax;

void afficherMessageConsole(char str[]);

void initConsole();

void libererMemoireConsole();

#endif
