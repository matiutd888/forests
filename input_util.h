//
// Created by mateusz on 13.03.2020.
//

#ifndef MALE_ZADANIE_C11_INPUT_UTIL_H
#define MALE_ZADANIE_C11_INPUT_UTIL_H
#define _GNU_SOURCE

#include <stdbool.h>


#define LINE_END '\n'
#define IGNORE_LINE_CHAR '#'

// Odczytuje linię ze standardowego wejścia, wyodrębnia z niej słowa
// i zapisuje je w tablicy 'words'.
// Zmienną wskazywaną przez 'word_count' ustawia na ilość słów w tablicy
// 'words' po wykonaniu funkcji.
// Jeśli odczytana linia jest niepoprawna pod względem ilości słów lub
// znajdujących się w niej znaków,
// wyświetla wiadomość o błędzie i ustawia ilość słów na 0.
// Zwraca 'true' jeśli wczytywanie powinno się zakończyć
// (koniec pliku wejściowego), 'false' wpp.
bool read_input(char **words, int *word_count);

#endif //MALE_ZADANIE_C11_INPUT_UTIL_H
