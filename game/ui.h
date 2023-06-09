#ifndef UI
#define UI

#include <stdbool.h>

#define GAMEWIDTH 11
#define GAMEHEIGHT 9

extern char board[GAMEWIDTH][GAMEHEIGHT];

bool initUI();
void showBoard();
void cleanupUI();

#endif