#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "hash.cpp"
#include "list.cpp"


int main() {
    // Создаем новую хэш-таблицу
    HashTable* table = newHashTable(1000);

    // Создаем списки
    LinkedList* listT1 = List(100);
    LinkedList* listT2 = List(100);
    LinkedList* listB1 = List(100);
    LinkedList* listB2 = List(100);

    //
    pushFront(listT1, 2);

    //IsPresent(listT1, 2);

    pushFront (listT2, 3);


    hashTableAdd(table, 2, T1);

    hashTableAdd(table, 3, T2);


    // Выводим содержимое списка T1
    printf("Содержимое списка T1: ");
    print_list(listT1);
    printf("\n");
     printf("Содержимое списка T2: ");
    print_list(listT2);
    printf("\n");

    printHashTable(table);

    return 0;
}







