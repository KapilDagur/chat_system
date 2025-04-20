#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "client_utils.h"

struct user 
{
    int id;
    char uid[32];
    char username[100];
    
    char fullname[200];
    char email[200];
    
    int authenticated;
};

int create_sock() {
    return socket(AF_INET, SOCK_STREAM, 0);
}

int close_sock(int sock_fd) {
    return close(sock_fd);
}

void create_inetaddr(struct sockaddr_in *addr, const char *ip, int port) {
    memset(addr, 0, sizeof(struct sockaddr_in));
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    inet_pton(AF_INET, ip, &addr->sin_addr);
}
