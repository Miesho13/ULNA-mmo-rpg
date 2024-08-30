#include "list.h" 
#include <stdlib.h>
#include <string.h>

void list_init(data_list_t *h_list) {
    h_list->node.data = (data_t){0};
    h_list->node.head = &h_list->node;
    h_list->node.tail = &h_list->node;
    h_list->node.next = NULL;
    h_list->node.before = NULL;
    h_list->size = 0;
}


void list_add(data_list_t *h_list, data_t data) {
    if (h_list->size > 0) {
        h_list->size++;

        node_t *tmp = h_list->node.head;
        h_list->node.head = (node_t*)malloc(sizeof(data_t));
        h_list->node.head->data = data; 

    } else {
        h_list->size++;
        h_list->node.data = data;
    }
}

