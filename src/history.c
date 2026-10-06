#include "history.h"

#include <stdint.h>
#include <stdlib.h>

#define INITIAL_HISTORY_CAPACITY 8U

void history_init(MoveHistory *history) {
    if (history == NULL) {
        return;
    }

    history->items = NULL;
    history->count = 0;
    history->capacity = 0;
}

int history_push(MoveHistory *history, Move move) {
    if (history == NULL) {
        return 0;
    }
    if (history->count >= history->capacity) {
        size_t new_capacity = (history->capacity == 0) ? (size_t)INITIAL_HISTORY_CAPACITY : history->capacity * 2U;
        Move *new_items = realloc(history->items, new_capacity * sizeof(Move));
        if (new_items == NULL) {
            return 0;
        }
        history->items = new_items;
        history->capacity = new_capacity;
    }
    history->items[history->count] = move;
    history->count++;
    return 1;
}

int history_pop(MoveHistory *history, Move *result) {
    if (history == NULL || history->count == 0 || history->items == NULL) {
        return 0;
    }
    history->count--;
    if (result != NULL) {
        *result = history->items[history->count];
    }
    return 1;
}

void history_clear(MoveHistory *history) {
    if (history == NULL) {
        return;
    }

    history->count = 0;
}

void history_destroy(MoveHistory *history) {
    if (history == NULL) {
        return;
    }

    free(history->items);
    history->items = NULL;
    history->count = 0;
    history->capacity = 0;
}
