//
// Created by mateusz on 03.03.2020.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bst.h"

#define STRING_ALLOC_CONST 10

// Rezerwuje miejsce w pamięci dla nowego węzła.
// Ustawia wskaźnik na jego synów na NULL, nazwę na 's' a value na na 'val'
// Zwraca wskaźnik na ten węzeł.
static node_t *initialize_node(char *s, node_t *val) {
    node_t *root = NULL;
    root = try_malloc(root, sizeof(struct node));

    root->right = NULL;
    root->left = NULL;

    root->name = NULL;
    root->name = try_malloc(root->name, strlen(s) + STRING_ALLOC_CONST);
    strcpy(root->name, s);

    root->value = val;

    return root;
}

node_t *add(node_t *root, char *s, node_t *val) {
    if (s == NULL)
        return root;

    if (root == NULL) {
        root = initialize_node(s, val);
    } else {
        int x = strcmp(s, root->name);
        if (x == 0)
            root->value = val;
        else if (x < 0)
            root->left = add(root->left, s, val);
        else root->right = add(root->right, s, val);
    }
    return root;
}

void print_tree(node_t *root) {
    if (root == NULL)
        return;

    print_tree(root->left);
    printf("%s\n", root->name);
    print_tree(root->right);
}

// Zwalnia pamięć zaalokowaną dla nazwy i wartości węzła wskazywanego
// przez zmienną wskazywaną przez 'root'. Ustawia tą zmienną (*root) na NULL
static void destruct_node_values(node_t **root) {
    if ((*root)->value != NULL) {
        destruct(&(*root)->value);
    }
    if ((*root)->name != NULL) {
        free((*root)->name);
        (*root)->name = NULL;
    }
}

// Zwalnia pamięć zaalokowaną dla węzła wskazywanego przez zmienną wskazywaną
// przez 'root'. Ustawia tą zmienną (*root) na NULL
static void destruct_node(node_t **root) {
    destruct_node_values(root);
    free(*root);
    *root = NULL;
}

void destruct(node_t **root) {
    if (*root == NULL)
        return;

    destruct(&(*root)->left);
    destruct(&(*root)->right);
    destruct_node(root);
}

// Znajduje węzeł o największej nazwie w kolejności leksykograficznej
// w drzewie o korzeniu wskazywanym przez root.
// Zwraca wskaźnik na ten węzeł
static node_t *max_value(node_t *root) {
    if (root->right == NULL)
        return root;

    return max_value(root->right);
}

// Funkcja służąca tylko jako funkcja pomocnicza dla 'delete_node'.
// W drzewie o korzeniu wskazywanym przez 'root' znajduje węzeł
// (nazwijmy go 'p') o największej nazwie w kolejności leksykograficznej.
// Usuwa ten węzeł, ale nie jego parametry,
// tj nazwę, lewego syna, prawego syna i wartość.
// Ustawia prawego syna ojca 'p' na wskaźnik na lewego syna 'p'.
// Zwraca wskaźnik na korzeń drzewa powstałego po wykonaniu tej operacji.
static node_t *delete_node_right(node_t *root) {
    if (root->right == NULL) {
        node_t *l = root->left;
        free(root);
        return l;
    }

    root->right = delete_node_right(root->right);
    return root;
}

// Przepisuje do węzła wskazywanego przez 'to'
// nazwę i wartość węzła wskazywanego przez 'from'.
static void copy_node(node_t *from, node_t *to) {
    to->value = from->value;
    to->name = from->name;
}

node_t *delete_node(node_t *root, char *s) {
    if (root == NULL)
        return root;
    int x = strcmp(s, root->name);
    if (x == 0) {
        if (root->right == NULL) {
            node_t *l = root->left;
            destruct_node(&root);
            return l;
        } else if (root->left == NULL) {
            node_t *r = root->right;
            destruct_node(&root);
            return r;
        } else {
            // Jeżeli żaden z synów wierzchołka wskazywanego
            // przez root nie jest NULL zwalniamy pamięć zaalokowaną dla
            // nazwy i wartości root i zmieniamy je na wartość i nazwe
            // wierzchołka o największej nazwie w kolejności leksykograficznej w
            // lewym poddrzewie root, pamiętając o zwolnieniu koniecznej pamięci.
            node_t *ls = max_value(root->left);
            destruct_node_values(&root);
            copy_node(ls, root);

            root->left = delete_node_right(root->left);
            return root;
        }
    } else if (x < 0) {
        root->left = delete_node(root->left, s);
        return root;
    } else {
        root->right = delete_node(root->right, s);
        return root;
    }
}

bool exists(node_t *root, char *s) {
    if (root == NULL)
        return false;
    int x = strcmp(s, root->name);
    if (x == 0)
        return true;
    else if (x > 0)
        return exists(root->right, s);
    else return exists(root->left, s);
}

node_t *get_value(node_t *root, char *s) {
    if (root == NULL)
        return NULL;
    int x = strcmp(s, root->name);
    if (x == 0)
        return root->value;
    else if (x > 0)
        return get_value(root->right, s);
    else return get_value(root->left, s);
}
