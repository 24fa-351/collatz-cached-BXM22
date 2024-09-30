#ifndef cachefile_H
#define cachefile_H

#define CACHE_CAPACITY 1000

typedef struct Node {  //Node
    int key;
    int value;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct { //data struct
    Node* head;
    Node* tail;
    int capacity;
    int size;
    Node* map[CACHE_CAPACITY]; 
} LRUCache;

Node* create_node(int key, int value);

LRUCache* create_cache(int capacity);

void move_to_front(LRUCache* cache, Node* node);

void evict(LRUCache* cache);

void insert(LRUCache* cache, int key, int value);

int get(LRUCache* cache, int key);

#endif