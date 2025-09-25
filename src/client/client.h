#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <stdint.h>
#include <stdio.h>

typedef struct {
    int fd;
} client_context;

int client_init(void);
int client_send(uint8_t *msg, size_t len);
void client_service(client_context *ctx);


#endif // CLIENT_CLIENT_H
