#ifndef SERVER_IO
#define SERVER_IO

#include "core.h"

#include <stdint.h>
#include <server.h>

void hello_user(core *CORE, cnet_message_t *msg);
void update_from_user(core *CORE, cnet_message_t *msg);

#endif // SERVER_IO
