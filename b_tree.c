#include "b_tree.h"

static char *get_str(){
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n = 0;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        } else if (n > 0) {
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
    }
    return res;
}


static char *fget_str(FILE *file) {
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n = 0;
    do {
        n = fscanf(file, "%80[^\n]", buf);
        if (n == EOF) return NULL;
        else if (n < 0) {
            if (!res) {
                return NULL;
            }
        } else if (n > 0) {
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            fscanf(file, "%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
    }

    return res;
}


int get_int(int *a){
    int n;
    do{
        n = scanf("%d", a);
        if (n < 0) return 1;
        if (n == 0){
            printf("Error!\n");
            scanf("%*c");
        }
    } while (n == 0);
    return 0;
}


Data *create_data(void){
	int first = 0, second = 0;
	char *string;
	printf("Enter the first number:\n");
	get_int(&first);
	printf("Enter the second number:\n");
	get_int(&second);
	scanf("%*c");
	printf("Enter the string:\n");
	string = get_str();
	
	Data *data = (Data*)malloc(sizeof(Data));
	data->first = first;
	data->second = second;
	data->string = string;
	return data;
}


void print_data(Data *data){
	printf("First number -> %d\n", data->first);
	printf("Second number -> %d\n", data->second);
	printf("String -> %s\n", data->string);
}


key_type input_key(void){
	key_type key;
	printf("Enter the key:\n");
	get_int(&key);
	return key;
}


Tree *create_tree(void){
	Tree *tree = (Tree*)malloc(sizeof(Tree));
	tree->root = NULL;
	return tree;
}


static Tree_element *create_tree_element(key_type key, Data *data, Tree_element *parent){
	Tree_element *tree_element = (Tree_element*)malloc(sizeof(Tree_element));
	tree_element->key = key;
	tree_element->data = data;
	tree_element->parent = parent;
	tree_element->left = tree_element->right = NULL;
	return tree_element;
}


static void del_element(Tree_element *element){
	free(element->data->string);
	free(element->data);
	free(element);
}


Data *insert(Tree *tree, key_type key, Data *data){
	if (!tree->root){
		tree->root = create_tree_element(key, data, NULL);
		return NULL;
	}
	Tree_element *now = tree->root;
	while(now){
		if (key>now->key){
			if (now->right){
				now = now->right;
				continue;
			}
			else{
				now->right = create_tree_element(key, data, now);
				return NULL;
			}
		}
		else if (key<now->key){
			if (now->left){
				now = now->left;
				continue;
			}
			else{
				now->left = create_tree_element(key, data, now);
				return NULL;
			}
		}
		else{
			printf("~~~We have already the same key~~~\n");
			Data *tmp;
			tmp = now->data;
			now->data = data;
			return tmp;
		}
	}
}


static Tree_element *get_ptr_by_key(Tree *tree, key_type key){
	if (tree->root){
		Tree_element *now = tree->root;
		while(now){
			if (now->key==key) return now;
			else if (now->key>key) now = now->left;
			else now = now->right;
		}
		//printf("Element not found\n");
		return NULL;
	} else{
		//printf("Tree is empty\n");
		return NULL;
	}
}


Data *get_data_by_key(Tree *tree, key_type key){
	Tree_element *element = get_ptr_by_key(tree, key);
	if (element) return element->data;
	else{
		printf("Element not found\n");
		return NULL;
	}
}


Tree_element *get_smallest_among_bigger_ptr(Tree *tree, key_type pending){
	if (tree->root){
		Tree_element *now = tree->root;
		Tree_element *possible = NULL;
		while(now->right || now->left){
			if (now->key>pending){
				if (now->left) {
					//printf("E1\n");
					possible = now;
					now = now->left;
				}
				else return now;
			} else{
				//printf("E3\n");
				if (now->right) now = now->right;
				else {
					if (now->key<=pending){
						//printf("E2\n");
						if (possible) return possible;
						else{
							//printf("Element not found\n");
							return NULL;
						}
					} else return now;
				}
			}
		}
		if (now->key>pending) return now;
		else{
			if (possible) return possible;
			else{
				//printf("Element not found\n");
				return NULL;
			}
		}
	} else{
		printf("Tree is empty\n");
		return NULL;
	}
}


Data *get_smallest_among_bigger(Tree *tree, key_type pending){
	Tree_element *element = get_smallest_among_bigger_ptr(tree, pending);
	if (element) return element->data;
	else return NULL;
}


static void print_tree_rec(Tree_element *element){
	if (element){
		print_tree_rec(element->left);
		printf("key=%d first=%d, second=%d, string=%s\n", element->key, element->data->first, 
			element->data->second, element->data->string);
		print_tree_rec(element->right);
	}
}


int print_tree(Tree* tree){
	if (tree->root){
		printf("Tree:\n");
		print_tree_rec(tree->root);
		printf("\n");
		return 0;
	} else {
		printf("Tree is empty\n");
		printf("\n");
		return 1;
	}
}


static Tree_element *find_max_element(Tree_element *element){
	while(element->right) element = element->right;
	return element;
}


static void remove_element_ptr(Tree *tree, Tree_element *element, int mod){
    if (element->left && element->right) {
		//printf("E1\n");
        Tree_element *localMax = find_max_element(element->left);
		//printf("E2\n");
		element->key = localMax->key;
		free(element->data->string);
		free(element->data);
        element->data = localMax->data;
        remove_element_ptr(tree, localMax, 0);
        return;
    } else if (element->left) {
		//printf("E3\n");
		if (element->parent){
			if (element == element->parent->left) {
				element->parent->left = element->left;
			} else {
				element->parent->right = element->left;
			}
			element->left->parent = element->parent;
		} else{
			tree->root = element->left;
			element->left->parent = NULL;
		}
    } else if (element->right){
		//printf("E4\n");
		if (element->parent){
			if (element == element->parent->right) {
				element->parent->right = element->right;
			} else {
				element->parent->left = element->right;
			}
			element->right->parent = element->parent;
		} else{
			tree->root = element->right;
			element->right->parent = NULL;
		}
    } else {
		//printf("E5\n");
		if (element->parent){
			if (element == element->parent->left) {
				element->parent->left = NULL;
			} else {
				element->parent->right = NULL;
			}
		} else{
			tree->root = NULL;
		}
    }
	if (mod) del_element(element);
	else free(element);
}


void remove_element(Tree *tree, key_type key){
	Tree_element *element = get_ptr_by_key(tree, key);
	if (element) remove_element_ptr(tree, element, 1);
	else printf("Element not found\n");
}


static void del_tree_rec(Tree_element *element){
	if (element){
		//printf("%d ", element->key);
		del_tree_rec(element->left);
		del_tree_rec(element->right);
		del_element(element);
	}
}


void del_tree(Tree *tree){
	printf("Clearing...\n");
	if (tree->root){
		Tree_element *now = tree->root;
		del_tree_rec(now);
		tree->root = NULL;
		printf("Done!\n");
		return;
	} else{
		printf("The tree has already been cleared\n");
		return;
	}
}


static int int_len(int a){
	int len = 0;
	if (a<=0) len++;
	while(a){
		a/=10;
		len++;
	}
	return len;
}


static void print_beauty_tree_rec(Tree_element *element, int level, int mod){
	if (element){
		if (mod){
			for (int i=0; i<level-2; i++) printf(" ");
			printf("\\_");
		}
		printf("%d", element->key);
		level += 1 + int_len(element->key);
		if (element->left) printf("_");
		print_beauty_tree_rec(element->left, level, 0);
		if (element->right) printf("\n");
		print_beauty_tree_rec(element->right, level, 1);
	}
}


int print_beauty_tree(Tree *tree){
	if (tree->root){
		printf("Tree:\n");
		print_beauty_tree_rec(tree->root, 0, 0);
		printf("\n");
		return 0;
	} else {
		printf("Tree is empty\n");
		printf("\n");
		return 1;
	}
}


void input_from_file(Tree *tree){
	char name[] = "debug.txt";
	FILE *file;
	char *string;
	int first, second, key;
	Data *data;
	if ((file = fopen(name, "r")) == NULL)
    {
		printf("File not found\n");
		//scanf("%*c");
		return;
    }
	while(fscanf(file, "%d", &key)!=EOF){
		fscanf(file, "%d %d ", &first, &second);
		string = fget_str(file);
		data = (Data*)malloc(sizeof(Data));
		data->first = first;
		data->second = second;
		data->string = string;
		data = insert(tree, key, data);
		if (data) {
			printf("Replaced information:\n");
			print_data(data);
			free(data->string);
			free(data);
		}
	}
	fclose(file);
	printf("Information has been loaded\n");
}

