#ifndef CHAT_SYSTEM_CLIENT_UTILS_H
#define CHAT_SYSTEM_CLIENT_UTILS_H

#include <netinet/in.h>

int create_sock();
int close_sock(int sock_fd);
void create_inetaddr(struct sockaddr_in *addr, const char *ip, int port);

#endif // CHAT_SYSTEM_CLIENT_UTILS_H
