#include "list.h"
#include<stdio.h>

ListDec(int, intList)
ListDef(int, intList)

int main(int argc, char const *argv[])
{

    intList a;
    init_intList(&a);
    //test push
    push_intList(&a, 1);
    push_intList(&a, 2);
    push_intList(&a, 100);
    //test insert
    insert_intList(&a,1,234);
    //test find and set
    set_intList(&a,find_intList(&a,1),1111);

    //test extend
    intList ll;
    init_intList(&ll);
    push_intList(&ll, 1);
    push_intList(&ll, 2);
    push_intList(&ll, 3);
    extend_intList(&a,&ll);

    //test sizeof
    printf("size of a:%d\n", size_of_intList(&a));

    for (size_t i = 0; i < size_of_intList(&a); i++)
    {
        //test get
        printf("%d\n", *get_intList(&a, i));
    }

    //test find
    printf("index of 2 in a:%d\n",find_intList(&a,2));

    //test pop
    printf("last of a:%d\n",pop_intList(&a));
    printf("size of a:%d\n", size_of_intList(&a));

    //test remove
    remove_intList(&a,2);
    printf("size of a:%d\n", size_of_intList(&a));
    for (size_t i = 0; i < size_of_intList(&a); i++)
    {
        printf("%d\n", *get_intList(&a, i));
    }

    //test free
    free_intList(&a);
    printf("size of a:%d\n", size_of_intList(&a));

    return 0;
}