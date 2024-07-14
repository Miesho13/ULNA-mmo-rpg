#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "log.h"

void logger_imple(LOG_LEVEL level, const char *str, ...) {
     
    switch (level) {
        case INFO:
            printf("[INFO]: ");
            break;

        case ERROR:
            printf("[ERROR]: ");
            break;
    }

    va_list args;
    va_start(args, str);
    vprintf(str, args);
    va_end(args);
    printf("\n");
}
