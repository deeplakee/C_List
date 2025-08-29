# C-List

A lightweight **generic dynamic array implementation in C**, inspired by C++’s `std::vector`.
 C-List provides type-safe dynamic arrays with automatic resizing, error handling, and common list operations.

------

## ✨ Features

- Generic, type-safe dynamic arrays (via macros)
- Automatic growth and shrink
- Error handling system with per-list and global error codes
- Common operations: push, pop, insert, remove, extend, clear, find, replace, sublist
- Interoperability with raw C arrays (`from_array`, `to_array`)
- Easy to print using custom callbacks
- Header-only (just include and use)

------

## 🚀 Getting Started

### 1. Include the header

```c
#include "c_list.h"
```

------

### 2. Initialize the library (once per project)

In **one source file only** (e.g., `main.c`), initialize the global error system:

```c
LIST_INIT
```

------

### 3. Declare and define a list type

Use the provided macros to declare and define a list for your chosen type:

```c
ListDec(int, IntList)   // Declare a dynamic array of int
ListDef(int, IntList)   // Define the implementation
```

This creates a type-safe `IntList` dynamic array with its own API.

------

### 4. Example

```
#include <stdio.h>
#include "c_list.h"

LIST_INIT

// Define IntList
ListDec(int, IntList)
ListDef(int, IntList)

void print_int(int x) {
    printf("%d", x);
}

int main() {
    IntList *list = create_IntList();

    push_IntList(list, 10);
    push_IntList(list, 20);
    push_IntList(list, 30);

    print_IntList(list, print_int);  // [10,20,30]

    pop_IntList(list);               // remove last element
    print_IntList(list, print_int);  // [10,20]

    destroy_IntList(list);
    return 0;
}
```

------

## ⚡ API Overview

For a list defined as:

```
ListDec(T, MyList)
ListDef(T, MyList)
```

you get the following functions (examples with `MyList`):

- **Creation / Destruction**
  - `MyList *create_MyList();`
  - `MyList *from_array_MyList(T *arr, size_t len);`
  - `void destroy_MyList(MyList *list);`
- **Capacity / Size**
  - `int size_MyList(MyList *list);`
  - `int capacity_MyList(MyList *list);`
  - `bool empty_MyList(MyList *list);`
  - `bool resize_MyList(MyList *list, int new_capacity);`
- **Element Access**
  - `T first_MyList(MyList *list);`
  - `T back_MyList(MyList *list);`
  - `T get_MyList(MyList *list, size_t index);`
  - `bool set_MyList(MyList *list, size_t index, T element);`
- **Modifiers**
  - `bool push_MyList(MyList *list, T element);`
  - `T pop_MyList(MyList *list);`
  - `bool insert_MyList(MyList *list, size_t index, T element);`
  - `bool remove_at_MyList(MyList *list, size_t index);`
  - `void remove_MyList(MyList *list, T element);`
  - `void replace_MyList(MyList *list, T oldElement, T newElement);`
  - `void clear_MyList(MyList *list);`
  - `MyList *extend_MyList(MyList *a, MyList *b);`
- **Utility**
  - `void init_MyList(MyList *list);`
  - `void free_MyList(MyList *list);`
  - `T *to_array_MyList(MyList *list);`
  - `int find_MyList(MyList *list, T element);`
  - `void print_MyList(MyList *list, void (*printElement)(T));`
  - `MyList *sublist_MyList(MyList *list, size_t start, size_t end);`

------

## ⚠️ Error Handling

C-List uses error codes to report problems.
There are two ways to check errors:

1. **Global errors** (from last operation):

   ```c
   List_errno err = get_list_errno();
   const char *msg = list_errno_str(err);
   ```
   or 
   ```c
   const char *msg = clean_list_errno();
   ```

2. **Per-list errors** (specific list):

   ```c
   List_errno err = get_errno_MyList(list);
   const char *msg = list_errno_str(err);
   ```

### Error Codes

| Code                     | Value | Meaning                                                    |
| ------------------------ | ----- | ---------------------------------------------------------- |
| `LIST_OK`                | `0`   | No error                                                   |
| `LIST_NOT_EXIST`         | `1`   | List pointer is `NULL`                                     |
| `LIST_EMPTY`             | `2`   | List is empty                                              |
| `LIST_OUT_OF_RANGE`      | `3`   | Index out of bounds                                        |
| `LIST_ALLOCATION_FAILED` | `4`   | Memory allocation failed                                   |
| `LIST_INVALID_PRINTFN`   | `5`   | Invalid print callback function                            |
| `LIST_INVALID_CAPACITY`  | `6`   | Invalid capacity (e.g., negative or zero when not allowed) |
| `LIST_INVALID_RAW_ARRAY` | `7`   | Invalid input raw array (e.g., `NULL` or invalid length)   |

------

## ⚠️ Notes

- `LIST_INIT` must be used **once per program** (in one `.c` file).
- Default return values for errors come from a global `MyList##_default_element`. You should set this if needed.
- Global error code (`global_list_errno`) is **not thread-safe**.

------

## 📜 License

MIT License.

------
