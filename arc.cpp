#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node node;
typedef struct LinkedList LinkedList;
typedef struct hashnode hashnode;
typedef struct Hash Hash;
typedef struct arc_cache arc_cache;

struct node {
    int val;
    node* next;
    node* prev;
};

struct LinkedList {
    int size;
    int now_size;
    node* head;
    node* tail;
};

struct hashnode {
    int value;
    node* point;
};

struct Hash {
    int capacity;
    hashnode** array;
};

struct arc_cache {
    LinkedList* t1;
    LinkedList* t2;
    LinkedList* b1;
    LinkedList* b2;
    Hash* p;
    int cache_size;
};

// Функции создания узла, списка, хэш-таблицы и кэша
node* create_node();
LinkedList* List(int size);
void list_free(LinkedList** list);
void pushFront(LinkedList* list, int data);
void popBack(LinkedList* list);
hashnode* create_hashnode(int value, node* point);
Hash* create_hash_table(int capacity);
arc_cache* init_arc_cache(int cache_size);

// Операции с кэшем
void cache_free(arc_cache* cache);
void cache_add(arc_cache* cache, int page);
void cache_delete(arc_cache* cache, int page);
void cache_lookup(arc_cache* cache, int page);

// Основная функция
int main() {
    // Инициализация кэша ARC
    arc_cache* cache = init_arc_cache(10);

    // Добавление элементов в кэш
    cache_add(cache, 1);
    cache_add(cache, 2);
    cache_add(cache, 3);

    // Поиск элемента в кэше
    cache_lookup(cache, 2); // Пример поиска элемента в кэше

    // Освобождение памяти, занимаемой кэшем
    cache_free(cache);

    return 0;
}

// Реализация функций

node* create_node() {
    node* new_node = (node*)malloc(sizeof(node));
    return new_node;
}

