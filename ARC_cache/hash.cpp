#include <stdio.h>
#include <stdlib.h>

// Определение enum для списков
typedef enum {
    T1,
    T2,
    B1,
    B2
} ListType;

// Определение структуры элемента хэш-таблицы
typedef struct HashItem {
    int key;
    ListType value;
} HashItem;

// Определение структуры хэш-таблицы
typedef struct HashTable {
    HashItem** items;
    int capacity;
} HashTable;

// Функция для создания нового элемента хэш-таблицы
HashItem* newHashItem(int key, ListType value) {
    HashItem* item = (HashItem*)malloc(sizeof(HashItem));
    item->key = key;
    item->value = value;
    return item;
}

// Функция для создания новой хэш-таблицы
HashTable* newHashTable(int capacity) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->items = (HashItem**)malloc(capacity * sizeof(HashItem*));
    for (int i = 0; i < capacity; i++) {
        table->items[i] = NULL;
    }
    table->capacity = capacity;
    return table;
}


// Функция для добавления элемента в хэш-таблицу
void hashTableAdd(HashTable* table, int key, ListType value) {
    int index = key % table->capacity;
    HashItem* item = newHashItem(key, value);
    table->items[index] = item;
}

// Функция для вывода содержимого хэш-таблицы
void printHashTable(HashTable* table) {
    printf("Содержимое хэш-таблицы: ");
    for (int i = 0; i < table->capacity; i++) {
        if (table->items[i] != NULL) {
            printf("%d (%d) ", table->items[i]->key, table->items[i]->value);
        }
    }
    printf("\n");
}

