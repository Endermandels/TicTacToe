#ifndef MODEL
#define MODEL

#include <stdbool.h>

#define BOARDWIDTH 3
#define BOARDHEIGHT 3

void initBoard();
void placeX(int x, int y);
void placeO(int x, int y);
bool xInBounds(int x);
bool yInBounds(int y);
bool gameWon();

#endif