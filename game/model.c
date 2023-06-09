/*
Board elements
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model.h"
#include "ui.h"

char board[GAMEWIDTH][GAMEHEIGHT];

void initBoard() {
    for (int xx = 0; xx < GAMEWIDTH; xx++) {
        for (int yy = 0; yy < GAMEHEIGHT; yy++) {
            if (xx >= GAMEWIDTH/2 - BOARDWIDTH/2 && xx <= GAMEWIDTH/2 + BOARDWIDTH/2) {
                if (yy >= GAMEHEIGHT/2 - BOARDHEIGHT/2 && yy <= GAMEHEIGHT/2 + BOARDHEIGHT/2) {
                    board[xx][yy] = ' ';
                    continue;
                }
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
