#include <stdio.h>
#include <stdlib.h>

typedef enum color_t {
	RED = 1, BLACK = 0
} color_t;

typedef struct rb_node {
	struct rb_node* parent, *lson, *rson;
	color_t color;
	int key;
	int data;
} rb_node_t, *rb_node_p;

void rbtree_insert(rb_node_p node, rb_node_p root) {
	if (node->data > root->data) //first insert
		root->rson = node;
	else
		root->lson = node;

	if (root->color == RED) {

		if (root->parent->lson == root) { //left
			if (root->lson == node) {
				if (root->parent->rson->color == RED) {
					root->parent->color==RED;
					root->color==BLACK;
					root->parent->rson->color==BLACK;
					root=root->parent;
					continu;
				}
			} else { //right

			}
		}
	}
}
