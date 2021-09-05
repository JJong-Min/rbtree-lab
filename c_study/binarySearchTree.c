# include<stdio.h>
# include<stdlib.h>

typedef struct NODE
{
    int data;
    struct NODE *leftchild;
    struct NODE *rightchild;
} node;

// create new BST tree
node *newBST(int data)
{
    node *tmp = malloc(sizeof(node));
    tmp->data = data;
    tmp->leftchild = tmp->rightchild = NULL;
    return tmp;
}

// traversal of BST(시간복잡도:O(n))
void inorder(node *root)
{
    if (root != NULL)
    {
        inorder(root->leftchild);
        printf("%d\n", root->data);
        inorder(root->rightchild);
    }
}

// search node
node *search(node *root, int data)
{
    if (root==NULL || root->data == data)
        return root;
    
    else if (root-> data > data)
        return search(root->leftchild, data);

    else
        return search(root->rightchild, data);
}

// insert new node to BST tree
node *insert(node *root, int data)
{
    if (root == NULL)
        return newBST(data);

    else
    {
        if(root->data > data)
            root->leftchild = insert(root->leftchild, data);
        else
            root->rightchild = insert(root->rightchild, data);
    }
    return root;
}

// find minVal in BST
node *minValueNode(node *Node)
{
    node *current = Node;
    while(current && current->leftchild != NULL)
        current = current->leftchild;
    
    return current;
}

// find maxVal in BST
node *maxValueNode(node *Node)
{
    node *current = Node;
    while(current && current->rightchild != NULL)
        current = current->rightchild;
    
    return current;
}

// delete node in BST
node *deleteNode(node *root, int data)
{
    if (root==NULL)
        return root;
    
    if (data < root->data)
        root->leftchild = deleteNode(root->leftchild, data);

    else if (data > root->data)
        root->rightchild = deleteNode(root->rightchild, data);

    else {
        // node with only one child or no child
        if (root->leftchild == NULL) {
            node *temp = root->rightchild;
            free(root);
            return temp;
        }

        else if (root->rightchild == NULL) {
            node *temp = root->leftchild;
            free(root);
            return temp;
        }

        // node with two childs
        node *temp = minValueNode(root->rightchild);
        root->data = temp->data;
        root->rightchild = deleteNode(root->rightchild, temp->data);
    }
    return root;
}

// Driver Code
int main()
{
    /* Let us create following BST
              50
           /     \
          30      70
         /  \    /  \
       20   40  60   80 */
    node *root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);
 
    printf("Inorder traversal of the given tree \n");
    inorder(root);
 
    printf("\nDelete 20\n");
    root = deleteNode(root, 20);
    printf("Inorder traversal of the modified tree \n");
    inorder(root);
 
    printf("\nDelete 30\n");
    root = deleteNode(root, 30);
    printf("Inorder traversal of the modified tree \n");
    inorder(root);
 
    printf("\nDelete 50\n");
    root = deleteNode(root, 50);
    printf("Inorder traversal of the modified tree \n");
    inorder(root);
 
    return 0;
}