#include <unistd.h>
#include <assert.h>
#include <curses.h>
#include "ui.h"

WINDOW *uiwindow = NULL;

bool initUI() {
    // init curses
    uiwindow = initscr();
    if (!uiwindow) {
        return false;
    }
    return true;
}

void showBoard() {
    for (int xx = 0; xx < GAMEWIDTH; xx++) {
        for (int yy = 0; yy < GAMEHEIGHT; yy++) {
            mvaddch(yy, xx, board[xx][yy]);
        }
    }
    refresh();
}

void cleanupUI() {
    delwin(uiwindow);
    endwin();
    refresh();
}