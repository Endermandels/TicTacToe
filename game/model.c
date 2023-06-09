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

bool gameWon(char player) {
    // Horizontals
    for (int ii = 0; ii < 3; ii++) {
        if (board[BOARDX][BOARDY+ii] == player && board[BOARDX+1][BOARDY+ii] == player && board[BOARDX+2][BOARDY+ii] == player) {
            return true;
        }
    }

    // Verticals
    for (int ii = 0; ii < 3; ii++) {
        if (board[BOARDX+ii][BOARDY] == player && board[BOARDX+ii][BOARDY+1] == player && board[BOARDX+ii][BOARDY+2] == player) {
            return true;
        }
    }

    // Diagonal Top Left
    if (board[BOARDX][BOARDY] == player && board[BOARDX+1][BOARDY+1] == player && board[BOARDX+2][BOARDY+2] == player) {
        return true;
    }

    // Diagonal Top Right
    if (board[BOARDX+2][BOARDY] == player && board[BOARDX+1][BOARDY+1] == player && board[BOARDX][BOARDY+2] == player) {
        return true;
    }

    return false;
}

bool tie() {
    for (int ii = 0; ii < 3; ii++) {
        for (int jj = 0; jj < 3; jj++) {
            if (board[BOARDX+ii][BOARDY+jj] == ' ') return false;
        }
    }
    return true;
}
