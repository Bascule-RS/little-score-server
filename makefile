CC=gcc
CFLAGS=-Wall
LDFLAGS=
EXEC=tic

all: $(EXEC)

tic:tic-tac-toe.c client2.c n-dial.c
	$(CC) $^ -o $@ $(CFLAGS)

ser:serveur2.c n-answersync.c
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -f *.o core
