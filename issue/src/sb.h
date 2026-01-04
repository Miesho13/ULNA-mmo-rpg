#ifndef STRING_BUILDER_H
#define STRING_BUILDER_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    size_t len;
    size_t cap;
} string_builder;

string_builder *sb_create(void);
void sb_append(string_builder *sb, const char *fmt, ...);
void sb_free(string_builder *sb);

#endif // STRING_BUILDER_H
