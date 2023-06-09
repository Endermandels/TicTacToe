#include "socketUtil.h"

struct AcceptedSocket {
    int acceptedSocketFD;
    struct sockaddr_in address;
    int error;
    bool acceptedSuccessfully;
};

struct AcceptedSocket *acceptIncomingConnection(int);
void sendReceivedMessageToOtherClients(char*,int);
void receiveAndPrintData(int);
void receiveAndPrintIncomingDataOnSeparateThread(struct AcceptedSocket *);
void startAcceptingIncomingConnections(int);
int setupServer();

struct AcceptedSocket acceptedSockets[10];
int acceptedSocketsCount = 0;

struct AcceptedSocket *acceptIncomingConnection(int serverSocketFD) {
    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof(struct sockaddr_in);
    int clientSocketFD = accept(serverSocketFD, &clientAddress, &clientAddressSize);

    struct AcceptedSocket *acceptedSocket = malloc(sizeof(struct AcceptedSocket));
    acceptedSocket->address = clientAddress;
    acceptedSocket->acceptedSocketFD = clientSocketFD;
    acceptedSocket->acceptedSuccessfully = clientSocketFD>0;

    if (!acceptedSocket->acceptedSuccessfully) {
        acceptedSocket->error = clientSocketFD;
    }

    return acceptedSocket;
}

void sendReceivedMessageToOtherClients(char *buffer, int socketFD) {

    for (int ii = 0; ii < acceptedSocketsCount; ii++) {
        if (acceptedSockets[ii].acceptedSocketFD != socketFD) {
            // Send message to all other clients
            send(acceptedSockets[ii].acceptedSocketFD, buffer, strlen(buffer), 0);
        }
    }

}

void receiveAndPrintData(int socketFD) {
    // Receive Client Messages
    char buffer[1024];
    while (true) {
        ssize_t amountReceived = recv(socketFD, buffer, 1024, 0);

        if (amountReceived > 0) {
            buffer[amountReceived] = '\0';
            printf("%s\n", buffer);

            sendReceivedMessageToOtherClients(buffer, socketFD);
        } else {
            // Right now, server exits after client exits
            break;
        }
    }

    close(socketFD);
}

void receiveAndPrintIncomingDataOnSeparateThread(struct AcceptedSocket *pSocket) {
    // Run a function on a separate thread
    pthread_t id;
    pthread_create(&id, NULL, receiveAndPrintData, pSocket->acceptedSocketFD);
}

void startAcceptingIncomingConnections(int serverSocketFD) {
    while (true) {
        struct AcceptedSocket *clientSocket = acceptIncomingConnection(serverSocketFD);
        acceptedSockets[acceptedSocketsCount++] = *clientSocket;

        receiveAndPrintIncomingDataOnSeparateThread(clientSocket);
    }
}

int setupServer() {

    int serverSocketFD = createTCPIpv4Socket();
    struct sockaddr_in *serverAddress = createTCPIpv4Address("", 2000); // Empty string indicates local host

    // Request access to listen for incoming connections to port 2000
    int result = bind(serverSocketFD, serverAddress, sizeof(*serverAddress));

    if (result == 0) {
        puts("Server socket was bound successfully");
    }

    int listenResult = listen(serverSocketFD, 10);

    startAcceptingIncomingConnections(serverSocketFD);

    shutdown(serverSocketFD, SHUT_RDWR);

    return 0;
}
