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
typedef struct rb_tree {
	unsigned node_size;
	rb_node_p root;
	rb_node_p nil;
}*rb_tree_p;
/*-----------------------------------------------------------
 |   node           right
 |   / \    ==>     / \
|  a  right      node  y
 |      / \      / \
|       b  y    a   b
 -----------------------------------------------------------*/

static void rb_retate_left(rb_tree_p tree, rb_node_p parent) {
	rb_node_p right = parent->rson;
	rb_node_p a = parent->lson;
	rb_node_p b = right->lson;
	rb_node_p y = right->rson;

	if (parent->rson = b) {
		b->parent = parent;
	}
	right->lson = parent;
	if (right->parent = parent->parent) {

		if (parent->parent->lson == parent)  //think about left ;
			parent->parent->lson = right;
		else
			parent->parent->rson = right;
	} else {
		tree->root = right;
	}

	parent->parent = right;
}

/*-----------------------------------------------------------

 |       node           left

 |       / \            /
 |    left  y   ==>    a   node

 |   / \               /
 |  a   b             b   y

 -----------------------------------------------------------*/
static rb_node_p rb_rotate_right(rb_tree_p tree, rb_node_p root) {

}
void rbtree_insert(rb_tree_p tree, int data) {

	rb_node_p node_insert = malloc(sizeof(struct rb_node));
	node_insert->data = data;
	node_insert->color = RED;
	node_insert->parent = node_insert->rson = node_insert->lson = tree->nil;
	rb_node_p x = tree->root, y = tree->nil;
	while (x != tree->nil) {  //找到 插入 的父节点
		y = x;
		if (x->data > data)
			x = x->lson;
		else
			x = x->rson;
	}
	node_insert->parent = y;
	if (y == tree->nil) {
		tree->root = node_insert;
	} else if (y->data > data) {
		y->lson = node_insert;
	} else {
		y->rson = node_insert;
	}
	tree->node_size++;
	rbtree_insert_fixup(tree, node_insert);
}
void rbtree_insert_fixup(rb_tree_p tree, rb_node_p node) {
	rb_node_p temp;

	while (node->parent->color == RED) {
		rb_node_p parent = node->parent;
		if (parent->lson == parent) {  //左边情况
			rb_node_p uncle = parent->parent->rson;  //uncle parent
			if (uncle->color == RED) { //叔为红 直接修改父 和叔为黑色，祖父节点变红 在循环
				parent->color = BLACK;
				uncle->color = BLACK;
				parent->parent->color = RED;
				node = parent->parent;
				continue;
			} else { //叔 黑或者为空
				if (parent->rson == node) { //节点在右边  以父节点为中心左旋转 ，父节点和子节点互换
					rb_retate_left(tree, parent);
					rb_node_p temp = node;
					node = parent;
					parent = node;
				}
				//父 变黑 祖父节点 变红 然后右调整
				parent->color = BLACK;
				parent->parent->color = RED;
				rb_rotate_right(tree, parent->parent);
				return;
			}

		} else { //right
			rb_node_p uncle = parent->parent->rson;  //uncle parent
			if (uncle->color == RED) {
				parent->color = BLACK;
				uncle->color = BLACK;
				parent->parent->color = RED;
				node = parent->parent;
				continue;
			} else {
				if (parent->lson == node) {
					rb_rotate_right(tree, parent);
					rb_node_p temp = node;
					node = parent;
					parent = node;
				}
				parent->color = BLACK;
				parent->parent->color = RED;
				rb_rotate_left(tree, parent->parent);
				return;
			}
		}
	}
}
