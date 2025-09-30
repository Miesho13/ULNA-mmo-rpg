#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <stdint.h>
#include <stdio.h>
#include "server_client_io.h"

typedef struct {
    int fd;
} client_context;

int client_init(void);
int client_send(uint8_t *msg, size_t len);
int client_recv(uint8_t *msg, size_t len);
void client_service(client_context *ctx);
void good_bye(uint16_t id);
int hello_to_server(void);
void send_chang_pos(int id, int dx, int dy, uint16_t players[PLAYER_MAP_SIZE]);

int client_push_event(event_request_t *event_request);
int client_recv_update_event(update_respone_t *update_respone);


#endif // CLIENT_CLIENT_H
