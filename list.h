#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    size_t stride;
    size_t length;
    size_t capacity;
    char *data;
} list_t;
void list_init(list_t *list, size_t stride);
bool list_push(list_t *list, void *value);
bool list_pop(list_t *list, void *value);
bool list_get(list_t *list, size_t index, void *value);
bool list_set(list_t *list, size_t index, void *value);
bool list_delete(list_t *list, size_t index);
void list_free(list_t *list);

void list_init(list_t *list, size_t stride)
{
    list->stride = stride;
    list->length = 0;
    list->capacity = 1024;
    list->data = calloc(list->capacity, list->stride);
}

bool list_push(list_t *list, void *value)
{
    if (list->length == list->capacity) {
        list->capacity *= 2;
        list->data = realloc(list->data, list->capacity * list->stride);
        if (list->data == NULL) {
            return false;
        }
    }
    memcpy(list->data + list->length * list->stride, value, list->stride);
    list->length++;
    return true;
}

bool list_pop(list_t *list, void *value)
{
    if (list->length == 0) {
        return false;
    }
    memcpy(value, list->data + (list->length - 1) * list->stride, list->stride);
    list->length--;
    return true;
}

bool list_get(list_t *list, size_t index, void *value)
{
    if (index >= list->length) {
        return false;
    }
    memcpy(value, list->data + index * list->stride, list->stride);
    return true;
}

bool list_set(list_t *list, size_t index, void *value)
{
    if (index >= list->length) {
        return false;
    }
    memcpy(list->data + index * list->stride, value, list->stride);
    return true;
}

bool list_delete(list_t *list, size_t index)
{
    if (index >= list->length) {
        return false;
    }

    if (index == list->length - 1) {
        list->length--;
        return true;
    }

    void *start = list->data + index * list->stride;
    void *end = list->data + (index + 1) * list->stride;
    size_t size = (list->length - index - 1) * list->stride;
    memmove(start, end, size);

    list->length--;
    return true;
}

void list_free(list_t *list)
{
    free(list->data);
}

#endif
