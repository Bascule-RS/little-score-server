/* n-dial.c
 Renvoie une connexion vers un serveur, ou -1 en utilisant IPv4
 */
# include "sys.h"

int
dial(char * machine, char * port){
  struct addrinfo * info, * p;
  struct addrinfo indices;
  int toserver, t;

  memset(&indices, 0, sizeof indices);
  indices.ai_family = AF_INET;       // seulement IPv4
  indices.ai_socktype = SOCK_STREAM; // seulement TCP

  t = getaddrinfo(machine, port, &indices, &info);
  if (t != 0)			// erreur
    return -1;

  // trouver une adresse qui fonctionne dans les reponses
  for(p = info; p != 0; p = p->ai_next){
    toserver = socket(p->ai_family, p->ai_socktype, 0);
    if (toserver >= 0)
      break;
  }
  if (p == 0) // rien ne marche
    return -1;

  // la connecter
  t = connect(toserver, info->ai_addr, info->ai_addrlen);
  if (t < 0){
    freeaddrinfo(info);
    close(toserver);
    return -1;
  }

  freeaddrinfo(info);
  return toserver;
}

# if DEBUG
int
main(int ac, char * av[]){
  char buffer[1];
  int t, fd = dial(av[1], av[2]);

  while((t = read(0, buffer, sizeof buffer)) > 0){
    write(fd, buffer, t);
    t = read(fd, buffer, sizeof buffer);
    write(1, buffer, t);
  }
  return 0;
}
# endif
