#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "b_tree.h"


void print_menu(void){
	printf("~~~MENU~~~\n");
	printf("0) Read from file for debug\n");
	printf("1) Include one new element\n");
	printf("2) Include several new elements\n");
	printf("3) Delete one item\n");
	printf("4) Delete several items\n");
	printf("5) Search for information by a key\n");
	printf("6) Search for the element corresponding to the value");
	printf(" of the smallest key that exceeds the specified value\n");
	printf("7) Print tree\n");
	printf("8) Print beauty tree\n");
	printf("9) Delete all tree\n");
	printf("10) Exit\n");
	printf("~~~~~~~~~~\n");
}


void include_elements(Tree* tree, int count){
	Data *data;
	key_type key;
	for (int i=0; i<count; i++){
		data = create_data();
		key = input_key();
		data = insert(tree, key, data);
		if (data) {
			printf("Replaced information:\n");
			print_data(data);
			free(data->string);
			free(data);
		}
	}
}


void delete_elements(Tree *tree, int count){
	key_type key;
	for (int i=0; i<count; i++){
		printf("Enter a key\n");
		get_int(&key);
		remove_element(tree, key);
	}
}


void UI(void){
	Tree *tree = create_tree();
	int choice;
	do{
		print_menu();
		do{
			printf("Select one of the following options\n");
			get_int(&choice);
		} while (choice<0 || choice>10);
		switch (choice){
			case 0:
			{
				input_from_file(tree);
				break;
			}
			case 2:
			{
				int count;
				do{
					printf("Enter the number of items\n");
					get_int(&count);
				} while (count<1);
				include_elements(tree, count);
				printf("Done!\n");
				break;
			}
			case 1:
			{
				include_elements(tree, 1);
				printf("Done!\n");
				break;
			}
			case 4:
			{
				int count;
				do{
					printf("Enter the number of items\n");
					get_int(&count);
				} while (count<1);
				delete_elements(tree, count);
				printf("Done!\n");
				break;
			}
			case 3:
			{
				delete_elements(tree, 1);
				printf("Done!\n");
				break;
			}
			case 5:
			{
				key_type key;
				Data *data;
				printf("Enter a key\n");
				get_int(&key);
				data = get_data_by_key(tree, key);
				if (data) print_data(data);
				break;
			}
			case 6:
			{
				key_type pending, key;
				Tree_element *element;
				Data *data;
				printf("Enter a number\n");
				get_int(&pending);
				element = get_smallest_among_bigger_ptr(tree, pending);
				if (element) key = element->key;
				data = get_smallest_among_bigger(tree, pending);
				if (data) {
					printf("Key -> %d\n", key);
					print_data(data);
				} else{
					printf("Element now found\n");
				}
				break;
			}
			case 7:
			{
				print_tree(tree);
				break;
			}
			case 9:
			{
				del_tree(tree);
				break;
			}
			case 10:
			{
				del_tree(tree);
				free(tree);
				break;
			}
			case 8:
			{
				print_beauty_tree(tree);
			}
		}
	} while (choice!=10);
}


int main(void){
	printf("Hello, World!\n");
	UI();
	printf("\nBye!\n");
	return 0;
}
