#include "socketUtil.h"

void listenAndPrint(int socketFD) {
    // Receive Client Messages
    char buffer[1024];
    while (true) {
        ssize_t amountReceived = recv(socketFD, buffer, 1024, 0);

        if (amountReceived > 0) {
            buffer[amountReceived] = '\0';
            printf("%s\n", buffer);
        } else {
            break;
        }
    }

    close(socketFD);
}

void startListeningAndPrintMessagesOnNewThread(int socketFD) {
    pthread_t id;
    pthread_create(&id, NULL, listenAndPrint, socketFD);
}

int setupClient() {
    // Create socket and address
    int socketFD = createTCPIpv4Socket();
    char *ip = "127.0.0.1"; // Local address
    struct sockaddr_in *address = createTCPIpv4Address(ip, 2000);

    // Connect socket to server at address
    int result = connect(socketFD, address, sizeof(*address));
    free(address);

    if (result == 0) {
        puts("Client connection was successful!");
    }

    char *name = NULL;
    size_t nameSize = 0;
    printf("Please enter your name:  ");
    size_t nameCount = getline(&name, &nameSize, stdin);
    name[nameCount-1] = '\0';

    char *line = NULL;
    size_t lineSize = 0;
    puts("Type message (exit to quit)");

    startListeningAndPrintMessagesOnNewThread(socketFD);

    char buffer[1024];

    // Send Messages to Server
    while (true) {
        size_t charCount = getline(&line, &lineSize, stdin);
        line[charCount-1] = '\0';

        sprintf(buffer, "%s:%s", name, line);

        if (charCount > 0) {
            if (!strcmp(line, "exit")) {
                break;
            }
            ssize_t amountSent = send(socketFD, buffer, strlen(buffer), 0);
        }
    }

    close(socketFD);

    return 0;
}
