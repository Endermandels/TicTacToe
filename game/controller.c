#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include "ui.h"
#include "model.h"

#define ITERATIONS 10

int startGame() {
    if (!initUI()) {
        return 1;
    }

    initBoard();

    for (int ii = 0; ii < ITERATIONS; ii++) {
        showBoard();
        userInput();
    }

    showBoard();

    usleep(1000000);

    cleanupUI();

    return 0;
}