CC=gcc
TARGET=labyrinth
CFLAGS= -Wall -pedantic -Wextra -g

all: maze.o main.o
	${CC} ${CFLAGS} $^ -o ${TARGET}

%.o: %.c
	${CC} -c ${CFLAGS} $< -o $@

clean:
	rm -f *.o ${TARGET}

