//
// Created by mateusz on 13.03.2020.
//

#ifndef MALE_ZADANIE_C11_EXECUTION_UTIL_H
#define MALE_ZADANIE_C11_EXECUTION_UTIL_H

#define STAR "*"

#include "bst.h"

// Funkcja pomocnicza używana przy obsłudze zapytania 'PRINT ..'.
// Przyjmuje jako argument wskaźnik na korzeń drzewa
// i tablicę łańcuchów words oraz ilość słów w tej tablicy.
// Jeżeli word_count = 1 to zwraca wskaźnik otrzymany jako argument.
// W przeciwnym wypadku zwraca wskaźnik na korzeń drzewa
// będącego 'value' bytu o nazwie zdefiniowanej przez sekwencję
// wyrazów od words[1] do words[word_count - 1].
// przykładowo jeżeli words = {"PRINT", "las1", "drzewo1", - }
// i word_count = 3 to get_value_by_words zwróci wskaźnik na korzeń drzewa
// reprezentującego zwierzęta żyjące w lesie "las1" na drzewie "drzewo1".
// Jeżeli taki byt nie istnieje zwraca NULL.
node_t *get_value_by_words(node_t *map, char **words, int word_count);

// Przyjmuje wskaźnik na korzeń drzewa 'map' i usuwa z niego byt
// o nazwie words[word_count - 1] żyjącego
// na bycie words[word_count - 2], ...., żyjącego na bycie words[it],
// żyjącego na drzewie, którego korzeń wskazywany jest przez 'map'.
// Jeśli word_count = 1 zwalnia pamięc zaolokowaną w całym drzewie.
// Zwraca wskaźnik na korzeń drzewa po wykonaniu operacji.
// Funkcja zakłada word_count >= it >= 1.
node_t *delete_recursive(node_t *map, char **words, int word_count, int it);

// Przyjmuje wskaźnik na korzeń drzewa 'map' i dodaje do niego
// byt o nazwie words[word_count - 1] żyjący na
// bycie words[word_count - 2], ...., żyjący na bycie words[it],
// żyjący na drzewie, którego korzeń wskazywany jest przez 'map'.
// Ignoruje probe dodania istniejacego bytu
// Zwraca wskaźnik na korzeń drzewa po wykonaniu operacji.
// Funkcja zakłada word_count > it >= 1.
node_t *add_recursive(node_t *map, char **words, int word_count, int it);

// Zwraca 'true' lub 'false' w zależności czy istnieje
// byt o nazwie words[word_count - 1] żyjący na
// bycie words[word_cout - 2], ... żyjący na bycie words[it],
// żyjący na drzewie o korzeniu wskazywanym przez 'map'.
// Funkcja zakłada, że word_count >= 2.
// Jezeli w komórce 'words' o indeksie równym it, różnym od word_count - 1,
// znajduje się słowo specjalne "*", funkcja istnienie bytu nazwie
// words[word_count - 1], żyjącego na bycie words[word_count - 2], ...,
// żyjącego na bycie words[it + 1] sprawdza
// dla każdego bytu żyjącego na drzewie o korzeniu wskazywanym przez 'map',
// i zwraca 'true' jeśli znalazła przynajmniej jeden taki by, 'false' wpp.
bool check_recursive(node_t *map, char **words, int word_count, int it);

#endif
