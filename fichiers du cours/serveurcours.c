/* serveur.c
 Faire tourner une fois 3n+1
 */
# include "sys.h"

int
servir(int fd){
  FILE * stream;
  char buffer[100];
  int valeur, t;

  stream = fdopen(fd, "r+");
  if (stream == 0){
    perror("serveur fdopen");
    exit(1);
  }
  setbuf(stream, 0);

  while(fgets(buffer, sizeof buffer, stream) != 0){
    if (sscanf(buffer, "SET %d", &t) == 1 && t > 0){
      valeur = t;
      fprintf(stream, "200 valeur %d\n", t);
    } else if (strncmp(buffer, "NEXT", 4) == 0){
      if (valeur % 2 == 0)
	valeur /= 2;
      else
	valeur = 3 * valeur + 1;
      fprintf(stream, "200 valeur %d\n", valeur);
    } else if (strncmp(buffer, "QUIT ", 4) == 0){
      fprintf(stream, "200 bye\n");
      exit(0);
    } else
      fprintf(stream, "500 message incorrect\n");
  }
  exit(0);
}

int
main(int ac, char * av[]){
  char * p;

  p = answer("19986", servir);
  fprintf(stderr, "repondre a echoue: %s\n", p);
  return 1;
}
