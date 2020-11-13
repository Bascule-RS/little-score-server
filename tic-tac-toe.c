





/* ******************************************************
Nom ......... : tic-tac-toe.c
Role ........ : petit jeu tic-tac-toe agrémenté d'une fonction
client/serveur pour les scores
Auteur ...... : Suraj Singh Bisht (mais revisité par Nicolas Tercé)
Version ..... : V1 .1 du 10/11/2020
Licence ..... : réalisé dans le cadre du cours de SE (IED L2)
Compilation :
gcc -Wall tic-tac.c -o tic-tac
Pour exécuter , tapez : ./tic-tac
******************************************************* */

//Modules
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "sys.h"

#define PLAYERFIRST 'X'
#define PLAYERSECOND 'O'
#define taille_saisie 100
# define DEBUG if (0) fprintf
// tableau du damier:
char s[10] = {'.','.','.','.','.','.','.','.','.'};
int turn=0;

// 0 1 2
// 3 4 5
// 6 7 8

int prompt(int win);
int ask_name(void);
int status(char p);
char * color_print(char p);
void displayboard(void);
int player(char p);
void
travail(FILE * stream, char * order);
int appel(char * order);
int detect_space(char * chaine);

char saisie[taille_saisie] = {0};
char * pointeur_nom;
struct player{char * name; int score ;} ;

struct player player1;//= malloc (sizeof(player));
struct player player2;//= malloc (sizeof(player));

int detect_space(char * chaine)
{
  int i = 0;
  char *pointeur=strtok(chaine,"\n");
  if (strlen(chaine) > 10) (chaine[10]=0);
  pointeur= chaine;
  while(*pointeur)
  {
    if (*pointeur == ' ') pointeur[0]='_';
    pointeur+=1;
  }

  DEBUG(stdout,"chaine modifiée :%s\n",chaine);

  return 0;

}

int ask_name(void){
  printf("veuillez entrer le nom du joueur1 [");
  color_print(PLAYERFIRST);
  printf("] (10 carctères maximum):\n");
  fgets(saisie,taille_saisie,stdin);
  detect_space(saisie);
  player1.name =strdup(saisie);
  player1.score = 0;

  printf("veuillez entrer le nom du joueur2 [");
  color_print(PLAYERSECOND);
  printf("] (10 carctères maximum):\n");
  fgets(saisie,taille_saisie,stdin);
  detect_space(saisie);
  player2.name =strdup(saisie);
  player2.score = 0;

  return 0;
}

// fonction qui verifie qu'aucun joueur n'a gagné
int status(char p){
  //conditions d'une victoire
  if


    ((s[0]==s[1] && s[1]==s[2] && s[0]==p)||(s[3]==s[4] && s[4]==s[5] &&
    s[5]==p)||(s[6]==s[7] && s[7]==s[8] && s[8]==p)||(s[0]==s[3] &&
    s[3]==s[6] && s[6]==p)||(s[1]==s[4] && s[4]==s[7] && s[7]==p)||(s[2]==s[5]
    && s[5]==s[8] && s[8]==p)||(s[0]==s[4] && s[4]==s[8] && s[8]==p)||(s[6]==s[4]
    && s[4]==s[2] && s[2]==p))
  {  return 1;
  }
  else
  {
    return 0;
  }
}

////fonction d'impression en couleur en fonction du caractère:
////qui renvoie le nom du joueur en fonction du caractère
char * color_print(char p)
{
  if ((int)p==(int)PLAYERFIRST)
  {
    // print about player
    printf("\x1B[48;5;%dm%c\x1B[0m",21,p);
    return player1.name;
  }
  else if ((int)p==(int)PLAYERSECOND)
  {
    printf("\x1B[48;5;%dm%c\x1B[0m",88,p);
    return player2.name;
  }
  else printf("\x1B[0m%c",p);
  return 0;
}
//fonction d'affichage du "plateau" de jeu (revisité pour y mettre de la couleur)
void displayboard(void){
  // netoyage de l'ecran:
  system("clear");
  // impression du tableau
  printf("\n\n");
  color_print(s[0]);
  printf(" | ");
  color_print(s[1]);
  printf(" | ");
  color_print(s[2]);
  printf("---->   0 | 1 | 2 \n-------------\n");
  color_print(s[3]);
  printf(" | ");
  color_print(s[4]);
  printf(" | ");
  color_print(s[5]);
  printf("---->   3 | 4 | 5 \n-------------\n");
  color_print(s[6]);
  printf(" | ");
  color_print(s[7]);
  printf(" | ");
  color_print(s[8]);
  printf("---->   6 | 7 | 8  \n\n\n");
}

