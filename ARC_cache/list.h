#ifndef DOUBLE_LIST
#define DOUBLE_LIST

typedef struct node node;
typedef struct LinkedList LinkedList;

struct node
{
	int val;
	node * next;
	node * prev;
};

struct LinkedList
{
	int size;
	int now_size;
	node * head;
	node * tail;
};

//LIST
node* create_node();
LinkedList* List(int size);
void list_free(LinkedList **list);
void pushFront(LinkedList *list, int data);
void popBack(LinkedList *list);
void print_list(LinkedList* list);

#endif
