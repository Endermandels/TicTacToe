#ifndef UI
#define UI

#include <stdbool.h>

#define GAMEWIDTH 9
#define GAMEHEIGHT 9

extern char board[GAMEWIDTH][GAMEHEIGHT];

bool initUI();
void showBoard();
void userInput();
void cleanupUI();

#endif