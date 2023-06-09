/*
Tic Tac Toe
by Elijah Delavar

Files: TODO

Compilation: TODO

Description:
    Play Tic Tac Toe by setting up a server which can host multiple clients.
    Each client can connect to the server.
    When a waiting room has two clients, a new game is started between the clients.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sockets/client.h"
#include "sockets/server.h"

int main(int argc, char const *argv[])
{
    if (argc == 2) {
        if (!strcmp(argv[1], "client")) {
            int err = setupClient();
            if (err) {
                return err;
            }
        } else if (!strcmp(argv[1], "server")) {
            int err = setupServer();
            if (err) {
                return err;
            }
        } else if (!strcmp(argv[1], "single-player-game")) {
            puts("Single player game");
        } else {
            puts("Invalid argument.  Please specify 'client' or 'server'");
            return 1;
        }
    } else {
        puts("Invalid argument count. Please specify 'client' or 'server'");
        return 1;
    }
    return 0;
}
