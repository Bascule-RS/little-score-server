/* client.c
Se connecter a un serveur qui calcule 3n+1
*/
# include "sys.h"
# define taille_saisie 15
# define DEBUG if (1) fprintf
/* travail  --  dialogue avec le serveur */
void
travail(FILE * stream){
  char buffer[100];
  char requete[15];

  /////établissement de la connexion:
  fprintf(stream, "SET\n");
  if (fgets(buffer, sizeof buffer, stream) == 0)
  {
    fprintf(stderr, "client: pas moyen d'initialiser la sequence\n");
    return;
  }

  /// test d'erreur sur le stream, si le code n'est pas 200:
  if (strncmp(buffer, "200 ", 4) != 0){
    fprintf(stderr, "client: recu %s", buffer);
    return;
  }


  if (strncmp(buffer, "200 ", 4) == 0){
    printf("connexion établie\n");

  }

  for(;;)
  {
    fgets (requete,taille_saisie,stdin  );
    char * strToken = strtok ( requete, " " );
     while ( strToken != NULL ) {
       if strToken
     printf ( "%s\n", strToken );
     // On demande le token suivant.
     strToken = strtok ( NULL, separators );
 }
    ///envoi de la requête sur le stream:
    fprintf(stream, requete);

    ////cas d'erreur de connexion
    if (fgets(buffer, sizeof buffer, stream) == 0){
      fprintf(stderr, "client: connexion rompue\n");
      return;
    }
    else if (strncmp(buffer, "200 reçu ASK", 12) == 0)
    {
      printf("200 Demande ASK reçue\n");
      while(fgets(buffer, sizeof buffer, stream)!=NULL && strcmp(strdup(buffer),"200 transmission scores terminée\n")!=0)
      printf("%s",buffer);
      //// impression de la ligne de fin de transmission :
      printf("%s",buffer);
      DEBUG(stdout,"EOF\n");
    }

    else if (strncmp(buffer, "200 reçu ADD", 12) == 0)
    {
      printf("200 Demande ADD reçue.\n");
    }
    else if (strncmp(buffer, "200 ", 4) != 0)
    {
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
  travail(stream);

  fprintf(stream, "QUIT\n");
  return 0;
}
