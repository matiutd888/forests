#include <stdio.h>
#include "bst.h"
#include "input_util.h"
#include "handle_util.h"

//AUTOR: Mateusz Nowakowski

int main() {
    node_t *forest_map = NULL;
    bool file_ended = false;
    while (!file_ended) {

        // Tablica łańcuchów znaków 'words' przewija się przez cały program.
        // ogólna konwencja:
        // words[0] reprezentuje pierwszy wczytany w poleceniu wyraz,
        // polecenie {ADD, DEL, CHECK, PRINT}
        // words[1] reprezentuje nazwe lasu którego dotyczy polecenie,
        // words[2] reprezentuje nazwę drzewa któ©ego dotyczy polecenie,
        // words[3] reprezentuje nazwę zwierzęcia którego dotyczy polecenie.
        // word_count reprezentuje ilość wczytanych w poleceniu słów
        char *words[MAX_WORD_COUNT];
        for (int i = 0; i < MAX_WORD_COUNT; i++)
            words[i] = NULL;
        int word_count = 0;

        file_ended = read_input(words, &word_count);
        forest_map = handle_words(words, word_count, forest_map);
        free_char_arr(words, word_count);
    }
    destruct(&forest_map);
    return 0;
}
