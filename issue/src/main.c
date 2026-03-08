#include "file_helper.h" 
#include "sb.h" 
#include "issue.h" 
#include "commands.h" 

#include <stdio.h>

static char *flag_table[] = {
    "--init"
};

void flag_parse(char *arg) {
    if (strcmp(arg, flag_table[0]) == 0) {
        fprintf(stderr, "the \"--init\" arg isn't implemente yeat.\n");
    }
    else {
        issue_append(arg);
    }
}

int main(int argc, char **argv)
{

//    if (is_dir_exist(".issues") != DIR_OK) {
//        fprintf(stderr, "ERR: Can't finde .issues base\nCreate one or use:\n\tissues init\n");
//        return 1;
//    }

    int ret = commands_service(argc, argv);

    return ret;
}
