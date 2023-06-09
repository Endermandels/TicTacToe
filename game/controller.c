#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include "ui.h"
#include "model.h"

#define ITERATIONS 300

#define REFRESH_DELAY 50000L // 50 ms delay

int startGame() {
    if (!initUI()) {
        return 1;
    }

    initBoard();

    for (int ii = 0; ii < ITERATIONS; ii++) {
        showBoard();
        usleep(REFRESH_DELAY);
    }

    cleanupUI();

    return 0;
}