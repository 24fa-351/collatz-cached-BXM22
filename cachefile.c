#include "cachefile.h"


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
