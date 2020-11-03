#include "general_util.h"
#include <stdio.h>
#include <string.h>

void show_error_message() {
    fprintf(stderr, "ERROR\n");
}

void *try_malloc(void *p, size_t size) {
    p = malloc(size);

    if (p == NULL)
        exit(1);
    return p;
}

bool equals_string(char *s, char *t) {
    return (strcmp(s, t) == 0);
}

void free_char_arr(char **arr, int l) {
    for (int i = 0; i < l; i++){
        free(arr[i]);
        arr[i] = NULL;
    }
}


