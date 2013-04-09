#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *pre;
	struct node *next;
};
struct node_list {
	struct node *head;
	struct node *tail;
	int node_size;
};

struct node_list* init_node_list() {
	struct node_list * head_node = malloc(sizeof(struct node_list));
	if (head_node != NULL ) {
		head_node->head = NULL;
		head_node->tail = NULL;
		head_node->node_size = 0;
		return head_node;
	} else {
		return NULL ;
	}
}

void add_node_list(struct node_list *head, struct node* node) {
	if (node == NULL ) {
		return;
	}
	if (head->tail != NULL ) {
		head->tail->next = node;
		head->node_size += 1;
	} else {
		head->tail = node;
		head->node_size += 1;
	}
}

struct node* init_node(int data) {
	struct node * node = malloc(sizeof(struct node));
	if (node != NULL ) {
		node->data = data;
		return node;
	} else {
		return NULL ;
	}
}

void travle_node_list(struct node_list * list) {
	while (list->tail != NULL ) {
		printf("%d \n", list->tail->data);
		list->tail = list->tail->next;
	}
}
