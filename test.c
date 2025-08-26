#include "c_list.h"
#include<stdio.h>

LIST_INIT

ListDec(int, IntList)

ListDef(int, IntList)

void print_int(int value) {
    printf("%d", value);
}

int main(int argc, char const *argv[]) {

    IntList *a = create_IntList();

    //test push
    printf("test push\n");
    push_IntList(a, 1);
    push_IntList(a, 2);
    push_IntList(a, 100);
    printf("expect a: [1,2,100]\na: ");
    print_IntList(a, print_int);
    printf("end test\n\n");

    //test insert
    printf("test insert\n");
    insert_IntList(a, 1, 234);
    printf("expect a: [1,234,2,100]\na: ");
    print_IntList(a, print_int);
    printf("end test\n\n");

    //test find and set
    printf("test find and set\n");
    set_IntList(a, find_IntList(a, 1), 1111);
    printf("expect a: [1111,234,2,100]\na: ");
    print_IntList(a, print_int);
    printf("end test\n\n");

    //test extend
    printf("test extend\n");
    IntList *b = create_IntList();
    push_IntList(b, 1);
    push_IntList(b, 2);
    push_IntList(b, 3);
    extend_IntList(a, b);
    printf("expect a: [1111,234,2,100,1,2,3]\na: ");
    print_IntList(a, print_int);
    printf("end test\n\n");

    //test sizeof
    printf("test sizeof\n");
    printf("expect sizeof a: 7\n");
    printf("size of a: %d\n", size_IntList(a));
    printf("end test\n\n");


    //test get
    printf("test size get\n");
    printf("expect a: [1111,234,2,100,1,2,3]\n");
    for (size_t i = 0; i < size_IntList(a); i++) {
        printf("%d\n", get_IntList(a, i));
    }
    printf("end test\n\n");


    //test print
    printf("test print\n");
    printf("expect a: [1111,234,2,100,1,2,3]\na: ");
    print_IntList(a, print_int);
    printf("end test\n\n");

    //test find
    printf("test find\n");
    printf("expect index of 2 in a: 2\n");
    printf("index of 2 in a:%d\n", find_IntList(a, 2));
    printf("end test\n\n");

    //test pop
    printf("test pop\n");
    printf("a: [1111,234,2,100,1,2,3]\n");
    printf("pop from a: %d\n", pop_IntList(a));
    printf("end test\n\n");

    //test remove
    printf("test remove size get\n");
    printf("a: [1111,234,2,100,1,2]\nremove 2 from a\n");
    remove_IntList(a, 2);
    printf("after remove, size of a: %d\n", size_IntList(a));
    printf("then print a\n");
    for (size_t i = 0; i < size_IntList(a); i++) {
        printf("%d\n", get_IntList(a, i));
    }
    printf("end test\n\n");

    //test free
    printf("test free\n");
    free_IntList(a);
    printf("after free, size of a: %d\n", size_IntList(a));
    printf("end test\n\n");

    //test decrease when remove
    printf("test decrease\n");
    IntList *c = create_IntList();
    printf("init c and push 1-100\n");
    for (int i = 1; i <= 100; i++) {
        push_IntList(c, i);
    }
    printf("after push, capacity of c: %d\n", capacity_IntList(c));
    printf("remove 21-100 from c\n");
    for (int i = 100; i > 20; i--) {
        remove_IntList(c, i);
    }
    printf("after remove, capacity of c: %d\n", capacity_IntList(c));
    printf("c: ");
    print_IntList(c, print_int);
    printf("end test\n\n");

    destroy_IntList(a);
    destroy_IntList(b);
    destroy_IntList(c);

    return 0;
}
