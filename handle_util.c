//
// Created by mateusz on 07.03.2020.
//

#include <stdbool.h>
#include <stdio.h>
#include "handle_util.h"
#include "execution_util.h"

// Funkcje *_util są wywoływane po przeanalizowaniu pierwszego wczytanego wyrazu.
// badają one całe polecenie pod kątem ilości słów, wywołują odpowiednią
// funkcję z biblioteki "execution_util.h" i wypisują odpowiedni komunikat.

static void check_util(char **words, int word_count, node_t *map) {
    if (word_count < 2 || equals_string(words[word_count - 1], STAR)) {
        show_error_message();
    } else {
        bool result = check_recursive(map, words, word_count, 1);
        if (result)
            printf("YES\n");
        else printf("NO\n");
    }
}

static void print_util(char **words, int word_count, node_t *map) {
    if (word_count < 1 || word_count > MAX_WORD_COUNT - 1) {
        show_error_message();
    } else {
        node_t *v = get_value_by_words(map, words, word_count);
        print_tree(v);
    }
}


static node_t *add_util(char **words, int word_count, node_t *map) {
    if (word_count > MAX_WORD_COUNT || word_count < 2) {
        show_error_message();
    } else {
        map = add_recursive(map, words, word_count, 1);
        printf(OK);
    }
    return map;
}

static node_t *del_util(char **words, int word_count, node_t *map) {

    if (word_count > MAX_WORD_COUNT || word_count < 1) {
        show_error_message();
    } else {
        map = delete_recursive(map, words, word_count, 1);
        printf(OK);
    }
    return map;
}

node_t *handle_words(char **words, int word_count, node_t *map) {
    if (word_count == 0)
        return map;

    char *first_word = words[0];

    if (equals_string(first_word, ADD))
        map = add_util(words, word_count, map);
    else if (equals_string(first_word, DELETE))
        map = del_util(words, word_count, map);
    else if (equals_string(first_word, CHECK))
        check_util(words, word_count, map);
    else if (equals_string(first_word, PRINT))
        print_util(words, word_count, map);
    else
        show_error_message();

    return map;
}