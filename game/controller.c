#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include "ui.h"
#include "model.h"

int startGame() {
    if (!initUI()) {
        return 1;
    }

    initBoard();

    while (!gameWon('X')) {
        showBoard();
        userInput();
        if (tie()) {
            break;
        }
    }

    showBoard();

    usleep(1000000);

    cleanupUI();

    return 0;
}