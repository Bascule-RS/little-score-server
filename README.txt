**********************************
TIC-TAC-TOE SCORES SERVER*********
**********************************

**********************************
COMPILATION:
just copy all the file in the directory

to compile, use makefile:
make

to launch the server:
./ser port_number

to launch the tic game client:
./tic ser_ip port_number



**********************************
NOM:

Tic-tac-toe scores server: Un jeu de tic-tac-toe avec client et serveur de scores
**********************************
SYNOPSIS:

Pour lancer le serveur:

./ser port_du_serveur

Pour lancer le client:

./tic ip_du_serveur port_du_serveur
**********************************
DESCRIPTION:

Petit jeu de tic tac toe, augmenté d'un serveur de scores qui lit les scores dans un fichier "scores".\\Pour lancer le jeu, lancer d'abord le serveur en précisant le port découte en argument. Lancer ensuite le client sur l'ip et le port d'ecoute du serveur.
Coté Client, renseigner les noms des joueurs en début de partie.
Chaque joueur joue l'un après l'autre en indiquant le chiffre de sa case de jeu (compris entre  0 et 8). \textbf{Faire bien attention à mettre un chiffre}.
En fin de partie le menu permet:

 1. De recupérer la liste des scores du serveur.
 2. D'envoyer le score du vainqueur au serveur.
 3. De recommencer un partie avec les mêmes noms de joueurs
 4. De quitter la partie

Coté serveur le déroulement des échanges est décrit.
**********************************
ORGINIAL AUTHOR:

Suraj Singh Bisht
https://www.bitforestinfo.com/2019/01/create-simple-tic-tac-toe-game-in-pure.html

**********************************
AUTHOR OF THIS SERVER UPGRADE:

nterce@gmail.com
16/11/2020
