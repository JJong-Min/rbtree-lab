# include<stdio.h>
# include<stdlib.h>

typedef struct NODE
{
    struct NODE *next;
    int data;
}node;

void addFirst(node *target, int data) 
{
    if (target == NULL)
        return;
    node *newnode = malloc(sizeof(node));
    if (newnode == NULL)
        return;
    newnode->next = target->next;
    target->next = newnode->next;
    newnode->data = data;
}

//기준 노드 다음 노드를 삭제
void removeFirst(node *target) {
    if (target == NULL)
        return;

    node *removenode = target->next;
    if (removenode == NULL)
        return;
    target->next = removenode->next;
    free(removenode);
}

// 특정 노드 검색
node *findNode(node *Node, int data)
{
    if (Node == NULL)
        return NULL;
    node *curr = Node->next;
    while(curr != NULL) {
        if (curr->data == data)
            return curr;
        curr = curr->next;
    }

    return NULL;
}

// 특정 노드 삭제
node *removeNode(node *Node, int data)
{
    if (Node == NULL)
        return NULL;
    node *curr = Node;
    node *prev = NULL;
    while(curr != NULL)
    {
        if (curr->data == data)
            prev->next = curr->next;
            free(curr);
        prev = curr;
        curr = curr->next;
    }

    return NULL;
}