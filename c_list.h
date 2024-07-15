#ifndef C_LIST_H
#define C_LIST_H


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define VAR_TO_STRING(var) #var

#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

#define DECREASE_CAPACITY(capacity) \
    ((capacity) < 16 ? 8 : (capacity) / 2)

#define CHANGE_ARRAY(type, pointer, oldCount, newCount) \
    (type *)reallocate(pointer, sizeof(type) * (oldCount), sizeof(type) * (newCount))

#define FREE_ARRAY(type, pointer, oldCount) \
    reallocate(pointer, sizeof(type) * (oldCount), 0)

void *reallocate(void *pointer, size_t oldSize, size_t newSize) {
    if (newSize == 0) {
        free(pointer);
        return NULL;
    }

    void *result = realloc(pointer, newSize);
    if (result == NULL)
        exit(1);
    return result;
}

#define ListDec(type, list_name)                                                            \
    typedef struct                                                                          \
    {                                                                                       \
        int capacity;                                                                       \
        int count;                                                                          \
        type *data;                                                                         \
    } list_name;                                                                            \
                                                                                            \
    void init_##list_name(list_name *list);                                                 \
    void push_##list_name(list_name *list, type Element);                                   \
    type pop_##list_name(list_name *list);                                                  \
    type back_##list_name(list_name *list);                                                 \
    type *get_##list_name(list_name *list, size_t index);                                   \
    bool set_##list_name(list_name *list, size_t index, type Element);                      \
    int find_##list_name(list_name *list, type Element);                                    \
    void free_##list_name(list_name *list);                                                 \
    int size_of_##list_name(list_name *list);                                               \
    bool is_empty_##list_name(list_name *list);                                             \
    void clear_##list_name(list_name *list);                                                \
    list_name* extend_##list_name(list_name *list_a, list_name *list_b);                    \
    bool insert_##list_name(list_name *list, size_t index, type Element);                   \
    bool remove_at_##list_name(list_name *list, size_t index);                              \
    void remove_##list_name(list_name *list, type Element);                                 \
    void print_##list_name(list_name *list, void (*printElement)(type));


