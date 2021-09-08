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
  node_t * x = t->root;
  node_t * left_child;
  node_t * right_child;
  

  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *tmp = malloc(sizeof(node_t));
  tmp->key = key;
  tmp->left = NULL;
  tmp->right = NULL;
  tmp->parent = NULL;
  // root가 없는경우
  if (t->root == NULL) {
    tmp->color = RBTREE_BLACK;
    t->root = tmp;
    return t->root;
  }
  // root가 있는 경우
  else {
    node_t *prev = t->root;
    while(1) {
      if (prev->key > key) {
        if(prev->left != NULL) {
          prev = prev->left;
        }
        else {
          prev->left = tmp;
          tmp->parent = prev;
          tmp->color = RBTREE_RED;
          break;
        }
      }
      else {
        if(prev->right != NULL) {
          prev = prev->right;
        }
        else {
          prev->right = tmp;
          tmp->parent = prev;
          tmp->color = RBTREE_RED;
          break;
        }
      }
      }
    }
  while (tmp->parent !=NULL && tmp->parent->color == RBTREE_RED) {
    //new node의 부모노드가 왼쪽자식인 경우
    if (tmp->parent == tmp->parent->parent->left) {
      // 부모노드의 형제노드 정의
      node_t *uncle = tmp->parent->parent->right;
      // case1(uncle's color is RED)
      if (uncle!=NULL&&uncle->color == RBTREE_RED) {
        tmp->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        tmp->parent->parent->color = RBTREE_RED;
        tmp = tmp->parent->parent;
      }
      //case2 or case3(uncle's color is BLACK)
      else{
        //case2
        if (tmp->parent->right == tmp) {
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
      if(uncle!=NULL&&uncle->color == RBTREE_RED ) {
        tmp->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        tmp->parent->parent->color = RBTREE_RED;
        tmp = tmp->parent->parent;
      }
      //case5 or case6
      else { 
        //case5
        if(tmp == tmp->parent->left) {
          tmp = tmp->parent;
          right_rotate(t, tmp);
        }
        //case6
        tmp->parent->parent->color = RBTREE_RED;
        tmp->parent->color = RBTREE_BLACK;
        left_rotate(t, tmp->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *minimum(rbtree *t, node_t *x) {
  while(x->left != NULL) {
    x = x->left;
  }
  return x;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}


int rbtree_erase(rbtree *t, node_t *p) {
  if (t->root==NULL){return 0;} //트리가 없으면 종료.
  node_t* x=t->root;
  node_t* y;  //y는 부모노드 
  while(1){   //부모찾기 반복문
      if (x->key > p->key){
          if(x->left!=NULL){ 
              y=x;
              x = x->left;}
          else{return 0;}}
      else if (x->key < p->key){
          if(x->right!=NULL){
              y=x;
              x = x->right;}
          else{return 0;}}
      /* else는 같을 경우 */
      else {break;}
      }
  
  if (p->left==NULL){
      node_t* temp =p->right;
      if (y->key > p->key){
          y->left=temp;
          free(p);
      }
      else if (y->key < p->key){
          y->right=temp;
          free(p);
      }
  }
  else if (p->right==NULL){
      node_t* temp=p->left;
      if (y->key > p->key){
          y->left=temp;
          free(p);
      }
  
      else if (y->key < p->key){
          y->right=temp;
          free(p);
      }
  }
  else {
      node_t* temp= p->right;  // successor 대상 찾기 (키 값 기준 오른쪽에서 가장 작은 값.)
      node_t* p_d =NULL;       // successor의 부모노드.
      while(temp->left!=NULL){
      p_d=temp;
      temp=temp->left;}
      if (p_d!=NULL){  
          p_d->left = temp->right;
      }
      else{ //succesor의 부모노드가 삭제 대상인 p인 경우. (p 바로 오른쪽 노드가 successor이고 successor는 왼쪽자식이 없는 상황 )
          p->right=temp->right;
      }
      p->key=temp->key;
      free(temp);
  }
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}