
CC = gcc
CFLAGS = -Wall -g
SOURCES = sha1.c
OBJECTS = sha1.o

all: sha1 sha1_parts

	
sha1: sha1.c sha.c sha1.h
	$(CC) $(SOURCES) $(CFLAGS) sha.c -o sha1
sha1_parts: sha1.c sha_parts.c sha1.h
	$(CC) $(SOURCES) $(CFLAGS) sha_parts.c -o sha_parts


clean:
	rm -rf *.o sha sha_parts a.out *.gch
