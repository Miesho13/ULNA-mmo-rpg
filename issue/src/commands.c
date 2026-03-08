#include "commands.h"
#include "issue.h"
#include "stdint.h"

static commands_map global_commands[] = {
    (commands_map){"init", issue_init},
};

int commands_service(int argc, char **argv)
{
    int ret = 0xff;
    if (argc == 1) { 
        issue_viewer(); 
        return 0;
    }

    const size_t commands_count = sizeof(global_commands)/sizeof(global_commands[0]);

    for (uint32_t command_idx = 0; command_idx < commands_count; command_idx++) {
        if (strcmp(global_commands[command_idx].name, argv[1]) == 0) {
            if (global_commands[command_idx].command) ret = global_commands[command_idx].command(argc, argv);
            break;
        }
    }

    if (ret == 0xff) {
        fprintf(stderr, "ERR: Can't finde provdied command.\n\tUse -h for list all avaliable commands.\n");
    }

    return ret;
}
