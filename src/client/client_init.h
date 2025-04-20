#ifndef CHAT_SYSTEM_CLIENT_INIT_H
#define CHAT_SYSTEM_CLIENT_INIT_H

struct client;
struct user;

typedef struct client client;
typedef struct user user;

client* init_client(const char *ip, const int port);
void destroy_client(client *__c);

user* init_user();
void destroy_user(user *__u);

#endif // CHAT_SYSTEM_CLIENT_INIT_H
