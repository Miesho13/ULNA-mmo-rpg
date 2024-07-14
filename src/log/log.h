#ifndef __LOG_H__
#define __LOG_H__

typedef enum {
    INFO = 0x0,
    ERROR,
} LOG_LEVEL;

void logger_imple(LOG_LEVEL level, const char *str, ...);


#endif
