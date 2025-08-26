#ifndef C_LIST_H
#define C_LIST_H


#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define VAR_TO_STR(var) #var

#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

#define DECREASE_CAPACITY(capacity) \
    ((capacity) < 16 ? 8 : (capacity) / 2)

#define CHANGE_ARRAY(type, pointer, oldCount, newCount) \
    (type *)reallocate(pointer, sizeof(type) * (oldCount), sizeof(type) * (newCount))

#define FREE_ARRAY(type, pointer, oldCount) \
    reallocate(pointer, sizeof(type) * (oldCount), 0)

#define log_err(M, ...)                                                       \
    fprintf(stderr, "[ERROR] (%s::%d::%s: errno: %s) " M "\n",                \
    __FILE__, __LINE__, __func__, clean_list_errno(), ##__VA_ARGS__)

static inline void *reallocate(void *pointer, size_t oldSize, size_t newSize) {
    if (newSize == 0) {
        free(pointer);
        return NULL;
    }
    return realloc(pointer, newSize);
}

static inline int next_power_of_2(const int a) {
    if (a == INT_MAX) {
        return INT_MAX;
    }
    int begin = 16;
    while (begin < a) {
        begin *= 2;
    }
    return begin;
}

typedef enum {
    LIST_OK = 0,
    LIST_NOT_EXIST,
    LIST_EMPTY,
    LIST_OUT_OF_RANGE,
    LIST_ALLOCATION_FAILED,
    LIST_INVALID_PRINTFN,
    LIST_INVALID_CAPACITY,
} List_errno;

extern List_errno global_list_errno;

extern const char *List_errno_string[];

static inline const char *list_errno_str(const List_errno e) {
    return List_errno_string[e];
}

static inline List_errno get_list_errno() {
    List_errno err = global_list_errno;
    global_list_errno = LIST_OK;
    return err;
}

static inline void set_list_errno(List_errno e) {
    global_list_errno = e;
}

static inline const char *clean_list_errno() {
    return list_errno_str(get_list_errno());
}

#define LIST_INIT \
    List_errno global_list_errno = LIST_OK;          \
    const char *List_errno_string[] = {              \
        "LIST_OK" ,                                  \
        "LIST_NOT_EXIST",                            \
        "LIST_EMPTY",                                \
        "LIST_OUT_OF_RANGE",                         \
        "LIST_ALLOCATION_FAILED",                    \
        "LIST_INVALID_PRINTFN",                      \
        "LIST_INVALID_CAPACITY",                     \
};

#define ListDec(type, list_name)                                                            \
    typedef struct                                                                          \
    {                                                                                       \
        int capacity;                                                                       \
        int count;                                                                          \
        type *data;                                                                         \
        List_errno err;                                                                     \
    } list_name;                                                                            \
    type list_name##_default_element;                                                       \
                                                                                            \
    List_errno get_errno_##list_name(list_name *list);                                      \
    void set_errno_##list_name(list_name *list, List_errno e);                              \
    list_name *create_##list_name();                                                        \
    void destroy_##list_name(list_name *list);                                              \
    void init_##list_name(list_name *list);                                                 \
    bool push_##list_name(list_name *list, type Element);                                   \
    type pop_##list_name(list_name *list);                                                  \
    bool resize_##list_name(list_name *list, int new_capacity);                             \
    bool expand_##list_name(list_name *list);                                               \
    bool shrink_##list_name(list_name *list);                                               \
    type first_##list_name(list_name *list);                                                \
    type back_##list_name(list_name *list);                                                 \
    type get_##list_name(list_name *list, size_t index);                                    \
    bool set_##list_name(list_name *list, size_t index, type Element);                      \
    int find_##list_name(list_name *list, type Element);                                    \
    void free_##list_name(list_name *list);                                                 \
    int size_##list_name(list_name *list);                                                  \
    int capacity_##list_name(list_name *list);                                              \
    bool empty_##list_name(list_name *list);                                                \
    void clear_##list_name(list_name *list);                                                \
    list_name *extend_##list_name(list_name *list_a, list_name *list_b);                    \
    bool insert_##list_name(list_name *list, size_t index, type Element);                   \
    bool remove_at_##list_name(list_name *list, size_t index);                              \
    void remove_##list_name(list_name *list, type Element);                                 \
    void print_##list_name(list_name *list, void (*printElement)(type));


#define ListDef(type, list_name)                                                               \
    List_errno get_errno_##list_name(list_name *list){                                         \
        if (list == NULL) {                                                                    \
            set_list_errno(LIST_NOT_EXIST);                                                    \
            return LIST_NOT_EXIST;                                                             \
        }                                                                                      \
        List_errno errno = list->err;                                                          \
        list->err = LIST_OK;                                                                   \
        global_list_errno = LIST_OK;                                                           \
        return errno;                                                                          \
}                                                                                              \
                                                                                               \
    void set_errno_##list_name(list_name *list, List_errno e){                                 \
        if (list == NULL) {                                                                    \
            set_list_errno(LIST_NOT_EXIST);                                                    \
            return;                                                                            \
        }                                                                                      \
        list->err = e;                                                                         \
        set_list_errno(e);                                                                     \
    }                                                                                          \
                                                                                               \
    void init_##list_name(list_name *list) {                                                   \
        if(list == NULL){                                                                      \
            set_list_errno(LIST_NOT_EXIST);                                                    \
            return;                                                                            \
        }                                                                                      \
        list->data = NULL;                                                                     \
        list->capacity = 0;                                                                    \
        list->count = 0;                                                                       \
        list->err = LIST_OK;                                                                   \
        set_list_errno(LIST_OK);                                                               \
    }                                                                                          \
                                                                                               \
    list_name *create_##list_name(){                                                           \
        list_name *newlist = (list_name*)malloc(sizeof(list_name));                            \
        if(newlist == NULL){                                                                   \
            set_list_errno(LIST_ALLOCATION_FAILED);                                            \
            return NULL;                                                                       \
        }                                                                                      \
        init_##list_name(newlist);                                                             \
        set_errno_##list_name(newlist, LIST_OK);                                               \
        return newlist;                                                                        \
}                                                                                              \
                                                                                               \
    void destroy_##list_name(list_name *list){                                                 \
        if(list == NULL){                                                                      \
            set_list_errno(LIST_NOT_EXIST);                                                    \
            return;                                                                            \
        }                                                                                      \
        free_##list_name(list);                                                                \
        free(list);                                                                            \
        set_list_errno(LIST_OK);                                                               \
    }                                                                                          \
                                                                                               \
    bool push_##list_name(list_name *list, type Element){                                      \
        if(list == NULL){                                                                      \
            set_list_errno(LIST_NOT_EXIST);                                                    \
            return false;                                                                      \
        }                                                                                      \
        if (list->capacity < list->count + 1){                                                 \
            if(!expand_##list_name(list)){                                                     \
                return false;                                                                  \
            }                                                                                  \
        }                                                                                      \
        list->data[list->count] = Element;                                                     \
        list->count++;                                                                         \
        set_errno_##list_name(list, LIST_OK);                                                  \
        return true;                                                                           \
    }                                                                                          \
                                                                                               \
    type pop_##list_name(list_name *list){                                                     \
        if(list == NULL){                                                                      \
            set_list_errno(LIST_NOT_EXIST);                                                    \
            return list_name##_default_element;                                                \
        }                                                                                      \
        if(list->count == 0){                                                                  \
            set_errno_##list_name(list, LIST_EMPTY);                                           \
            return list_name##_default_element;                                                \
        }                                                                                      \
        list->count--;                                                                         \
        if(list->count * 4 < list->capacity){                                                  \
            if(!shrink_##list_name(list)){                                                     \
                return false;                                                                  \
            }                                                                                  \
        }                                                                                      \
        set_errno_##list_name(list, LIST_OK);                                                  \
        return list->data[list->count];                                                        \
    }                                                                                          \
                                                                                               \
    bool resize_##list_name(list_name *list, int new_capacity){                                \
        if(list == NULL){                                                                      \
            set_list_errno(LIST_NOT_EXIST);                                                    \
            return false;                                                                      \
        }                                                                                      \
        if (new_capacity < 0){                                                                 \
            set_errno_##list_name(list, LIST_INVALID_CAPACITY);                                \
            return false;                                                                      \
        }                                                                                      \
        list->data = CHANGE_ARRAY(type, list->data, list->capacity, new_capacity);             \
        if(list->data == NULL){                                                                \
            set_errno_##list_name(list, LIST_ALLOCATION_FAILED);                               \
            return false;                                                                      \
        }                                                                                      \
        list->capacity = new_capacity;                                                         \
        list->count = list->count < new_capacity ? list->count : new_capacity;                 \
        set_errno_##list_name(list, LIST_OK);                                                  \
        return true;                                                                           \
}                                                                                              \
                                                                                               \
    bool expand_##list_name(list_name *list){                                                  \
        return resize_##list_name(list, GROW_CAPACITY(list->capacity));                        \
    }                                                                                          \
                                                                                               \
    bool shrink_##list_name(list_name *list){                                                  \
        return resize_##list_name(list, DECREASE_CAPACITY(list->capacity));                    \
    }                                                                                          \
                                                                                               \
    type first_##list_name(list_name *list){                                                   \
        if(list == NULL){                                                                      \
            set_list_errno(LIST_NOT_EXIST);                                                    \
            return list_name##_default_element;                                                \
        }                                                                                      \
        if(list->count == 0){                                                                  \
            set_errno_##list_name(list, LIST_EMPTY);                                           \
            return list_name##_default_element;                                                \
        }                                                                                      \
        set_errno_##list_name(list, LIST_OK);                                                  \
        return list->data[0];                                                                  \
    }                                                                                          \
                                                                                               \
    type back_##list_name(list_name *list){                                                    \
        if(list == NULL){                                                                      \
            set_list_errno(LIST_NOT_EXIST);                                                    \
            return list_name##_default_element;                                                \
        }                                                                                      \
        if(list->count == 0){                                                                  \
            set_errno_##list_name(list, LIST_EMPTY);                                           \
            return list_name##_default_element;                                                \
        }                                                                                      \
        set_errno_##list_name(list, LIST_OK);                                                  \
        return list->data[list->count-1];                                                      \
    }                                                                                          \
                                                                                               \
    type get_##list_name(list_name *list, size_t index){                                       \
        if(list == NULL){                                                                      \
            set_list_errno(LIST_NOT_EXIST);                                                    \
            return list_name##_default_element;                                                \
        }                                                                                      \
        if(index >= list->count){                                                              \
            set_errno_##list_name(list, LIST_OUT_OF_RANGE);                                    \
            return list_name##_default_element;                                                \
        }                                                                                      \
        set_errno_##list_name(list, LIST_OK);                                                  \
        return list->data[index];                                                              \
    }                                                                                          \
                                                                                               \
    bool set_##list_name(list_name *list, size_t index, type Element) {                        \
        if(list == NULL){                                                                      \
            set_list_errno(LIST_NOT_EXIST);                                                    \
            return false;                                                                      \
        }                                                                                      \
        if (index >= list->capacity){                                                          \
            set_errno_##list_name(list, LIST_OUT_OF_RANGE);                                    \
            return false;                                                                      \
        }                                                                                      \
        list->data[index] = Element;                                                           \
        list->count = index > list->count ? index : list->count;                               \
        set_errno_##list_name(list, LIST_OK);                                                  \
        return true;                                                                           \
    }                                                                                          \
                                                                                               \
    int find_##list_name(list_name *list, type Element){                                       \
        if(list == NULL){                                                                      \
            set_list_errno(LIST_NOT_EXIST);                                                    \
            return -1;                                                                         \
        }                                                                                      \
        set_errno_##list_name(list, LIST_OK);                                                  \
        for (int i = 0; i < list->count; i++){                                                 \
            if (list->data[i]==Element) {                                                      \
                return i;                                                                      \
            }                                                                                  \
        }                                                                                      \
        return -1;                                                                             \
    }                                                                                          \
                                                                                               \
    void free_##list_name(list_name *list){                                                    \
        if(list == NULL){                                                                      \
            set_list_errno(LIST_NOT_EXIST);                                                    \
            return;                                                                            \
        }                                                                                      \
        FREE_ARRAY(type, list->data, list->capacity);                                          \
        init_##list_name(list);                                                                \
        set_errno_##list_name(list, LIST_OK);                                                  \
    }                                                                                          \
                                                                                               \
    int size_##list_name(list_name *list) { return list->count; }                              \
                                                                                               \
    int capacity_##list_name(list_name *list) { return list->capacity; }                       \
                                                                                               \
    bool empty_##list_name(list_name *list) { return list->count == 0; }                       \
                                                                                               \
    void clear_##list_name(list_name *list) { free_##list_name(list); }                        \
                                                                                               \
    list_name *extend_##list_name(list_name *list_a, list_name *list_b) {                      \
        if (list_a == NULL) {                                                                  \
            set_list_errno(LIST_NOT_EXIST);                                                    \
            return NULL;                                                                       \
        }                                                                                      \
        if (list_b == NULL) {                                                                  \
            set_errno_##list_name(list_a, LIST_NOT_EXIST);                                     \
            return NULL;                                                                       \
        }                                                                                      \
        if(list_a->capacity < list_a->count + list_b->count){                                  \
            int new_capacity = next_power_of_2(list_a->count+list_b->count);                   \
            if(!resize_##list_name(list_a, new_capacity)){                                     \
                return NULL;                                                                   \
            }                                                                                  \
        }                                                                                      \
        memcpy(list_a->data + list_a->count, list_b->data, sizeof(type) * list_b->count);      \
        list_a->count += list_b->count;                                                        \
        set_errno_##list_name(list_a, LIST_OK);                                                \
        return list_a;                                                                         \
    }                                                                                          \
                                                                                               \
    bool insert_##list_name(list_name *list, size_t index, type Element) {                     \
        if (list == NULL) {                                                                    \
            set_list_errno(LIST_NOT_EXIST);                                                    \
            return false;                                                                      \
        }                                                                                      \
        if (index > list->count) {                                                             \
            set_errno_##list_name(list, LIST_OUT_OF_RANGE);                                    \
            return false;                                                                      \
        }                                                                                      \
        if (list->capacity < list->count + 1){                                                 \
            if(!expand_##list_name(list)){                                                     \
                return false;                                                                  \
            }                                                                                  \
        }                                                                                      \
        for (int i = list->count; i > index; i--) {                                            \
            list->data[i] = list->data[i - 1];                                                 \
        }                                                                                      \
        list->data[index] = Element;                                                           \
        list->count++;                                                                         \
        set_errno_##list_name(list, LIST_OK);                                                  \
        return true;                                                                           \
    }                                                                                          \
                                                                                               \
    bool remove_at_##list_name(list_name *list, size_t index) {                                \
        if (list == NULL) {                                                                    \
            set_list_errno(LIST_NOT_EXIST);                                                    \
            return false;                                                                      \
        }                                                                                      \
        if (index >= list->count) {                                                            \
            set_errno_##list_name(list, LIST_OUT_OF_RANGE);                                    \
            return false;                                                                      \
        }                                                                                      \
        for (int i = index; i < list->count - 1; i++) {                                        \
            list->data[i] = list->data[i + 1];                                                 \
        }                                                                                      \
        list->count--;                                                                         \
        if(list->count * 4 < list->capacity){                                                  \
            if(!shrink_##list_name(list)){                                                     \
                return false;                                                                  \
            }                                                                                  \
        }                                                                                      \
        set_errno_##list_name(list, LIST_OK);                                                  \
        return true;                                                                           \
    }                                                                                          \
                                                                                               \
    void remove_##list_name(list_name *list, type Element){                                    \
        if (list == NULL) {                                                                    \
            set_list_errno(LIST_NOT_EXIST);                                                    \
            return;                                                                            \
        }                                                                                      \
        int index = find_##list_name(list, Element);                                           \
        while (index != -1)                                                                    \
        {                                                                                      \
            remove_at_##list_name(list, index);                                                \
            index = find_##list_name(list, Element);                                           \
        }                                                                                      \
        set_errno_##list_name(list, LIST_OK);                                                  \
    }                                                                                          \
                                                                                               \
    void print_##list_name(list_name *list, void (*printElement)(type)){                       \
        if(list == NULL) {                                                                     \
            printf("NULL\n");                                                                  \
            set_list_errno(LIST_NOT_EXIST);                                                    \
            return;                                                                            \
        }                                                                                      \
        if(printElement == NULL){                                                              \
            set_errno_##list_name(list, LIST_INVALID_PRINTFN);                                 \
            return;                                                                            \
        }                                                                                      \
        printf("[");                                                                           \
        for (int i = 0; i < list->count; i++) {                                                \
            printElement(list->data[i]);                                                       \
            if(i < list->count - 1) {                                                          \
                printf(",");                                                                   \
            }                                                                                  \
        }                                                                                      \
        printf("]\n");                                                                         \
        set_errno_##list_name(list, LIST_OK);                                                  \
    }
#endif //C_LIST_H