#define ListDef(type, list_name)                                                               \
    void init_##list_name(list_name *list) {                                                   \
        list->data = NULL;                                                                     \
        list->capacity = 0;                                                                    \
        list->count = 0;                                                                       \
    }                                                                                          \
                                                                                               \
    void push_##list_name(list_name *list, type Element){                                      \
        if (list->capacity < list->count + 1){                                                 \
            int oldCapacity = list->capacity;                                                  \
            list->capacity = GROW_CAPACITY(oldCapacity);                                       \
            list->data = CHANGE_ARRAY(type, list->data, oldCapacity, list->capacity);          \
        }                                                                                      \
        list->data[list->count] = Element;                                                     \
        list->count++;                                                                         \
    }                                                                                          \
                                                                                               \
    type pop_##list_name(list_name *list){                                                     \
        if(list->count==0){                                                                    \
            fprintf(stderr,                                                                    \
            "list %s is empty, you could not pop element from it",VAR_TO_STRING(list_name));   \
            exit(0);                                                                           \
        }                                                                                      \
        list->count--;                                                                         \
        return list->data[list->count];                                                        \
    }                                                                                          \
                                                                                               \
    type back_##list_name(list_name *list){                                                    \
        if(list->count==0){                                                                    \
            fprintf(stderr,                                                                    \
            "list %s is empty, you could not pop element from it",VAR_TO_STRING(list_name));   \
            exit(0);                                                                           \
        }                                                                                      \
        return list->data[list->count-1];                                                      \
    }                                                                                          \
                                                                                               \
    type *get_##list_name(list_name *list, size_t index){                                      \
        if (index >= list->count || index < 0){                                                \
            return NULL;                                                                       \
        }                                                                                      \
        return &(list->data[index]);                                                           \
    }                                                                                          \
                                                                                               \
    bool set_##list_name(list_name *list, size_t index, type Element) {                        \
        if (index >= 0 && index < list->count){                                                \
            list->data[index] = Element;                                                       \
            return true;                                                                       \
        }                                                                                      \
        return false;                                                                          \
    }                                                                                          \
                                                                                               \
    int find_##list_name(list_name *list, type Element){                                       \
        for (int i = 0; i < list->count; i++){                                                 \
            if (list->data[i]==Element) return i;                                              \
        }                                                                                      \
        return -1;                                                                             \
    }                                                                                          \
                                                                                               \
    void free_##list_name(list_name *list){                                                    \
        FREE_ARRAY(type, list->data, list->capacity);                                          \
        init_##list_name(list);                                                                \
    }                                                                                          \
                                                                                               \
    int size_of_##list_name(list_name *list) { return list->count; }                           \
                                                                                               \
    bool is_empty_##list_name(list_name *list) { return list->count == 0; }                    \
                                                                                               \
    void clear_##list_name(list_name *list) { free_##list_name(list); }                        \
                                                                                               \
    list_name* extend_##list_name(list_name *list_a, list_name *list_b) {                      \
        if (list_a == NULL) return NULL;                                                       \
        if (list_b == NULL) return list_a;                                                     \
        if(list_a->capacity<list_a->count+list_b->count){                                      \
            int oldCapacity = list_a->capacity;                                                \
            list_a->capacity = GROW_CAPACITY(list_a->count+list_b->count);                     \
            list_a->data = CHANGE_ARRAY(type, list_a->data, oldCapacity, list_a->capacity);    \
        }                                                                                      \
        memcpy(list_a->data+list_a->count, list_b->data,sizeof(type)*list_b->count);           \
        list_a->count+=list_b->count;                                                          \
        return list_a;                                                                         \
    }                                                                                          \
                                                                                               \
    bool insert_##list_name(list_name *list, size_t index, type Element) {                     \
        if (index < 0 || index > list->count) {                                                \
            return false;                                                                      \
        }                                                                                      \
        if (list->count == list->capacity) {                                                   \
            int oldCapacity = list->capacity;                                                  \
            list->capacity = GROW_CAPACITY(oldCapacity);                                       \
            list->data = CHANGE_ARRAY(type, list->data, oldCapacity, list->capacity);          \
        }                                                                                      \
        for (int i = list->count; i > index; i--) {                                            \
            list->data[i] = list->data[i - 1];                                                 \
        }                                                                                      \
        list->data[index] = Element;                                                           \
        list->count++;                                                                         \
        return true;                                                                           \
    }                                                                                          \
                                                                                               \
    bool remove_at_##list_name(list_name *list, size_t index) {                                \
        if (index < 0 || index >= list->count) {                                               \
            return false;                                                                      \
        }                                                                                      \
        for (int i = index; i < list->count - 1; i++) {                                        \
            list->data[i] = list->data[i + 1];                                                 \
        }                                                                                      \
        list->count--;                                                                         \
        if (list->count<list->capacity/3)                                                      \
        {                                                                                      \
            int oldCapacity = list->capacity;                                                  \
            list->capacity=DECREASE_CAPACITY(oldCapacity);                                     \
            list->data = CHANGE_ARRAY(type, list->data, oldCapacity, list->capacity);          \
        }                                                                                      \
        return true;                                                                           \
    }                                                                                          \
                                                                                               \
    void remove_##list_name(list_name *list, type Element){                                    \
        int index = find_##list_name(list, Element);                                           \
        while (index != -1)                                                                    \
        {                                                                                      \
            remove_at_##list_name(list, index);                                                \
            index=find_##list_name(list, Element);                                             \
        }                                                                                      \
    }                                                                                          \
                                                                                               \
    void print_##list_name(list_name *list, void (*printElement)(type)){                       \
        printf("===list begin===\n");                                                          \
        for (int i = 0; i < list->count; i++) {                                                \
            printElement(list->data[i]);                                                       \
            printf("\n");                                                                      \
        }                                                                                      \
        printf("=== list end ===\n");                                                          \
    }
#endif //C_LIST_H