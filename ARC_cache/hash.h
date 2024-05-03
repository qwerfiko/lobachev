#ifndef HASH_TABLE
#define HASH_TABLE
#include "list.h"

typedef struct hashnode hashnode;
typedef struct Hash Hash;
typedef struct cash cash;



struct hashnode
{
	int value;
	node * point;
};

struct Hash
{
	int capacity;
	hashnode **array;
};

struct cash
{
	LinkedList * list;
	Hash * table;
	int size_L;
	int size_T;

};

//HASH
hashnode* create_node_h(int value, node *point);
Hash* delete_from_hash(Hash *hash, int k);
hashnode **init_array(int capacity);
Hash* create_HASH_TABLE(int size_Table);
void free_item(hashnode *node);
void free_HASH(Hash *hash);
int find_element_in_hash(Hash *hash, int page);
int search_for_empty_place_in_hash(Hash *hash);
void add_value_to_hash(int page, node *list, Hash *hash, int i);
void hash_add(cash *cash, int page, node *list);
void hash_delete(cash *cash, int page);
//CASH
cash* init_cash(int size_List, int size_Table);
void free_cash(cash *CASH);
void push(cash *cash, int page);
void exchange(cash *cash, int data);
//
int init_value_in_list(cash *Cash, int page);
int print(cash *cash, int *array, int size);

#endif
