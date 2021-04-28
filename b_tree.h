#ifndef B_TREE
#define B_TREE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int key_type;

typedef struct _Data{
	int first;
	int second;
	char *string;
} Data;

typedef struct _Tree_element{
	key_type key;
	struct _Data *data;
	struct _Tree_element *left;
	struct _Tree_element *right;
	struct _Tree_element *parent;
} Tree_element;

typedef struct _Tree{
	struct _Tree_element *root;
} Tree;


//char *get_str();
Data *create_data(void);
key_type input_key(void);
Tree *create_tree(void);
//Tree_element *create_tree_element(key_type key, Data *data, Tree_element *parent);
Data *insert(Tree *tree, key_type key, Data *data);
//void print_tree_rec(Tree_element *element);
int print_tree(Tree* tree);
//Tree_element *get_ptr_by_key(Tree *tree, key_type key);
//Tree_element *find_max_element(Tree_element *element);
//void remove_element_ptr(Tree *tree, Tree_element *element, int mod);
void remove_element(Tree *tree, key_type key);
Data *get_data_by_key(Tree *tree, key_type key);
Tree_element *get_smallest_among_bigger_ptr(Tree *tree, key_type pending);
Data *get_smallest_among_bigger(Tree *tree, key_type pending);
//void del_element(Tree_element *element);
//void del_tree_rec(Tree_element *element);
void del_tree(Tree *tree);
int get_int(int *a);
void print_data(Data *data);
//void print_beauty_tree_rec(Tree_element *element, int level, int mod);
int print_beauty_tree(Tree *tree);
//int int_len(int a);
void input_from_file(Tree *tree);

#endif