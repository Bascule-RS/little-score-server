
# include "sys.h"
# define LONGline 100

# define DEBUG if (0) fprintf

/////////////fonction de fabrication de liste de score inspirée du cours de Algo1:
list cons_score(char * nom , int score , list liste)
{
  list triplet = malloc (sizeof (list));
  if (!triplet) printf("pas assez de RAM pour la liste");
  nom(triplet)= nom;
  score(triplet)=score;
  cdr(triplet) = liste;
  return triplet;
}

int algo_tri(list liste)
{
  //je vais avoir besoin d'une "case" liste temporaire:
  list tmp=malloc (sizeof (list));
  if (!tmp) printf("pas assez de  RAM ...\n");

  // et de deux autres cases pour le tri:
  list current =  liste;
  list index = cdr(liste);

  if (!current) return 0;
  else
  {
    while(current)
    {
      index = cdr(current);
      DEBUG (stderr,"current score :%i\tcurrent nom: %s\n",score(current),nom(current));
      while( index)
      {
        if (score(current)> score(index))
        {
          score(tmp)=score(current);
          nom(tmp)=nom(current);
          DEBUG (stderr,"tmp score :%i\ttmp nom: %s\n",score(tmp),nom(tmp));
          score(current)=score(index);
          nom(current)= nom(index);

          nom(index)=nom(tmp);
          score(index)=score(tmp);

        }
        index= cdr(index);

      }
      current = cdr(current);
    }
  }
  free(current);
  free(index);
  free(tmp);
  return 0;
}

/*
if(self.head == None):
return;
else:
while(current != None):
#Node index will point to node next to current
index = current.next;

while(index != None):
#If current node's data is greater than index's node data, swap the data between them
if(current.data > index.data):
temp = current.data;
current.data = index.data;
index.data = temp;
index = index.next;
current = current.next;*/










int
servir(int fd){
  FILE * stream;
  FILE * lecture_score;
  char buffer[100];
  char ligne[100];
  list liste_pointeur = nil;
  char * chaine_dup;

  char chaine_scan[10]={0};
  int score_scan;

  int  t;
  char nom[20];

  stream = fdopen(fd, "r+");
  if (stream == 0){
    perror("serveur fdopen");
    exit(1);
  }
  setbuf(stream, 0);

  while(fgets(buffer, sizeof buffer, stream) != 0)
  {
    if (strncmp(buffer, "SET", 3) == 0)
    {
      DEBUG(stdout,"SET bien reçu\n");
      fprintf(stream, "200 ");
    }
    ////si sscanf qui recoit ADD renvoit bien deux valeurs:
    if (sscanf(buffer, "ADD %s %d",nom, &t) == 2 )
    {

      fprintf(stream, "200 reçu ADD %s %d\n",nom, t);
      /////ouverture du fichier de scores en ecriture
      lecture_score = fopen("scores" ,"a");
      fprintf(lecture_score,"%s %d\n",nom,t);
      fclose(lecture_score);

    }
    else if (strncmp(buffer, "ASK", 3) == 0)
    {

      fprintf(stream, "200 reçu ASK\n");
      /////////ouvrir le fichier score en lecture
      lecture_score = fopen("scores" ,"r");
      /////////tant qu'il y a des lignes à lire:
      while (fgets(ligne,LONGline,lecture_score) != NULL || !feof(lecture_score))
      {
        //fabrication d'un "maillon" de la chaine
        sscanf (ligne,"%s %i",chaine_scan,&score_scan);
        chaine_dup= strdup(chaine_scan);
        printf("%s", chaine_dup);
        liste_pointeur =cons_score(chaine_dup,score_scan,liste_pointeur);

      }
      //sauvegarde du pointeur du début de la liste:
      list liste_debut= liste_pointeur;

      //tri:
      algo_tri(liste_debut);

      //impression de la liste
      while (liste_pointeur)
      {
        /////////envoyer les lignes de la liste sur le stream
        DEBUG(stderr,"nom:%s,%p\tscore:%i,%p\n",nom(liste_pointeur),nom(liste_pointeur),score(liste_pointeur),&score(liste_pointeur));
        fprintf(stream,"nom:%s\tscore:%i\n",nom(liste_pointeur),score(liste_pointeur));
        liste_pointeur=cdr(liste_pointeur);
      }


      fprintf(stream, "200 transmission scores terminée\n");

      fclose(lecture_score);
    }
    else if (strncmp(buffer, "QUIT ", 4) == 0)
    {
      fprintf(stream, "200 bye\n");
      exit(0);
    }
    else
    fprintf(stream, "500 message incorrect\n");
  }
  exit(0);
}

int
main(int ac, char * av[]){
  char * p;

  p = answerone("19986", servir);
  fprintf(stderr, "repondre a echoue: %s\n", p);
  return 1;
}
