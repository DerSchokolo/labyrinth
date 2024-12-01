#ifndef _MAZE_H
#define _MAZE_H

#include <stdint.h>


/**
 * Error codes
 */
#define	ERR_WALKED_INTO_WALL	1
#define	ERR_NOT_ALL_ITEMS		2


/**
 * Items in the maze.
 */
typedef enum {
	NOTHING, SPELLBOOK, POTION, WAND
} Item;

/**
 * A single maze cell with connections to other cells and (possibly) an item.
 */
typedef struct MazeCell MazeCell;
struct MazeCell {
	MazeCell* north;
	MazeCell* south;
	MazeCell* east;
	MazeCell* west;
	Item item;
};


/**
 * Creates a maze of the given dimensions. The connections between the maze
 * cells and the positions of the items are coded by the mazeArray.
 */
MazeCell* createMaze(int mazeRows, int mazeCols, const uint8_t* mazeArray);

/**
 * Checks if a given string describes a valid path out of the maze, which means
 *
 * 1) It cannot use connections between maze cells that do not exist.
 * 2) It must collect all three items in the maze.
 *
 * Example string: "WWWSNE" = go west 3x, then south, then north, then east.
 * 
 * Returns: 0, if string is a valid path.
 *          -ERR_WALKED_INTO_WALL, if path uses a connection that does not exist.
 *          -ERR_NOT_ALL_ITEMS, if path does not collect all items.
 */
int attemptEscapeFromMaze(MazeCell* startPoint, const char* solutionString);

#endif
