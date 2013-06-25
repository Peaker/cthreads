CFLAGS=-g -Wall
CFILES=main.c threads32.c

main: ${CFILES} threads.h threads_private.h
	gcc -o $@ ${CFLAGS} ${CFILES}
