#include "rbtree.h"
#include <stdio.h>
#include <malloc.h>

void delete_case1(rbtree *t, node_t *n);
void delete_case2(rbtree *t, node_t *n);
void delete_case3(rbtree *t, node_t *n);
void delete_case4(rbtree *t, node_t *n);
void delete_case5(rbtree *t, node_t *n);
void delete_case6(rbtree *t, node_t *n);
void delete_one_child(rbtree *t, node_t *n);

// tree 첫 생성
rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(sizeof(rbtree), 1);
  return p;
}

void rotate_left(rbtree *t, node_t *x) {
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

void rotate_right(rbtree *t, node_t *x) {
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

// 조부모 노드 반환
node_t *grandparent(node_t *n) {
  if ((n != NULL) && (n->parent != NULL)) {
    return n->parent->parent;
  }
  else {
    return NULL;
  }
}

// 삼촌 노드 반환
node_t *uncle(node_t *n) {
  node_t *grand_parent_node = grandparent(n);
  if (grand_parent_node == NULL) {
    return NULL;
  }
  else {
    if (grand_parent_node->left == n->parent) {
      return grand_parent_node->right;
    }
    else {
      return grand_parent_node->left;
    }
  }
}

// 형제 노드 반환
node_t *sibling(node_t *n) {
  if (n->parent == NULL) {
    return NULL;
  }
  else {
    if (n->parent->left == n) {
      return n->parent->right;
    }
    else{
      return n->parent->left;
    }
  }
}

// tree 전체 노드를 free
void delete_rbtree(rbtree *t) {
  // TODO: implement delete_rbtree
  free(t);
}

// key값을 가지고 tree에 insert
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
          rotate_left(t, tmp);
        }
        //case3
        tmp->parent->parent->color = RBTREE_RED;
        tmp->parent->color = RBTREE_BLACK;
        rotate_right(t, tmp->parent->parent);
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
          rotate_right(t, tmp);
        }
        //case6
        tmp->parent->parent->color = RBTREE_RED;
        tmp->parent->color = RBTREE_BLACK;
        rotate_left(t, tmp->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
  return t->root;
}


// 특정 key가 tree에 있으면 해당 노드 봔한
node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t *tmp = t->root;
  if (tmp != NULL) {
    while(tmp != NULL && tmp->key != key) {
      if (tmp->key > key) {
        tmp = tmp->left;
      }
      else {
        tmp = tmp->right;
      }
    }
  }
  return tmp;
}

// tree의 min key를 가지는 노드 반환
node_t *rbtree_min(const rbtree *t) {
  node_t *tmp = t->root;
  if (tmp != NULL) {
    while(tmp->left != NULL) {
      tmp = tmp->left;
    }
  }
  return tmp;
}

// tree의 max key를 가지는 노드 반환
node_t *rbtree_max(const rbtree *t) {
  node_t *tmp = t->root;
  if (tmp != NULL) {
    while(tmp->right != NULL) {
      tmp = tmp->right;
    }
  }
  return tmp;
}

// 특정 노드 지우기
int rbtree_erase(rbtree *t, node_t *p) {
  // p가 tree에 존재하지 않거나 tree 자체가 없는 바로 종료
  if (t->root == NULL || p == NULL) {
    return 0;
  }
  //삭제하고자 하는 node의 자식이 2명인 경우
  if (p->left != NULL && p->right != NULL) {
    //  preceder 찾기
    node_t *tmp = p->left;
    node_t *parent = NULL;
    while(tmp->right != NULL) {
      parent = tmp;
      tmp = tmp->right;
    }

    //preceder의 상태에 따라 경우 나눔
    if(parent != NULL) {
      // precedor의 왼쪽 자식이 nuil인 겨우는 precedor를 유령노드(nil노드)인 것처럼 쓸것이므로 예외처리
      if(tmp->left != NULL) {
        parent->right = tmp->left;
      }
    }
    // preceder가 삭제노드(p)의 자식인 경우
    else {
      // preceder의 왼쪽 자식이 nuil인 겨우는 precedor를 유령노드(nil노드)인 것처럼 쓸것이므로 예외처리
      if (tmp->left != NULL) {
        p->left = tmp->left;
      }
      p->key = tmp->key;
      delete_one_child(t, tmp);
    }
  }
  //자식이 1개이거나 0개인경우
  else {
    delete_one_child(t, p);
  }
  return 0;
}


int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  return 0;
}

// 전위순회로 tree node 출력
void inorder(node_t *p) {
  if(p != NULL) {
    inorder(p->left);
    printf("key: %d, color: %d \n", p->key, p->color);
    inorder(p->right);
  }
}

// 특정 key값을 받으면 해당 노드의 정보 출력
void node_info(rbtree *t, const key_t key) {
  node_t *tmp = rbtree_find(t, key);
  printf("key: %d, color: %d, add: %p", tmp->key, tmp->color, tmp);
}

