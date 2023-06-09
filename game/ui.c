#include <unistd.h>
#include <assert.h>
#include <ncurses.h>
#include "ui.h"
#include "model.h"

WINDOW *uiwindow = NULL;

int cursorX = GAMEWIDTH/2-BOARDWIDTH/2;
int cursorY = GAMEHEIGHT/2-BOARDHEIGHT/2;

bool initUI() {
    // init curses
    uiwindow = initscr();
    if (!uiwindow) {
        return false;
    }
    noecho(); // Does not show what the user inputs
    cbreak(); // Reads in user inputs without needing a newline

    return true;
}

void showBoard() {
    for (int xx = 0; xx < GAMEWIDTH; xx++) {
        for (int yy = 0; yy < GAMEHEIGHT; yy++) {
            mvaddch(yy, xx, board[xx][yy]);
        }
    }
    refresh();
    move(cursorY, cursorX);
}

void userInput() {
    int input = 0;
    while (input == 0) {
        input = getch();
        if (input == 27) {
            // escape
            input = getch();
            if (input == '[') {
                // open bracket
                input = getch();
                if (input == 'A') {
                    // up
                    input = KEY_UP;
                } else if (input == 'B') {
                    // down
                    input = KEY_DOWN;
                } else if (input == 'C') {
                    // right
                    input = KEY_RIGHT;
                } else if (input == 'D') {
                    // left
                    input = KEY_LEFT;
                }
            }
        }
        
        // check for valid input
        if (input == '\n') {
            placeX(cursorX, cursorY);
        } else if (input == KEY_UP) {
            if (yInBounds(cursorY-1)) cursorY -= 1;
        } else if (input == KEY_DOWN) {
            if (yInBounds(cursorY+1)) cursorY += 1;
        } else if (input == KEY_LEFT) {
            if (xInBounds(cursorX-1)) cursorX -= 1;
        } else if (input == KEY_RIGHT) {
            if (xInBounds(cursorX+1)) cursorX += 1;
        } else {
            input = 0;
        }
    }
}

void cleanupUI() {
    delwin(uiwindow);
    endwin();
    refresh();
}