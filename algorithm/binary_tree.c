#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node * lson, *rson, *parent;
};
typedef struct node* node_p;

node_p tree_node_search(node_p root, int data) {

	while (root != NULL ) {

		if (root->data > data) {
			root = root->lson;
		} else if (root->data < data) {
			root = root->rson;
		} else {
			return root;
		}
	}
	return NULL ;

}

void tree_insert(node_p root, int data) {
	node_p temp = NULL;
	node_p x = root;
	node_p node = malloc(sizeof(struct node));
	if (node == NULL ) {
		return;
	} else {
		node->data = data;
		node->lson = NULL;
		node->rson = NULL;
		node->parent = NULL;
	}
	while (x != NULL ) {
		temp = x;
		if (x->data > data) {
			x = x->lson;
		} else if (x->data < data) {
			x = x->rson;
		}
	}
	node->parent = temp;

}

void tree_node_delete(node_p root, int data) {
	node_p node = tree_node_search(root, data);
	if (node != NULL ) {

		if (!node->rson) {  //无右儿子
			node->parent->lson = node->lson;
			node->lson->parent=node->parent;
			free(node);
		} else if (!node->lson) { //无左二子
			node->parent->rson = node->rson;
			node->rson->parent=node->parent;
			free(node);
		} else { //有兩個兒子
//        先找前继
			node_p s = node->lson;
			node_p s_parent;
			while (s->rson) {
				s = s->rson;
			}
			node->data = s->data;

		}
	} else {

		return;
	}
}

