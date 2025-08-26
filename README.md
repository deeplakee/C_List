# C-List

A lightweight **generic dynamic array implementation in C**, inspired by C++’s `std::vector`.
 C-List provides type-safe dynamic arrays with automatic resizing, error handling, and common list operations.

------

## ✨ Features

- Generic, type-safe dynamic arrays (via macros)
- Automatic growth and shrink
- Error handling system with per-list and global error codes
- Common operations: push, pop, insert, remove, extend, clear, find
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
  - `void destroy_MyList(MyList *list);`
  - `void init_MyList(MyList *list);`
  - `void free_MyList(MyList *list);`
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
  - `void clear_MyList(MyList *list);`
  - `MyList *extend_MyList(MyList *a, MyList *b);`
- **Utility**
  - `int find_MyList(MyList *list, T element);`
  - `void print_MyList(MyList *list, void (*printElement)(T));`

------

## ⚠️ Notes

- `LIST_INIT` must be used **once per program** (in one `.c` file).
- Default return values for errors come from a global `MyList##_default_element`. You should set this if needed.
- Global error code (`global_list_errno`) is **not thread-safe**.

------

## 📜 License

MIT License.

------
