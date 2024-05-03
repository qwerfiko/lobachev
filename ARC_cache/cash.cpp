#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "hash.cpp"
#include "list.cpp"


int main() {
    // Создаем четыре списка
    LinkedList* T1 = List(100); // Замените 100 на нужный размер
    LinkedList* T2 = List(100);
    LinkedList* B1 = List(100);
    LinkedList* B2 = List(100);

    // Добавляем число 2 в список T1
    pushFront(T1, 2);

    // Выводим содержимое всех списков
    printf("Содержимое списка T1: ");
    node* tmp = T1->head;
    while (tmp != NULL) {
        printf("%d ", tmp->val);
        tmp = tmp->next;
    }
    printf("\n");

    // Повторите этот процесс для списков T2, B1 и B2

    return 0;
}




