#include <stdio.h>
#include <stdbool.h>
#include "./list.h"

int main()
{
    list_t list;
    list_init(&list, sizeof(int));
    for (int i = 0; i < 10; i++) {
        bool success = list_push(&list, &i);
        if (!success) {
            printf("push failed\n");
            return 1;
        }
    }

    list_push(&list, &(int){ 10 });

    for (int i = 0; i < 10; i++) {
        int value;
        bool success = list_get(&list, i, &value);
        if (!success) {
            printf("Error: list_get failed\n");
            break;
        }
        printf("%d\n", value);
    }
    list_free(&list);
    return 0;
}
