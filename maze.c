#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "maze.h"

/** HINWEIS: Um die Aufgabe zu loesen, m�ssen Sie diesen Code nicht lesen und
 * nicht verstehen!
 */
int attemptEscapeFromMaze(MazeCell *startPoint, const char *solutionString) {
  bool wandFound = false, bookFound = false, potionFound = false;
  MazeCell *currentPos = startPoint;

  for (size_t i = 0; i < strlen(solutionString); i++) {
    if (solutionString[i] == 'N' && &currentPos->north != NULL) {
      currentPos = currentPos->north;
    } else if (solutionString[i] == 'E' && currentPos->east != NULL) {
      currentPos = currentPos->east;
    } else if (solutionString[i] == 'S' && currentPos->south != NULL) {
      currentPos = currentPos->south;
    } else if (solutionString[i] == 'W' && currentPos->west != NULL) {
      currentPos = currentPos->west;
    } else {
      return -ERR_WALKED_INTO_WALL;
    }

    if (currentPos->item == WAND) {
      wandFound = true;
    } else if (currentPos->item == POTION) {
      potionFound = true;
    } else if (currentPos->item == SPELLBOOK) {
      bookFound = true;
    }
  }

  if (wandFound && potionFound && bookFound)
    return 0;
  else
    return -ERR_NOT_ALL_ITEMS;
}

/** HINWEIS: Um die Aufgabe zu l�sen, m�ssen Sie diesen Code nicht lesen und
 * auch nicht verstehen!
 */
MazeCell *createMaze(int mazeRows, int mazeCols, const uint8_t *mazeArray) {
  MazeCell *maze = calloc(mazeRows * mazeCols, sizeof(MazeCell));
  if (maze == NULL) {
    printf("Fehler beim Allokieren des Speichers.\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < mazeRows; i++) {
    for (int j = 0; j < mazeCols; j++) {
      MazeCell *cell = maze + i * mazeCols + j;
      uint8_t cellSetup = mazeArray[i * mazeCols + j];

      /* Set connections to surrounding cells */
      if (cellSetup & (1 << 4) && i != 0) {
        cell->north = maze + (i - 1) * mazeCols + j;
      }
      if (cellSetup & (1 << 5) && j != mazeCols - 1) {
        cell->east = maze + i * mazeCols + j + 1;
      }
      if (cellSetup & (1 << 6) && i != mazeRows - 1) {
        cell->south = maze + (i + 1) * mazeCols + j;
      }
      if (cellSetup & (1 << 7) && j != 0) {
        cell->west = maze + i * mazeCols + j - 1;
      }

      /* Set item */
      if (cellSetup & (1 << 1)) {
        cell->item = WAND;
      } else if (cellSetup & (1 << 2)) {
        cell->item = POTION;
      } else if (cellSetup & (1 << 3)) {
        cell->item = SPELLBOOK;
      }
    }
  }

  return maze;
}
