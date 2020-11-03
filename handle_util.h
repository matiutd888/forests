//
// Created by mateusz on 13.03.2020.
//


#ifndef MALE_ZADANIE_C11_HANDLE_UTIL_H
#define MALE_ZADANIE_C11_HANDLE_UTIL_H

#include "bst.h"

#define ADD "ADD"
#define DELETE "DEL"
#define PRINT "PRINT"
#define CHECK "CHECK"
#define OK "OK\n"

// Przyjmuje tablicę wczytanych słów wraz z ich ilością
// oraz wskaźnik na korzeń drzewa na którym ma być wykonane polecenie.
// W zależności od wczytanych słów i ich ilości wypisuje stosowny
// komunikat {"OK, "ERROR", "YES", "NO"}.
// Zwraca wskaźnik na korzeń drzewa po wykonaniu polecenia.
node_t *handle_words(char **words, int word_count, node_t *map);

#endif //MALE_ZADANIE_C11_HANDLE_UTIL_H