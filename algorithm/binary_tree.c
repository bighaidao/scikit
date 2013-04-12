#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node * lson, *rson, *parent;
};
typedef struct node* node_p;

//tarverse

void preorder_traverse(node_p tree) {
	if (tree != NULL ) {
		printf("%d \n", tree->data);
		preorder_traverse(tree->lson);
		preorder_traverse(tree->rson);
	}

}

void midorder_traverse(node_p tree) {
	if (tree != NULL ) {
		preorder_traverse(tree->lson);
		printf("%d \n", tree->data);
		preorder_traverse(tree->rson);

	}
}

void postorder_traverse(node_p tree) {
	if (tree != NULL ) {
		preorder_traverse(tree->lson);
		preorder_traverse(tree->rson);
		printf("%d \n", tree->data);
	}
}
//depth
int tree_depth(node_p tree) {
	if (!tree) {
		return 0;
	}
	int nleft  = tree_depth(tree->lson);
	int nright = tree_depth(tree->rson);
	return (nleft > nright) ? (nleft + 1) : (nright + 1);
}

void hang_traverse(node_p tree) {

}

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
	if (root == NULL ) {
		root = node;
		return;
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
	if (temp->data >= data) {
		temp->lson = node;
	} else {
		temp->rson = node;
	}

}

void tree_node_delete(node_p root, int data) {
	node_p node = tree_node_search(root, data);
	if (node != NULL ) {

		if (!node->rson) {  //无右儿子
			node->parent->lson = node->lson;
			node->lson->parent = node->parent;
			free(node);
		} else if (!node->lson) { //无左二子
			node->parent->rson = node->rson;
			node->rson->parent = node->parent;
			free(node);
		} else { //有兩個兒子
//        先找前继

			node_p s = node->lson;

			node_p s_parent = node;
			while (s->rson) {
				s_parent = s;
				s = s->rson;
			}
			node->data = s->data;
			if (s_parent != node) //test s->rson is null or not
				s_parent->rson = s->lson;
			else
				s_parent->lson = s->lson;
			free(s);

		}
	} else {

		return;
	}
}

//int main() {
//	node_p tree = malloc(sizeof(struct node));
//	tree->data = 12;
//	tree->parent = tree->lson = tree->rson = NULL;
//	//构造文章开头图中的二叉树
//	tree_insert(tree, 15);
//	tree_insert(tree, 6);
//	tree_insert(tree, 18);
//	tree_insert(tree, 3);
//	tree_insert(tree, 7);
//	tree_insert(tree, 17);
//	tree_insert(tree, 20);
//	tree_insert(tree, 2);
//	tree_insert(tree, 4);
//	tree_insert(tree, 13);
//	tree_insert(tree, 9);
//	if (tree == NULL ) {
//		printf("null");
//	}
//	preorder_traverse(tree);
//	tree_node_delete(tree,15);
//	preorder_traverse(tree);
//	return 0;
//}

