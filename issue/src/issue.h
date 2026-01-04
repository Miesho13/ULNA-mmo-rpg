#ifndef _ISSUE_
#define _ISSUE_

#include "sb.h"

#define ISSUE_VIEWER_BUFFER_SIZE (1024)

/*
 * [1] (date) (uid) (name) (prio) (short_breaf)
 */ 
typedef struct {
    char id[ISSUE_VIEWER_BUFFER_SIZE];
    char date[ISSUE_VIEWER_BUFFER_SIZE];
    char uid[ISSUE_VIEWER_BUFFER_SIZE];
    char name[ISSUE_VIEWER_BUFFER_SIZE];
    char prio[ISSUE_VIEWER_BUFFER_SIZE];
    char short_breaf[ISSUE_VIEWER_BUFFER_SIZE];
} issue_view_record;

typedef struct {
    issue_view_record *items;
    size_t count;
    size_t capacity;
} issue_container;


void issue_viewer(void);
void issue_append(char *issue_name);

#endif // _ISSUE_
