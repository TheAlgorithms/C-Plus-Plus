// Copyright 2020 Arctic2333
#include <stdlib.h>
#include<stdio.h>
#define MAX 6
# define HASHMAX 5
// Hash Search Algorithm
// Best Time Complexity Ω(1)
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
// In this algorithm, we use the method of division and reservation remainder to construct the hash function, 
// and use the method of chain address to solve the conflict, that is, we link a chain list after the data, 
// and store all the records whose keywords are synonyms in the same linear chain list.
void create_list(int key) {  // Construct hash table
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
    } else {
        hashtab[index].next = n; }
}
int hash_search(int key) {  // Hash lookup function
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
    while (index < MAX) {  // Construct hash table
        create_list(data[index]);
        index++;
    }
    for (i = 0; i < HASHMAX; i++) {  // Output hash table
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
