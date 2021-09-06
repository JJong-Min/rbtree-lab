#include "rbtree.h"

#include <malloc.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(sizeof(rbtree), 1);
  return p;
}

void left_rotate(rbtree *t, node_t *x) {
  node_t *y = x->right;
  x->right = y->left;
  if (y->left != NULL) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  // x가 root인 경우
  if(x->parent == NULL) {
    t->root = y;
  }
  // x가 왼쪽자식인 경우
  else if(x == x->parent->left) {
    x->parent->left = y;
  }
  //x가 오른쪽자식인 경우
  else {
    x->parent->right = y;
  }
  // 마지막으로 y의 왼쪽자식과  x의 부모노드 업데이트
  y->left = x;
  x->parent = y;
}

void right_rotate(rbtree *t, node_t *x) {
  node_t *y = x->left;
  x->left = y->right;
  if (y->right != NULL) {
    y->right->parent = x;
  }
  y->parent = x->parent;
  // x가 root인 경우
  if(x->parent == NULL) {
    t->root = y;
  }
  // x가 왼쪽자식인 경우
  else if(x == x->parent->left) {
    x->parent->left = y;
  }
  //x가 오른쪽자식인 경우
  else {
    x->parent->right = y;
  }
  // 마지막으로 y의 왼쪽자식과  x의 부모노드 업데이트
  y->right = x;
  x->parent = y;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *tmp = malloc(sizeof(node_t));
  tmp->key = key;
  tmp->left = NULL;
  tmp->right = NULL;
  tmp->parent = NULL;
  // root가 없는경우
  if (t == NULL) {
    tmp->color = RBTREE_BLACK;
    t->root = tmp;
  }
  // root가 있는 경우
  else {
    node_t *prev = t->root;
    while(prev != NULL) {
      if (key < prev->key) {
        prev = prev->left;
      }
      else {
        prev = prev->right;
      }
    }

    tmp->parent = prev;
    tmp->color = RBTREE_RED;
  }

  while (tmp->parent->color == RBTREE_RED) {
    //new node의 부모노드가 왼쪽자식인 경우
    if (tmp->parent == tmp->parent->parent->left) {
      // 부모노드의 형제노드 정의
      node_t *uncle = tmp->parent->parent->right;
      // case1(uncle's color is RED)
      if (uncle->color == RBTREE_RED) {
        tmp->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        tmp->parent->parent->color = RBTREE_RED;
        tmp = tmp->parent->parent;
      }
      //case2 or case3(uncle's color is BLACK)
      else{
        //case2
        if (tmp->parent->right = tmp) {
          tmp = tmp->parent;
          left_rotate(t, tmp);
        }
        //case3
        tmp->parent->parent->color = RBTREE_RED;
        tmp->parent->color = RBTREE_BLACK;
        right_rotate(t, tmp->parent->parent);
      }
    }
    // new node의 부모노드가 오른쪽자식인 경우
    else {
      // 부모노드의 형제노드(uncle) 정의
      node_t *uncle = tmp->parent->parent->left;
      //case4(uncle's color is RED)
      if(uncle->color == RBTREE_RED) {
        tmp->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        tmp->parent->parent->color = RBTREE_RED;
        tmp = tmp->parent->parent;
      }
      //case5 or case6
      else { 
        //case5
        if(tmp = tmp->parent->left) {
          tmp = tmp->parent;
          left_rotate(t, tmp);
        }
        //case6
        tmp->parent->parent->color = RBTREE_RED;
        tmp->parent->color = RBTREE_BLACK;
        right_rotate(t, tmp->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
  return t->root;
}