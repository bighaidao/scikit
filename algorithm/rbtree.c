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

static void rb_rotate_left(rb_tree_p tree, rb_node_p parent) {
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

 |       / \            /  \
 |    left  y   ==>    a   node

 |   / \                   /  \
 |  a   b                  b   y

 -----------------------------------------------------------*/
static rb_node_p rb_rotate_right(rb_tree_p tree, rb_node_p parent) {

	rb_node_p left = parent->lson;
	rb_node_p a = left->lson;
	rb_node_p b = left->rson;
	rb_node_p y = parent->rson;

	if (parent->lson = b) {
		b->parent = parent;
	}
	left->rson = parent;
	if (left->parent = parent->parent) {

		if (parent->parent->lson == parent)  //think about left ;
			parent->parent->lson = left;
		else
			parent->parent->rson = left;
	} else {
		tree->root = left;
	}

	parent->parent = left;

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
					rb_rotate_left(tree, parent);
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

rb_node_p rbtree_delete_fixup(rb_tree_p tree, rb_node_p x) {

	while ((x != tree->root) && (x->color == BLACK)) {
		rb_node_p brother;
		rb_node_p parent;
		parent = x->parent;
		if (x->parent->lson == x) { //左边情况
			brother = x->parent->rson;
			//case 1
			if (brother->color == RED) {
				brother->color = BLACK;
				parent->color = RED;
				rb_rotate_left(tree, parent);
				brother = parent->rson;
			}
			//case 2
			if (brother->lson->color == BLACK
					&& brother->rson->color == BLACK) { //往上传颜色
				brother->color = RED;
				x = x->parent;  //往上
			} else {
				//case 3
				if (brother->rson->color == BLACK) { //it measn brother->lson->color==red
					brother->lson->color = BLACK;
					brother->color = RED;
					rb_rotate_right(tree, brother);
					brother = parent->rson;
				}
				//case 4  第四种情况是情况3的延续 所以直接接着写     第四种为标准模式
				/**
				 *因为 x的右子树已经是平衡的了，所以，只要让x的左子树也平衡就行了
				 *旋转之后，因为 x的右边 到w 黑高度为1 所以要将w的右儿子变为黑的
				 *而x的左边因为x是双重黑 ，降到这边的x的父节点必须变为黑 这样就达到了 左右黑高度平衡
				 */
				brother->color = parent->color; //直接继承parent的color
				parent->color = BLACK;
				if (brother->rson != tree->nil)
					brother->rson->color = BLACK;
				rb_rotate_left(tree, x->parent);
				x = tree->root;

			}
		} else {

			brother = x->parent->lson;
			//1
			if (brother->color == RED) {
				brother->color = BLACK;
				parent->color = RED;
				rb_rotate_right(tree, parent);
				brother = parent->lson;
			}
			//2
			if (brother->lson->color == BLACK
					&& brother->rson->color == BLACK) { //往上传颜色
				brother->color = RED;
				x = x->parent;  //往上
			} else {
				//3
				if (brother->lson->color == BLACK) { //it measn brother->lson->color==red
					brother->rson->color = BLACK;
					brother->color = RED;
					rb_rotate_left(tree, brother);
					brother = parent->lson;
				}
				//4  第四种情况是情况3的延续 所以直接接着写     第四种为标准模式
				/**
				 *因为 x的右子树已经是平衡的了，所以，只要让x的左子树也平衡就行了
				 *旋转之后，因为 x的右边 到w 黑高度为1 所以要将w的右儿子变为黑的
				 *而x的左边因为x是双重黑 ，降到这边的x的父节点必须变为黑 这样就达到了 左右黑高度平衡
				 */
				brother->color = parent->color; //直接继承parent的color
				parent->color = BLACK;
				if (brother->lson != tree->nil)
					brother->lson->color = BLACK;
				rb_rotate_right(tree, x->parent);
				x = tree->root;

			}
		}
	}

}
//后继  中序遍历
rb_node_p tree_successor(rb_node_p node) {
	rb_node_p temp = node;
	if (node->rson) {
		while (temp->lson)
			temp = temp->lson;
		return node;
	}
	rb_node_p y = node->parent;
	while (y != NULL && node == y->rson) {
		node = y;
		y = y->parent;
	}
	return y;
}

rb_node_p rbtree_delete(rb_tree_p tree, rb_node_p target) {

	rb_node_p x, y;  //y指向真正删除的节点  x指向要调整的节点
	if (target->lson == tree->nil || target->rson == tree->nil)
		y = target;
	else
		y = tree_successor(target);

	if (y->lson == tree->nil) //找到x
		x = y->rson;
	else
		x = y->lson;
	x->parent = y->parent;
	if (y->parent == tree->nil)
		tree->root = x;
	else if (y->parent->lson == y)
		y->parent->lson = x;
	else
		y->parent->rson = x;
	if (target != y)
		target->data = y->data;
	if (y->color == BLACK && x != tree->nil) {
		rbtree_insert_fixup(tree, x);
	}
	return y;
}

void test_midorder_traverse(rb_node_p root,rb_node_p nil) {

	if (root != nil ) {
		test_midorder_traverse(root->lson,nil);
		printf("%d \t", root->data);
		test_midorder_traverse(root->rson,nil);

	}
}

void test_preorder_traverse(rb_node_p root,rb_node_p nil) {

	if (root != nil ) {
		printf("%d \t", root->data);
		test_preorder_traverse(root->lson,nil);

		test_preorder_traverse(root->rson,nil);

	}
}
int main(int argc, char **argv) {

	rb_tree_p tree = malloc(sizeof(struct rb_tree));
	tree->node_size = 0;
	rb_node_p node = malloc(sizeof(struct rb_node));
	rb_node_p nil = malloc(sizeof(struct rb_node));
	node->parent = node->lson = node->rson = nil;
	node->data=20;
	tree->root = node;
	tree->nil = nil;
	rbtree_insert(tree,10);
	rbtree_insert(tree,3);
	rbtree_insert(tree,12);
	rbtree_insert(tree,42);
	rbtree_insert(tree,5);
	rbtree_insert(tree,6);
	rbtree_insert(tree,7);
	rbtree_insert(tree,8);
	rbtree_insert(tree,9);
	test_midorder_traverse(tree->root,tree->nil);
	printf("%d \n");
	test_preorder_traverse(tree->root,tree->nil);

}

