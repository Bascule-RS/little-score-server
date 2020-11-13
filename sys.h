/* sys.h
Inclure
 */
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <stdio.h>
# include <netdb.h>
# include <unistd.h>
# include <ctype.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <assert.h>

////////////primitives pour la liste de codes

typedef struct Nom_score {char* nom ; int score ; struct Nom_score * cdr ;} * list ;       // la structure de base ; list est un pointeur sur un doublet

#define nom(Nom_score) ((Nom_score)->nom)
#define score(Nom_score) ((Nom_score)->score)
#define cdr(Nom_score) ((Nom_score)->cdr)
#define nil NULL

list cons_score(char * nom , int score , list liste);
int dial(char * host, char * port);          // dans dial.c
char *answersync(char * port, int (*fun)(int));
