#include "RBT.h"

void rb_init(RBNODE **t)
{
	*t = NULL;
}

RBNODE *rb_create_node(int val, char color)
{
	RBNODE *n = (RBNODE *)malloc(sizeof(RBNODE));
	n->data   = val;
	n->parent = NULL;
	n->left   = NULL;
	n->right  = NULL;
	n->color  = color;

	return n;
}

void rb_preorder(RBNODE *root)
{
	if (NULL != root) {
		printf("%c(%d) ", root->color? 'R': 'B', root->data);
		rb_preorder(root->left);
		rb_preorder(root->right);
	}
}

void rb_inorder(RBNODE *root)
{
	if (NULL != root) {
		rb_inorder(root->left);
		printf("%c(%d) ", root->color? 'R': 'B', root->data);
		rb_inorder(root->right);
	}
}

void rb_postorder(RBNODE *root)
{
	if (NULL != root) {
		rb_postorder(root->left);
		rb_postorder(root->right);
		printf("%c(%d) ", root->color? 'R': 'B', root->data);
	}
}

void rb_BFS(RBNODE *root)
{
	RBNODE *c;
	queue <RBNODE *> Q;

	Q.push(root);
	while (!Q.empty()) {
		c = Q.front(), Q.pop();

		if (c->parent)
			printf("[%d]", c->parent->data);
		printf("(%d)%c ", c->data, c->color? 'R': 'B');

		if (NULL != c->left)
			Q.push(c->left);

		if (NULL != c->right)
			Q.push(c->right);
	}
}

void traversals(RBNODE *root)
{
	printf("InOrder\n\t");
	rb_inorder(root), printf("\n\n");

	/*printf("PreOrder\n\t");
	rb_preorder(root), printf("\n\n");
	
	printf("PostOrder\n\t");
	rb_postorder(root), printf("\n\n");*/

	printf("BFS\n\t");
	rb_BFS(root), printf("\n");
}

RBNODE *rbh_gparent(RBNODE *n)
{
	if (NULL != n && NULL != n->parent)
		return n->parent->parent;
	else
		return NULL;
}

RBNODE *rbh_uncle(RBNODE *n)
{
	RBNODE *g = rbh_gparent(n);

	if (NULL == g)
		return g; 
	if (n->parent == g->left)
		return g->right;
	else
		return g->left;
}

void rbh_rotate_right(RBNODE **root, RBNODE *n) 
{
	RBNODE *tmp_g = rbh_gparent(n);
	RBNODE *tmp_p = n->parent;
	RBNODE *tmp_r = n->right;
	printf("  ROTATE R\n");

	n->parent = tmp_g;
	if (NULL != tmp_g) {
		if (tmp_g->left == tmp_p)
			tmp_g->left  = n;
		else
			tmp_g->right = n;
	} else {
		*root = n;
	}
	
	tmp_p->left   = tmp_r;
	if (NULL != tmp_r)
		tmp_r->parent = tmp_p;

	n->right      = tmp_p;
	tmp_p->parent = n;
}

void rbh_rotate_left(RBNODE **root, RBNODE *n)
{
	RBNODE *tmp_g = rbh_gparent(n);
	RBNODE *tmp_p = n->parent;
	RBNODE *tmp_l = n->left;
	printf("  ROTATE L\n");

	n->parent = tmp_g;
	if (NULL != tmp_g) {
		if (tmp_g->left == tmp_p)
			tmp_g->left  = n;
		else
			tmp_g->right = n;
	} else {
		*root = n;
	}
	
	tmp_p->right  = tmp_l;
	if (NULL != tmp_l)
		tmp_l->parent = tmp_p;

	n->left       = tmp_p;
	tmp_p->parent = n;
}

RBNODE *rbh_insert(RBNODE *root, RBNODE *parent, RBNODE *n)
{
	if (NULL == root) {
		n->parent = parent;
		return n;
	} else {
		if (n->data < root->data)
			root->left  = rbh_insert(root->left,  root, n);
		else
			root->right = rbh_insert(root->right, root, n);
	}
	return root;
}

void rbh_insert_case5(RBNODE **root, RBNODE *n)
{
	RBNODE *g = rbh_gparent(n);
	printf(" CASE 5\n");

	n->parent->color = BLACK;
	g->color         = RED;

	if (n == n->parent->left)
		rbh_rotate_right(&(*root), g->left);
	else
		rbh_rotate_left(&(*root), g->right);
}

void rbh_insert_case4(RBNODE **root, RBNODE *n)
{
	RBNODE *g = rbh_gparent(n);
	printf(" CASE 4\n");

	if (n == n->parent->right && n->parent == g->left) {
		rbh_rotate_left(&(*root), n->parent->right);
		n = n->left;
	} else if (n == n->parent->left && n->parent == g->right) {
		rbh_rotate_right(&(*root), n->parent->left);
		n = n->right; 
	}
	rbh_insert_case5(&(*root), n);
}

void rbh_insert_case3(RBNODE **root, RBNODE *n)
{
	RBNODE *g = NULL;
	RBNODE *u = rbh_uncle(n);
	printf(" CASE 3\n");

	if (NULL != u && RED == u->color) {
		n->parent->color = BLACK;
		u->color         = BLACK;
		g                = rbh_gparent(n);
		g->color         = RED;

		rbh_insert_case1(&(*root), g);
	} else {
		rbh_insert_case4(&(*root), n);
	}
}

void rbh_insert_case2(RBNODE **root, RBNODE *n)
{
	printf(" CASE 2\n");
	if (n->parent->color == BLACK)
		return; 
	else
		rbh_insert_case3(&(*root), n);
}

void rbh_insert_case1(RBNODE **root, RBNODE *n)
{
	printf(" CASE 1\n");
	if (NULL == n->parent)
		n->color = BLACK;
	else
		rbh_insert_case2(&(*root), n);
}

void rb_insert(RBNODE **root, int val)
{
	RBNODE *n = rb_create_node(val, RED);
	printf("+Insert %d\n", val);
	*root = rbh_insert(*root, NULL, n);
	rbh_insert_case1(&(*root), n);
	printf("-Insert\n\n");
}


RBNODE *rbh_sibling(RBNODE *n)
{
	if (NULL == n || NULL == n->parent)
		return NULL;
	if (n == n->parent->left)
		return n->parent->right;
	else
		return n->parent->left;
}

void rb_delete(RBNODE **root, int val)
{

}

RBNODE *rb_find(RBNODE *t, int val)
{
	return NULL;
}

int main(int argc, char *argv[])
{
	int i;
	RBNODE *t;
	
	rb_init(&t);
	
	while (1) {
		printf("Insert? ");
		scanf("%d", &i);
	
		rb_insert(&t, i);
		traversals(t);
	}
	return 0;
}
