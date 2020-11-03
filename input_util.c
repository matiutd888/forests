#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input_util.h"
#include "general_util.h"

#define GETLINE_FAILURE -1

// Zwraca 'true' jeśli znak 'c' jest białym znakiem
// (koniec linii nie jest liczony jako znak biały), 'false' wpp.
static bool is_space(unsigned char c) {
    return c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r';
}

// Dodaje do tablicy łańcuchów znaków 'words' łańcuch 's' o długości 'len'
// i zwiększa licznik słów w 'words' wskazywany przez 'word_count'.
static void add_to_words(char **words, char *s, int *word_count, size_t len) {

    words[*word_count] = NULL;
    words[*word_count] = try_malloc(words[*word_count], len + 10);
    strcpy(words[*word_count], s);
    (*word_count)++;
}

// Zwraca 'true' jeśli łańcuch znaków 's' o długosci 'len',
// zakończony znakiem końca linii składa się tylko z białych znaków
// i znaków o kodach ASCII od 32 do 255, oraz znaku końca linii na końcu,
// lub 'false' wpp.
static bool has_all_good_chars(const char *s, ssize_t len) {
    int i = 0;
    bool ok = true;
    while (i < len && s[i] != LINE_END && ok) {
        unsigned char c = s[i++];
        if (c < 33 && !is_space(c))
            ok = false;
    }
    return ok;
}

// Zwraca 'true' jeśli łańcuch znaków 's' o długosci len posiada znak niebiały
// 'false' wpp.
bool has_non_whitespace(const char *s, ssize_t len) {
    bool is_all_whitespace = true;

    for (ssize_t i = 0; i < len && is_all_whitespace; i++) {
        unsigned char c = s[i];

        if (!is_space(c))
            is_all_whitespace = false;
    }
    return !is_all_whitespace;
}

// Odczytuje słowa zapisane w linijce 'line' o długości 'len' i
// zapisuje je w tablicy 'words', ustawiając przy tym zmienną wskazywaną
// przez wskaźnik 'word_count' na ilość słów w linii.
// Zwraca 'true', jeśli linia jest poprawna,
// 'false', jeśli linia jest niepoprawna tzn:
// jeśli linia zawiera niedozwolone znaki lub więcej słów, niż maksymalna
// dozwolona ilość słów w linii.
static bool read_from_line(char *line, int len, char **words, int *word_count) {
    char delimit[] = " \t\r\n\v\f";
    bool good_input = true;

    if (!has_all_good_chars(line, len))
        return false;

    char *token = NULL;
    token = strtok(line, delimit);
    while (token != NULL && good_input) {
        if (*word_count > MAX_WORD_COUNT - 1)
            good_input = false;
        else {
            size_t l = strlen(token);
            add_to_words(words, token, word_count, l);
            token = strtok(NULL, delimit);
        }
    }
    return good_input;
}

// Przyjmuje jako argument linię 'line' o długosci 'len' i
// obsługuje nietypowe przypadki: linię będacą komentarzem i
// linię niezakończoną znakiem końca linii.
// Zwraca 'true' jeśli wystąpił któryś z wymienionych przypadków, false wpp.
static bool corner_cases(char *line, ssize_t len) {
    if (line[0] == IGNORE_LINE_CHAR)
        return true;

    // Polecenie niebędące komentarzem bez końca linii jako ostatni znak
    // musi się składać z samych znaków białych.
    // W przeciwnym wypadku należy wypisać komunikat o błędzie.
    if (line[len - 1] != LINE_END) {
        if (has_non_whitespace(line, len))
            show_error_message();

        return true;
    }
    return false;
}

bool read_input(char **words, int *word_count) {
    char *line;
    line = try_malloc(&line, 2);
    size_t rozmiar = 1;

    ssize_t len = getline(&line, &rozmiar, stdin);

    if (len == GETLINE_FAILURE) {
        free(line);
        return true;
    }

    if (corner_cases(line, len)) {
        free(line);
        return false;
    }

    bool good_input = read_from_line(line, len, words, word_count);

    if (!good_input) {
        show_error_message();
        free_char_arr(words, *word_count);
        *word_count = 0;
    }
    free(line);

    return false;
}
