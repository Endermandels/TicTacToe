#include "socketUtil.h"

int createTCPIpv4Socket() {
    return socket(AF_INET, SOCK_STREAM, 0);
}

// Construct address to some server
struct sockaddr_in *createTCPIpv4Address(char *ip, int port) {
    struct sockaddr_in *address = NULL;
    address = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
    if (!address) {
        puts("Failed to Allocate Memory");
        return NULL;
    }

    address->sin_family = 2;
    address->sin_port = htons(port);

    if (strlen(ip) == 0) {
        // Server Only
        address->sin_addr.s_addr = INADDR_ANY; // Any incoming address
    } else {
        int err = inet_pton(AF_INET, ip, &(address->sin_addr.s_addr));
        if (err == 0) {
            puts("SRC does not contain a character string representing a valid network address in the specified address family");
            free(address);
            return NULL;
        } else if (err < 0) {
            puts("AF does not contain a valid address family");
            free(address);
            return NULL;
        }
    }

    return address;
}