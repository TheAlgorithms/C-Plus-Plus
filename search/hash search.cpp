    // Copyright 2020 Arctic2333
    #include <stdlib.h>

    #include <stdio.h>

    # define MAX 6

    # define HASHMAX 5
    // Hash Search Algorithm
    // Best Time Complexity Ω(1)
    int data[MAX] = {
        12,
        160,
        219,
        522,
        725,
        9997
    };
    int hashtab[HASHMAX];
    int counter = 1;
    int h(int key) {  // hash function 
        return key % HASHMAX;
    }
    int collision(int * address) {  // Linear probe hashes to handle conflicts
        return ( * address + 1) % HASHMAX;
    }
    int create_list(int key) {
        int hashtime = 0;
        int collisiontime = 0;
        int * address, i;
        * address = h(key);
        while (hashtime < HASHMAX) {
            if (hashtab[ * address] == 0) {
                hashtab[ * address] = key;
                printf("key:%d=>address%d\n", key, * address);
                for (i = 0; i < HASHMAX; i++)
                    printf("[%d]", hashtab[i]);
                printf("\n");
                return 1;
            } else {
                collisiontime++;
                printf("collision:%d=>address%d\n", collisiontime, * address);
                * address = collision(address);
            }
            hashtime++;
        }
        return 0;
    }
    int hash_search(int key) {
        int * address;
        counter = 0;
        * address = h(key);
        while (counter < HASHMAX) {
            counter++;
            if (hashtab[ * address] == key)
                return 1;
            else {
                * address = collision(address);
            }
        }
        return 0;
    }
    main() {
        int key, index, i;
        index = 0;
        printf("input data:");
        for (i = 0; i < HASHMAX; i++)
            scanf("%d", & data[i]);
        printf("\n");
        for (i = 0; i < HASHMAX; i++) {
            hashtab[i] = 0;
        }
        while (index < MAX) {
            if (create_list(data[index]))
                printf("hash success!\n");
            else {
                printf("hash fulled!\n");
            }
            index++;
        }
        for (i = 0; i < HASHMAX; i++)
            printf("[%d]", hashtab[i]);
        printf("\n");
        while (key != 1) {
            printf("please input key");
            scanf("%d", & key);
            if (hash_search(key))
                printf("search time = %d\n", counter);
            else {
                printf("no found!\n");
            }

        }

    }