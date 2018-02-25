CC=g++
CFLAGS=
LIBS=-lsfml-graphics -lsfml-window -lsfml-system

all:
	$(CC) $(LIBS) -o lyfe main.cc