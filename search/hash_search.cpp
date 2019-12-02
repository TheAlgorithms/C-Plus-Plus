// Copyright 2020 Arctic2333
#include <stdlib.h>
#include<stdio.h>
#define MAX 6
# define HASHMAX 5
int data[MAX] = { 12, 160, 219, 522, 725, 9997};
typedef struct list {
    int key;
    struct list * next;
}
node, * link;
node hashtab[HASHMAX];
int counter = 1;
int h(int key) {
    return key % HASHMAX;
}
void create_list(int key) {
    link p, n;
    int index;
    n = (link) malloc(sizeof(node));
    n -> key = key;
    n -> next = NULL;
    index = h(key);
    p = hashtab[index].next;
    if (p != NULL) {
        n -> next = p;
        hashtab[index].next = n;
    } else
        hashtab[index].next = n;
}
int hash_search(int key) {
    link pointer;
    int index;
    counter = 0;
    index = h(key);
    pointer = hashtab[index].next;
    printf("data[%d]:", index);
    while (pointer != NULL) {
        counter++;
        printf("data[%d]:", pointer -> next);
        if (pointer -> key == key)
            return 1;
        else
            pointer = pointer -> next;
    }
    return 0;
}
int main() {
    link p;
    int key, index, i;
    index = 0;
    printf("input data:");
    for (i = 0; i < HASHMAX; i++)
        scanf("%d", & data[i]);
    printf("\n");
    while (index < MAX) {
        create_list(data[index]);
        index++;
    }
    for (i = 0; i < HASHMAX; i++) {
        printf("hashtab [%d]", i);
        printf("n");
        p = hashtab[i].next;
        while (p != NULL) {
            printf("please int key:");
            if (p -> key > 0)
                printf("[%d]", p -> key);
            p = p -> next;
        }
        printf("\n");
    }
    while (key != -1) {
        printf("please input data\n");
        scanf("%d", & key);
        if (hash_search(key))
            printf("search time = %d\n", counter);
        else
            printf("no found!\n");
    }
    return 0;
}
