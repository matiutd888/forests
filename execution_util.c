
#include "execution_util.h"
#include "general_util.h"

node_t *add_recursive(node_t *map, char **words, int word_count, int it) {
    if (it == word_count - 1) {
        if (!exists(map, words[it]))
            map = add(map, words[it], NULL);
    } else {
        node_t *t = get_value(map, words[it]);
        t = add_recursive(t, words, word_count, it + 1);
        map = add(map, words[it], t);
    }
    return map;
}

node_t *delete_recursive(node_t *map, char **words, int word_count, int it) {
    if (word_count == 1) {
        destruct(&map);
    } else if (it == word_count - 1) {
        map = delete_node(map, words[it]);
    } else {
        node_t *t = get_value(map, words[it]);
        if (t != NULL) {
            t = delete_recursive(t, words, word_count, it + 1);
            map = add(map, words[it], t);
        }
    }
    return map;
}

node_t *get_value_by_words(node_t *map, char **words, int word_count) {
    if (word_count > MAX_WORD_COUNT - 1 || word_count < 1)
        return NULL;
    if (word_count == 1)
        return map;
    return get_value(get_value_by_words(map, words, word_count - 1),
                     words[word_count - 1]);
}

bool check_recursive(node_t *map, char **words, int word_count, int it) {
    if (map == NULL)
        return false;
    if (it == word_count - 1)
        return exists(map, words[it]);

    if (equals_string(words[it], STAR)) {
        if (check_recursive(map->value, words, word_count, it + 1))
            return true;
        return
                check_recursive(map->right, words, word_count, it) ||
                check_recursive(map->left, words, word_count, it);
    } else
        return check_recursive(get_value(map, words[it]),
                               words, word_count, it + 1);
}



