# C_List: A Generic List Library for C

C-List is a generic list library for C, providing dynamic array functionality with a set of utility functions for managing lists of any data type.

## Features

- Dynamic array resizing
- Push and pop operations
- Element access and modification
- Find, insert, and remove operations
- List concatenation
- Clear and free functions

##### The functions below are available.

```C
void init(list_name *list);
void push(list_name *list, type Element);
type pop(list_name *list);
type *get(list_name *list, int index);
bool set(list_name *list, int index, type Element);
int find(list_name *list, type Element);
void free_##(list_name *list);
int size_of(list_name *list);
bool is_empty(list_name *list);
void clear(list_name *list);
list_name* extend(list_name *list_a, list_name *list_b);
bool insert(list_name *list, int index, type Element);
bool remove_at(list_name *list, int index);
void remove(list_name *list, type Element);
```

## Usage

### Including the Library

To use the C-List library in your project, include the `c_list.h` header file:

```c
#include "c_list.h"
```

### Use the macros

Then you can Define a list for your specific data type using the `ListDec` and `ListDef` macros:

```c
ListDec(type, list_name)
ListDef(type, list_name)
```

