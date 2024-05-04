#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

//LIST
node* create_node()
{
	node *new_node = (node*) malloc(sizeof(node));
	return new_node;
}

LinkedList* List(int size)
{
	LinkedList *list = NULL;
	list = (LinkedList*) malloc((sizeof(LinkedList)));
	list->size = size;
	list->now_size = 0;
	list->head = NULL;
	list->tail = NULL;

	return list;

}

void list_free(LinkedList **list)
{
	node *tmp = (*list)->head;
	node *next = NULL;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}

	free(*list);
	(*list) = NULL;
}

void pushFront(LinkedList *list, int data)
{
	node *tmp = (node*) malloc(sizeof(node));
	if (tmp == NULL)
	{
		exit(1);
	}

	tmp->val = data;
	tmp->next = list->head;
	tmp->prev = NULL;
	if (list->head)
	{
		list->head->prev = tmp;
	}

	list->head = tmp;

	if (list->tail == NULL)
	{
		list->tail = tmp;
	}

	list->now_size++;
}

void popBack(LinkedList *list)
{
	node * next;
	if (list->tail == NULL)
	{
		exit(4);
	}

	next = list->tail;
	list->tail = list->tail->prev;
	if (list->tail)
	{
		list->tail->next = NULL;
	}

	if (next == list->head)
	{
		list->head = NULL;
	}

	free(next);

	list->now_size--;

}


void print_list(LinkedList* list) {
    node* current = list->head;
    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
}
