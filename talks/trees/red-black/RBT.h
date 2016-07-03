#ifndef _RBTREE_H_
#define _RBTREE_H_

#include <cstdio>
#include <cstdlib>
#include <queue>

using namespace std;

enum Color {BLACK, RED};

typedef struct rbnode {
	int  data;
	char color;
	struct rbnode *parent;
	struct rbnode *right;
	struct rbnode *left;
} RBNODE;

void    rb_init(RBNODE **);
RBNODE *rb_create_node(int, char);

void    rb_preorder(RBNODE *);
void    rb_inorder(RBNODE *);
void    rb_postorder(RBNODE *);
void    rb_BFS(RBNODE *);
void    traversals(RBNODE *);

RBNODE *rbh_gparent(RBNODE *);
RBNODE *rbh_uncle(RBNODE *);
void    rbh_rotate_right(RBNODE **, RBNODE *);
void    rbh_rotate_left(RBNODE **, RBNODE *);

void    rbh_insert_case1(RBNODE **, RBNODE *);
void    rbh_insert_case2(RBNODE **, RBNODE *);
void    rbh_insert_case3(RBNODE **, RBNODE *);
void    rbh_insert_case4(RBNODE **, RBNODE *);
void    rbh_insert_case5(RBNODE **, RBNODE *);

RBNODE *rbh_insert(RBNODE *, RBNODE *, RBNODE *);
void    rb_insert(RBNODE **, int);

RBNODE *rbh_sibling(RBNODE *);
void    rb_delete(RBNODE **, int);

RBNODE *rb_find(RBNODE *, int );

#endif