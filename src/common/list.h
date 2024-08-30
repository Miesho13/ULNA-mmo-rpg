#ifndef _LIST_TEMPLATE_
#define _LIST_TEMPLATE_

#include <stdlib.h>



typedef struct {
    int a;
} data_t;

typedef struct _node node_t;
struct _node{
    data_t data;
    node_t *head;
    node_t *tail;
    node_t *next;
    node_t *before;
    size_t size;
};



typedef struct {
    node_t node;
    size_t size;

} data_list_t;

void list_init(data_list_t *hlist);
void list_add(data_list_t *hlist, data data);
void list_pop(data_list_t *hlist, data *data);
void list_get_index(data_list_t *hlist);
void list_get_first(data_list_t *hlist);
void list_get_last(data_list_t *hlist);



#endif
