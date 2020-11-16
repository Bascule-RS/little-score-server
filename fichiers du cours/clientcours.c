/* client.c
 Se connecter a un serveur qui calcule 3n+1
 */
# include "sys.h"

/* travail  --  dialogue avec le serveur */
void
travail(FILE * stream, int v){
  char buffer[100];

  fprintf(stream, "SET %d\n", v);
  if (fgets(buffer, sizeof buffer, stream) == 0){
    fprintf(stderr, "client: pas moyen d'initialiser la sequence\n");
    return;
  }
  if (strncmp(buffer, "200 ", 4) != 0){
    fprintf(stderr, "client: recu %s", buffer);
    return;
  }

  while(v != 1){
    printf("%d ", v);
    fprintf(stream, "NEXT\n");
    if (fgets(buffer, sizeof buffer, stream) == 0){
      fprintf(stderr, "client: connexion rompue\n");
      return;
    }
    if (sscanf(buffer, "200 valeur %d", &v) != 1){
      fprintf(stderr, "client: erreur, recu %s", buffer);
      return;
    }
  }
  printf("1 \n");
}
    
int
main(int ac, char * av[]){
  int i, t;
  FILE * stream;

  t = dial("localhost", "19986");
  if (t < 0){
    fprintf(stderr, "Pas moyen d'appeler %s\n", "localhost");
    exit(1);
  }
  stream = fdopen(t, "r+");
  if (stream == 0){
    perror("fdopen");
    exit(1);
  }
  setbuf(stream, 0);		/* pas de buffer */

  for(i = 1; i < ac; i++)
    travail(stream, atoi(av[i]));

  fprintf(stream, "QUIT\n");
  return 0;
}