// verification du tableau:
int checkinput(int i){
  if (i<9){
    if(s[i]=='.'){
      return 1;}
      return 0;
    };return 0;
  }


  // jeu d'un joueur:
  int player(char p){
    int ret=0;
    // impression du plateau
    displayboard();
    // Input value space
    int i;
    // print about player
    printf("[+] Le joueur des ");
    pointeur_nom = color_print(p);
    printf(" %s",pointeur_nom);
    printf(", c'est ton tour\n[+] Insère ton nombre d'index pour placer ton coup");

    do{
      // scan variable
      scanf("%d", &i);
    }while( !isdigit(i) && !checkinput(i) );
    // Insert mark
    s[i]=p;
    turn += 1;
    displayboard();
    if(turn==9){
      printf("[-] Game Tie.\n");
      status(p);
      exit(0);
    }
    if(status(p)){
      printf("!!Winner!!,%s  ",pointeur_nom);
      color_print(p);
      printf(" est le gagnant.\n");
      return 5;
    };

    printf("[+]Joueur %s ",pointeur_nom);
    color_print(p);
    printf(", ton jeu est accepté : %d , Tour de jeu No. %d",i, turn);
    // return value
    return ret;
  };

  // Trigger
  int main(){
    ////rajout:variable du gagnant:
    int win= 0;
    int reponse;
    displayboard();
    ask_name();
    // Display Status

    // while loop










    while(1){
      displayboard();
      while(win==0){
        // first player turn
        if(player(PLAYERFIRST)){
          player1.score +=10;
          win=1;
          break;
        };
        // second player turn
        if(player(PLAYERSECOND)){
          player2.score +=10;
          win=2;
          break;
        };

      };
      while(win!=0)
      {
        turn =prompt(win);
        if (turn==3)
        {

          sprintf (s,".........");
          turn =0;
          win=0;
          break;}
        }
      }


      exit(0);
    };

    int prompt(int win)
    {

      int reponse;
      char order[20]={0} ;
      printf("**************************\n");
      printf("Résultats du jeu:\n%s:%i\t%s:%i\n",player1.name,player1.score,player2.name,player2.score);
      printf("**************************\nMenu:\n**************************\nVeuillez faire votre choix.\nMeilleurs scores.1\nAjouter le score.2\nNouvelle partie.3\nQuitter.4\n?");
      scanf("%d",&reponse);
      if (reponse ==1)
      {
        displayboard();
        printf("Connexion au serveur des meilleurs scores...\n");


        sprintf(order,"ASK\n");
        appel(order);
        return 1;
      }
      else if (reponse ==2)
      {printf("Ajout du score...\n");
      displayboard();
      if (win==1)
      sprintf(order,"ADD %s %i\n",player1.name,player1.score);
      if (win==2)
      sprintf(order,"ADD %s %i\n",player2.name,player2.score);

      appel(order);
      return 2;}
      else if (reponse ==3)
      {
        printf("Nouvelle partie.\n");
        return 3;
      }
      else if (reponse ==4)
      {
        printf("Merci, Au revoir!\n");
        exit(0);
      }
      else return 5;
    }

    int appel(char * order)
    {
      int t;
      FILE * stream;

      t = dial("192.168.1.16", "19986");
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
      travail(stream,order);


      return 0;
    }
