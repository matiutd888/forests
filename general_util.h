//
// Created by mateusz on 13.03.2020.
//

#ifndef MALE_ZADANIE_GENERAL_UTIL_H
#define MALE_ZADANIE_GENERAL_UTIL_H

// Biblioteka udostępnia ogólne funkcje przydatne w różnych miejscach programu

#include <stdlib.h>
#include <stdbool.h>

#define MAX_WORD_COUNT 4

// Wyświetla wiadomość o błędzie
void show_error_message();

// Rezerwuje w miejscu wskazywanym przez 'p' pamięć o rozmiarze 'size'.
// Jeżeli to się nie uda, kończy program z kodem 1.
void *try_malloc(void *p, size_t size);

// Zwraca 'true' jeśli łańcuchy znaków 's' i 't' są równe.
// 'false' w przeciwnym wypadku.
bool equals_string(char *s, char *t);

// uwalnia pamięć zarezerwowaną dla każdego elementu tablicy 'arr' o długości 'l'
void free_char_arr(char **arr, int l);

#endif //MALE_ZADANIE_GENERAL_UTIL_H