LinkedList* List(int size) {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->size = size;
    list->now_size = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void list_free(LinkedList** list) {
    node* tmp = (*list)->head;
    node* next = NULL;
    while (tmp) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}

void pushFront(LinkedList* list, int data) {
    node* tmp = (node*)malloc(sizeof(node));
    if (tmp == NULL) {
        exit(1);
    }
    tmp->val = data;
    tmp->next = list->head;
    tmp->prev = NULL;
    if (list->head) {
        list->head->prev = tmp;
    }
    list->head = tmp;
    if (list->tail == NULL) {
        list->tail = tmp;
    }
    list->now_size++;
}

void popBack(LinkedList* list) {
    node* next;
    if (list->tail == NULL) {
        exit(4);
    }
    next = list->tail;
    list->tail = list->tail->prev;
    if (list->tail) {
        list->tail->next = NULL;
    }
    if (next == list->head) {
        list->head = NULL;
    }
    free(next);
    list->now_size--;
}

hashnode* create_hashnode(int value, node* point) {
    hashnode* tmp = (hashnode*)malloc(sizeof(hashnode));
    tmp->value = value;
    tmp->point = point;
    return tmp;
}

Hash* create_hash_table(int capacity) {
    Hash* hash = (Hash*)malloc(sizeof(Hash));
    hash->capacity = capacity;
    hash->array = (hashnode**)malloc(capacity * sizeof(hashnode*));
    for (int i = 0; i < capacity; i++) {
        hash->array[i] = NULL;
    }
    return hash;
}

arc_cache* init_arc_cache(int cache_size) {
    arc_cache* cache = (arc_cache*)malloc(sizeof(arc_cache));
    cache->t1 = List(cache_size);
    cache->t2 = List(cache_size);
    cache->b1 = List(cache_size);
    cache->b2 = List(cache_size);
    cache->p = create_hash_table(2 * cache_size);
    cache->cache_size = cache_size;
    return cache;
}

void cache_free(arc_cache* cache) {
    list_free(&(cache->t1));
    list_free(&(cache->t2));
    list_free(&(cache->b1));
    list_free(&(cache->b2));
    free(cache->p->array);
    free(cache->p);
    free(cache);
}

void cache_add(arc_cache* cache, int page) {
    // Проверяем наличие страницы в кэше
    int is_in_cache = cache_lookup(cache, page);

    if (is_in_cache) {
        // Если страница уже в кэше, перемещаем её в соответствующий список T1 или T2
        if (is_in_cache == 1) {
            // Перемещаем из T2 в T1
            exchange(cache->t2, page);
            pushFront(cache->t1, page);
        } else {
            // Перемещаем из T1 в T2
            exchange(cache->t1, page);
            pushFront(cache->t2, page);
        }
    } else {
        // Если страницы нет в кэше
        if (cache->t1->now_size + cache->b1->now_size == cache->cache_size) {
            // Если объединенный размер T1 и B1 равен размеру кэша, то удаляем страницу из B1
            if (cache->t1->now_size < cache->cache_size) {
                // Удаление LRU страницы из B1
                cache_delete(cache, cache->b1->tail->val);
            } else {
                // Удаление LRU страницы из T1
                popBack(cache->t1);
            }
        } else {
            // Если объединенный размер T1 и B1 меньше размера кэша, то удаляем страницу из B2
            if (cache->t1->now_size + cache->b1->now_size + cache->t2->now_size + cache->b2->now_size >= cache->cache_size) {
                // Удаление LRU страницы из B2
                cache_delete(cache, cache->b2->tail->val);
            }
        }

        // Добавление страницы в кэш в соответствии с алгоритмом ARC
        if (cache->t1->now_size < cache->cache_size && ((cache->t1->now_size + cache->b1->now_size) < cache->cache_size)) {
            pushFront(cache->t1, page);
        } else {
            pushFront(cache->t2, page);
        }

        // Добавление страницы в хэш-таблицу
        add_value_to_hash(page, cache->t1->head, cache->p, page);
    }
}


void cache_delete(arc_cache* cache, int page) {
    int data = find_element_in_hash(cache->p, page);
    if (data != -1) {
        delete_from_hash(cache->p, data);
        if (cache->t1->now_size != 0 && find_element_in_hash(cache->t1->head, page) != -1) {
            popBack(cache->t1);
        } else if (cache->t2->now_size != 0 && find_element_in_hash(cache->t2->head, page) != -1) {
            popBack(cache->t2);
        } else if (cache->b1->now_size != 0 && find_element_in_hash(cache->b1->head, page) != -1) {
            popBack(cache->b1);
        } else if (cache->b2->now_size != 0 && find_element_in_hash(cache->b2->head, page) != -1) {
            popBack(cache->b2);
        }
    }
}

int cache_lookup(arc_cache* cache, int page) {
    int data = find_element_in_hash(cache->p, page);
    if (data != -1) {
        if (cache->t1->now_size != 0 && find_element_in_hash(cache->t1->head, page) != -1) {
            return 1;
        } else if (cache->t2->now_size != 0 && find_element_in_hash(cache->t2->head, page) != -1) {
            return 2;
        } else if (cache->b1->now_size != 0 && find_element_in_hash(cache->b1->head, page) != -1) {
            return 3;
        } else if (cache->b2->now_size != 0 && find_element_in_hash(cache->b2->head, page) != -1) {
            return 4;
        }
    }
    return 0;
}

int main() {
    // Размер кэша
    int cache_size = 5;

    // Создание кэша
    arc_cache* cache = create_arc_cache(cache_size);

    // Добавление страниц в кэш
    cache_add(cache, 1);
    cache_add(cache, 2);
    cache_add(cache, 3);
    cache_add(cache, 4);
    cache_add(cache, 5);

    // Проверка присутствия страниц в кэше
    printf("Page 3 is%s in the cache\n", cache_lookup(cache, 3) ? "" : " not");
    printf("Page 6 is%s in the cache\n", cache_lookup(cache, 6) ? "" : " not");

    // Удаление страниц из кэша
    cache_delete(cache, 4);

    // Проверка присутствия страниц в кэше после удаления
    printf("Page 4 is%s in the cache after deletion\n", cache_lookup(cache, 4) ? "" : " not");

    // Освобождение памяти, выделенной для кэша
    destroy_arc_cache(cache);

    return 0;
}
