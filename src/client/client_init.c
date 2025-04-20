#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "client_init.h"
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

struct client {
    int sock_fd;
    struct sockaddr_in server_addr;
    user *usr;
};

client* init_client(const char *ip, const int port) {
    client *c = malloc(sizeof(client));
    if (!c) return NULL;

    c->sock_fd = create_sock(); 
    if (c->sock_fd < 0) {
        free(c);
        return NULL;
    }

    create_inetaddr(&c->server_addr, ip, port);
    user *u = init_user();

    c->usr = anonymous_user(u);

    return c;
}

void destroy_client(client *c) {
    if (!c) return;
    if (c->sock_fd >= 0) close_sock(c->sock_fd);
    destroy_user(c->usr);
    free(c);
}

user* init_user() {
    user *u = malloc(sizeof(user));
    if (!u) return NULL;
    memset(u, 0, sizeof(user));
    return u;
}

user* anonymous_user(user* u){
    u->id = -1;
    u->authenticated = 0;

    strcpy(u->fullname, "Anonymous User");
    strcpy(u->username, "anonymous_user");
    strcpy(u->email, "anonymous_user@example.com");
    
    return u;
}

void set_user(user*) {
    
}

void destroy_user(user *u) {
    if (u) free(u);
}
