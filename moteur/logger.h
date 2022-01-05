#ifndef LOGGER_H
#define LOGGER_H

/* logger : permet d'ecrire dans un .txt des messageList d'erreurs et de deboguer le programme (version developpement) */


/* Ouvre le fichier de log */
void initLogFile();

/* ajoute un message au fichier de log */
void newLog(char* message);

/* referme le fichier de log */
void closeLogFile();


#endif