void replace_node(node_t *n, node_t *c) {
  c->parent = n->parent;
  if (n->parent->left == n) {
    n->parent->left = c;
  }
  else if (n->parent->right == n) {
    n->parent->right = c;
  }
}

// 삭제 노드가 자식이 없거나 1개인 경우에 처리를 어떻게 할지에 대한 함수
void delete_one_child(rbtree *t, node_t *n) {
  // root삭제 시 바로 free
  if(t->root == n) {
    t->root = NULL;
    free(n);
    return;
  }
  // root가 아닐 시
  // 삭제하고자 하는 node가 자식이 없고 black이면 case1 진입
  if (n->left == NULL && n->right == NULL) {
    if (n->color == RBTREE_BLACK) {
      delete_case1(t, n);
    }
  
    // 삭제하고자 하는 node가 자식이 없고 red이면 null로 치환하고 free
    if (n == n->parent->left) {
      n->parent->left = NULL;
    }
    else if (n == n->parent->right) {
      n->parent->right = NULL;
    }
    free(n);
    return;
  }
  // 자식이 하나라도 있는 경우
  node_t *child;
  // 오른쪽 자식만 있는 경우
  if (n->left == NULL) {
    child = n->right;
  }
  // 왼쪽 자식만 있는 경우
  else {
    child = n->left;
  }
  // 삭제하고자하는 node와 자식node 위치 변환
  replace_node(n, child);
  // 삭제하고자하는 node가 black인 경우만 생각하면 됨.
  // 삭제node는 black이고 자식이 red이면 자식을 black으로 치환해주고 삭제 node free
  if(n->color == RBTREE_BLACK && child->color == RBTREE_RED) {
    child->color = RBTREE_BLACK;
  }
  free(n);
}

void delete_case1(rbtree *t, node_t *n) {
  if(n->parent != NULL) {
    delete_case2(t, n);
  }
}

void delete_case2(rbtree *t, node_t *n) {
  // 형제노드를 루트로 하는 서브트리의 상황에 따라 달라짐
  node_t *s = sibling(n);
  if(s->color == RBTREE_RED) {
    n->parent->color = RBTREE_RED;
    s->color = RBTREE_BLACK;
    if (n == n->parent->left) {
      rotate_left(t, n->parent);
    }
    else {
      rotate_right(t, n->parent);
    }
    delete_case3(t, n);
  }
}

void delete_case3(rbtree *t, node_t *n) {
  node_t *s = sibling(n);
  if ((n->parent->color == RBTREE_BLACK) &&
      (s->color == RBTREE_BLACK) &&
      (s->left == NULL || s->left->color == RBTREE_BLACK) &&
      (s->right == NULL || s->right->color == RBTREE_BLACK)) {
        
        s->color = RBTREE_RED;
        delete_case1(t, n->parent);
  } else {
    delete_case4(t, n);
  }
}

void delete_case4(rbtree *t, node_t *n) {
  node_t *s = sibling(n);
  if ((n->parent->color == RBTREE_RED) &&
      (s->color == RBTREE_BLACK) &&
      (s->left == NULL || s->left->color == RBTREE_BLACK) &&
      (s->right == NULL || s->right->color == RBTREE_BLACK)) {
        s->color = RBTREE_RED;
        n->parent->color = RBTREE_BLACK;
      }
  else {
    delete_case5(t, n);
  }
}

void delete_case5(rbtree *t, node_t *n) {
  node_t *s = sibling(n);

  if (s->color == RBTREE_BLACK) {
    if((n == n->parent->left) &&
       (s->right == NULL || s->right->color == RBTREE_BLACK) &&
       (s->left != NULL && s->left->color == RBTREE_RED)) {
         s->color = RBTREE_RED;
         s->left->color = RBTREE_BLACK;
         rotate_right(t, s);
       }
    else if ((n == n->parent->right) &&
              (s->left == NULL || s->left->color == RBTREE_BLACK) &&
              (s->right != NULL || s->right->color == RBTREE_RED)) {
                s->color = RBTREE_RED;
                s->right->color = RBTREE_BLACK;
                rotate_left(t, s);
              }
  }
  delete_case6(t, n);
}

void delete_case6(rbtree *t, node_t *n) {
  node_t *s = sibling(n);
  s->color = n->parent->color;
  n->parent->color = RBTREE_BLACK;

  if (n == n->parent->left) {
    if(s->right != NULL) {
      s->right->color = RBTREE_BLACK;
    }
    rotate_left(t, n->parent);
    }
  else {
    if(s->left != NULL) {
      s->left->color = RBTREE_BLACK;
    }
    rotate_right(t, n->parent);
  }
}