/* ******************************************************
Nom ......... : client.c
Role ........ : client d'échanges de scores
Auteur ...... : Jean Méhat (mais largement revisité par
                Nicolas Tercé)
Version ..... : V1 .1 du 13/11/2020
Licence ..... : réalisé dans le cadre du cours de SE (IED L2)
Compilation :
gcc -Wall client.c -Dtest -o client
Pour exécuter , tapez : ./client
******************************************************* */
#include "sys.h"
#define taille_saisie 15
#define DEBUG if (0) fprintf
/* travail  --  dialogue avec le serveur */
void
travail (FILE * stream, char *order)
{
  char buffer[100];

  ////établissement de la connexion:
  fprintf (stream, "SET\n");
  if (fgets (buffer, sizeof buffer, stream) == 0)
    {
      fprintf (stderr, "client: pas moyen d'initialiser la sequence\n");
      return;
    }

  ////test d'erreur sur le stream, si le code n'est pas 200:
  if (strncmp (buffer, "200 ", 4) != 0)
    {
      fprintf (stderr, "client erreur d'établissement de connexion: recu %s",
	       buffer);
      return;
    }


  if (strncmp (buffer, "200 ", 4) == 0)
    {
      printf ("connexion établie\n");

    }

  ////ici j'ai enlevé la boucle, pour qu'il n'y ai qu'un echange:
  ////envoi de la requête sur le stream:
  fprintf (stream, order);

  DEBUG (stdout, "envoyé:'%s'\n", order);
  ////cas d'erreur de connexion
  if (fgets (buffer, sizeof buffer, stream) == 0)
    {
      DEBUG (stdout, "buffer contient:%s\n", buffer);

      fprintf (stderr, "client: connexion rompue\n");
      return;
    }
  ////reception des meilleurs scores:
  else if (strncmp (buffer, "220 reçu ASK", 12) == 0)
    {
      printf ("%s\n", buffer);
      printf
	("--------------------------\nMEILLEURS SCORES:\n--------------------------\n");
      while (fgets (buffer, sizeof buffer, stream) != NULL
	     && strcmp (strdup (buffer),
			"220 transmission scores terminée\n") != 0)
	printf ("%s", buffer);
      printf ("--------------------------\n");
      //// impression de la ligne de fin de transmission :
      printf ("%s", buffer);

      DEBUG (stdout, "EOF\n");
      return;
    }

  else if (strncmp (buffer, "220 reçu ADD", 12) == 0)
    {
      printf ("%s\n", buffer);
      printf ("Score du gagnant transféré !\n");
      return;
    }
  else if (strncmp (buffer, "220 ", 4) != 0)
    {
      fprintf (stderr, "Client: erreur, recu %s", buffer);
      return;
    }
}

////J'ai conservé cette partie :
#ifdef TEST
int
main (int ac, char *av[])
{
  int i, t;
  FILE *stream;
  char *order = "ASK\n";
  t = dial (av[1], av[2]);
  if (t < 0)
    {
      fprintf (stderr, "Pas moyen d'appeler %s\n", "localhost");
      exit (1);
    }
  stream = fdopen (t, "r+");
  if (stream == 0)
    {
      perror ("fdopen");
      exit (1);
    }
  setbuf (stream, 0);
  travail (stream, order);

  fprintf (stream, "QUIT\n");
  return 0;
}
#endif
