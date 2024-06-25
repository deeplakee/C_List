# C_List

a simple list implement for C
provide function below

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
