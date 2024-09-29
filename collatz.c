#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CACHE_CAPACITY 1000

typedef struct Node {  //Node
    int key;
    int value;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct { //data struct(hashmap) 
    Node* head;
    Node* tail;
    int capacity;
    int size;
    Node* map[CACHE_CAPACITY]; 
} LRUCache;

Node* create_node(int key, int value){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

LRUCache* create_cache(int capacity) {
    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
    cache->capacity = capacity;
    cache->size = 0;
    cache->head = NULL;
    cache->tail = NULL;

    for (int i = 0; i < CACHE_CAPACITY; i++) {
        cache->map[i] = NULL;
    }
    return cache;
}

void move_to_front(LRUCache* cache, Node* node) {
    if (cache->head == node) {
        return; 
    }
    if (node->prev) {
        node->prev->next = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    }
    if (cache->tail == node) {
        cache->tail = node->prev;
    }
    node->next = cache->head;
    node->prev = NULL;
    if (cache->head) {
        cache->head->prev = node;
    }
    cache->head = node;

    if (cache->tail == NULL) {
        cache->tail = node;
    }
}

void evict(LRUCache* cache) {
    if (cache->tail == NULL) {
        return; 
    }
    Node* toRemove = cache->tail;
    cache->map[toRemove->key % CACHE_CAPACITY] = NULL;
    if (cache->tail->prev) {
        cache->tail->prev->next = NULL;
    }
    cache->tail = cache->tail->prev;
    if (cache->tail == NULL) {
        cache->head = NULL;
    }
    free(toRemove);
    cache->size--;
}

void insert(LRUCache* cache, int key, int value) {
    int index = key % CACHE_CAPACITY;

    if (cache->map[index] != NULL && cache->map[index]->key == key) {
        cache->map[index]->value = value;
        move_to_front(cache, cache->map[index]);
    } else {
        
        if (cache->size == cache->capacity) {
            evict(cache); 
        }
        Node* newNode = create_node(key, value);
        cache->map[index] = newNode;
        newNode->next = cache->head;
        if (cache->head) {
            cache->head->prev = newNode;
        }
        cache->head = newNode;
        if (cache->tail == NULL) {
            cache->tail = newNode;
        }
        cache->size++;
    }
}

int get(LRUCache* cache, int key) {
    int index = key % CACHE_CAPACITY;

    if (cache->map[index] != NULL && cache->map[index]->key == key) {
        move_to_front(cache, cache->map[index]);
        return cache->map[index]->value;
    }
    return -1; 
}



int collatz_eq(int n, LRUCache* cache) //collatz equation
{   

    int cacheResult = get(cache,n);
    if (cacheResult != -1) {
        return cacheResult;
    }
    int steps = 0;
    int num = n;
    while (n != 1) {
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
        steps++;
    }
    insert(cache,num,steps);
    return steps;
}

int test_collaz(int N, int MIN, int MAX) //generates file and puts the num and steps onto csv
{
    LRUCache* cache = create_cache(CACHE_CAPACITY);
    const char *filename = "collatz_output.csv"; 
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(fp, "Number,Steps\n"); 

    for (int i = 0; i < N; i++) {
        int randomNumber = (rand() % (MAX - MIN + 1)) + MIN;
        fprintf(fp, "%d,", randomNumber); 

        int steps = collatz_eq(randomNumber,cache);
        fprintf(fp, "%d\n", steps); 
    }

    fclose(fp);
    printf("Steps exported to %s.\n", filename);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 4) {
        printf("Usage: %s <N> <MIN> <MAX>\n", argv[0]);
        return 1;  
    }

    int N = atoi(argv[1]);
    int MIN = atoi(argv[2]);
    int MAX = atoi(argv[3]);

    srand(time(NULL)); 

    if (test_collaz(N, MIN, MAX) != 0) {
        printf("Error in processing.\n");
        return 1;
    }

    return 0;
}
