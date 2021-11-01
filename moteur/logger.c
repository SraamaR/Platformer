#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../affichage/console.h"
#include "./frames.h"

FILE* logFile; // fichier de log

void initLogFile() // ouvre le fichier de log
{

    logFile = fopen("./log.txt", "w");

    if (logFile == NULL)
    {
        afficherMessageConsole("Erreur lors de l'ouverture du fichier de log", ERRMSG);
    } 
    else {
        time_t t = time(NULL);
        struct tm tActuel = *localtime(&t);
        fprintf(logFile, "Platformer %d:%d\n", tActuel.tm_hour, tActuel.tm_min);
        
        afficherMessageConsole("Fichier de log ouvert correctement", INFOMSG);
    }

    return;

}

void newLog(char* message) // ajoute un message au fichier de log
{

    if (logFile != NULL)
    {
        fprintf(logFile, "%d : %s \n", compteurFrame, message);
    }

    return;

}

void closeLogFile() // referme le fichier de log
{

    if (logFile != NULL)
    {
        fclose(logFile);
    }

    return;

}
