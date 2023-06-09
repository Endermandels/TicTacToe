/*
Board elements
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model.h"
#include "ui.h"

#define BOARDX (GAMEWIDTH/2 - BOARDWIDTH/2)
#define BOARDY (GAMEWIDTH/2 - BOARDHEIGHT/2)

char board[GAMEWIDTH][GAMEHEIGHT];

bool xInBounds(int x);
bool yInBounds(int y);

void initBoard() {
    for (int xx = 0; xx < GAMEWIDTH; xx++) {
        for (int yy = 0; yy < GAMEHEIGHT; yy++) {
            if (xInBounds(xx) && yInBounds(yy)) {
                board[xx][yy] = ' ';
                continue;
            }
            board[xx][yy] = '-';
        }
    }
}

void placeX(int x, int y) {
    board[x][y] = 'X';
}

void placeO(int x, int y) {
    board[x][y] = 'O';
}

bool xInBounds(int x) {
    return x >= BOARDX && x < BOARDX + BOARDWIDTH;
}

bool yInBounds(int y) {
    return y >= BOARDY && y < BOARDY + BOARDHEIGHT;
}

bool gameWon() {
    // Check for all scenarios
    if (board[BOARDX][BOARDY] == 'X') {
        return true;
    }

    return false;
}
