#ifndef ARC_CACHE_H
#define ARC_CACHE_H

// Структура для узла двусвязного списка
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Структура для двусвязного списка
typedef struct {
    Node* head;
    Node* tail;
    int size;
} LinkedList;

// Структура для узла хэш-таблицы
typedef struct {
    int key;
    Node* value;
} HashNode;

// Структура для хэш-таблицы
typedef struct {
    int capacity;
    HashNode** array;
} HashTable;

// Структура для кэша ARC
typedef struct {
    int cache_size;
    int p;
    int c;
    int b1_size;
    int b2_size;
    LinkedList* t1;
    LinkedList* t2;
    LinkedList* b1;
    LinkedList* b2;
    HashTable* t1_cache;
    HashTable* t2_cache;
} ARC_Cache;

// Функции для работы с кэшем ARC
ARC_Cache* create_arc_cache(int cache_size);
void destroy_arc_cache(ARC_Cache* cache);
void cache_add(ARC_Cache* cache, int page);
void cache_delete(ARC_Cache* cache, int page);
int cache_lookup(ARC_Cache* cache, int page);

#endif /* ARC_CACHE_H */
