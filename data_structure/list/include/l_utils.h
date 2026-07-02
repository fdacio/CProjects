#ifndef L_UTILS_H
#define L_UTILS_H

#include "list.h"

void print_list(const TItemList *list);
void print_list_pointer(const TItemList *list);
void print_head_list_pointer(const TItemList *list, int limit);
void print_item(const TItemList *item);
void print_item_pointer(const TItemList *item);
void print_sorted_list(const TItemList *list);
void print_descriptor(const TDescriptorList *descriptor);


#endif 