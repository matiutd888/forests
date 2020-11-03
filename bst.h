//
// Created by mateusz on 13.03.2020.
//

#ifndef MALE_ZADANIE_C11_BST_H
#define MALE_ZADANIE_C11_BST_H

#include "general_util.h"
#include <stdbool.h>

// Biblioteka udostępnia interfejs mapy
// zaimplementowanej w postaci drzewa BST na wskaźnikach.

// Struktura węzła drzewa BST,
// zawiera wskaźnik na lewego syna, prawego syna,
// nazwę bytu (lasu/drzewa/zwierzęcia)
// oraz wskaźnik na korzeń drzewa BST reprezentującego
// mapę obiektow żyjacych na danym bycie.
// (dla przykladu value dla wezla reprezentujacego drzewo
// to wskaznik na węzeł będący korzeniem drzewa
// zwierząt żyjących na danym drzewie).
typedef struct node {
    struct node *left;
    struct node *right;
    char *name;
    struct node *value;
} node_t;


// Dodaje do drzewa o korzeniu wskazywanym przez 'root' węzeł
// z nazwą 's' i value 'val'.
// Jeżeli w drzewie istnieje już obiekt o danej nazwie
// zmienia jego value na 'val'.
// Zwraca wskaźnik na korzeń drzewa powstałego po wykonaniu operacji.
node_t *add(node_t *root, char *s, node_t *val);

// Wypisuje rekurencyjnie nazwy wezłów w drzewie o korzeniu
// wskazywanym przez 'root' w kolejności leksykograficznej.
void print_tree(node_t *root);

// Dokonuje operacji usunięcia węzła reprezentującego
// byt o nazwie 's' w drzewie ukorzenionym w węźle wskazywanym przez 'root'.
// Jeżeli taki węzeł nie istnieje nie zmienia nic w drzewie.
// Zwraca wskaźnik na korzeń drzewa powstałego po wykonaniu operacji.
node_t *delete_node(node_t *root, char *s);

// Funkcja zwraca true, jeśli na drzewie o korzeniu wskazywanym przez 'root'
// istnieje węzeł o nazwie s, false w przeciwnym wypadku.
bool exists(node_t *root, char *s);

// Rekurencyjnie zwalnia pamięć dla wszystkich węzłów w drzewie o korzeniu
// wskazywanym przez zmienną wskazywaną przez 'root'
// Zmienia wartość tej zmiennej (*root) na NULL.
void destruct(node_t **root);

// Znajduje węzeł o nazwie 's' w drzewie o korzeniu
// wskazywanym przez 'root' i zwraca jego value.
// Jeżeli taki węzeł nie istnieje zwraca NULL.
node_t *get_value(node_t *root, char *s);

#endif
