#ifndef WORLD_UPDATE 
#define WORLD_UPDATE 

#include "core.h"

void update_position(core *CORE, uint32_t player_id);
void epilog_update(core *CORE, uint32_t player_id);
void update_claster(core *CORE, uint32_t player_id);
void update_events(core *CORE, uint16_t player_id);

#endif // WORLD_UPDATE
