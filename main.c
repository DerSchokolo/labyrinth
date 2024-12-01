#include <stdio.h>
#include <stdlib.h>

#include "maze.h"


#define	MAZE_ROWS	3
#define	MAZE_COLS	3

const uint8_t maze_array[MAZE_ROWS * MAZE_COLS] = { 0x60, 0x81, 0x48, \
													0x70, 0xA0, 0xD0, \
													0x30, 0x84, 0x12 };


int main() {
	MazeCell* startPoint = createMaze(MAZE_ROWS, MAZE_COLS, maze_array);

	char pathToFreedom[] = "SSEWNEENSS";
	int result = attemptEscapeFromMaze(startPoint, pathToFreedom);
	if (result == 0) {
		printf("Hurra! Du bist aus dem Labyrinth entkommen!\n");
	}
	else if (result == -ERR_NOT_ALL_ITEMS) {
		printf("Du versuchst zu zaubern, aber irgendwas fehlt...\n");
	}
	else if (result == -ERR_WALKED_INTO_WALL) {
		printf("Aua! Da ist eine Wand!\n");
	}

	free(startPoint);
	return 0;
}
