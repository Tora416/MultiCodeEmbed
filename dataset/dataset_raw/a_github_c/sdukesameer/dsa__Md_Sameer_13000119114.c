#include<stdio.h> 
#include<stdlib.h> 
typedef struct n{
    int key;
    struct n *left, *right;
}list;
typedef struct{
    int top;
    unsigned int size;
    int* arr;
}stack;
list* initialise_tree(list* root){
    root=NULL;
    return root;
}
stack* initialise_stack(unsigned int x){
    stack* ret=(stack*) malloc(sizeof(stack));
    ret->top=-1;
    ret->size=x;
    ret->arr=(int*)malloc(x * sizeof(int));
    return ret;
}
list *newNode(int item){
    list *temp = (list*)malloc(sizeof(list));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp; 
}
list* insert(list* node, int key){
    if (node == NULL)
    return newNode(key); 
    if (key < node->key) 
        node->left = insert(node->left, key);
    else if (key > node->key) 
        node->right = insert(node->right, key); 
    return node;
}
int is_full(stack* stk){
    if(stk->top==(stk->size-1))
        return 1;
    else
        return 0;
}
void push(stack* stk, int n){
    if(is_full(stk))
        printf("OVERFLOW OCCURRED!\n");
    else{
        stk->arr[++stk->top]=n;
        printf("%d pushed to stack.\n",stk->arr[stk->top]);
    }
}
int is_empty(stack* stk){
    if(stk->top==-1)
        return 1;
    else
        return 0;
}
list* minValNode(list* node){
    list* curr=node;
    while(curr && curr->left!=NULL)
        curr=curr->left;
    return curr;
}
int find(list* root, int n){
    if (root==NULL)
        return 0;
    else{
        if (n<root->key)
            find(root->left,n);
        else if(n>root->key)
            find(root->right,n);
        else
            return 1;
    }
}
list* del_Node(list* node, int n){
    if(node==NULL)
        return node;
    if(n<node->key)
        node->left=del_Node(node->left,n);
    else if(n>node->key)
        node->right=del_Node(node->right,n);
    else{
        if(node->left==NULL){
            list*temp=node->right;
            free(node);
            return temp;
        }
        else if (node->right==NULL){
            list* temp=node->left;
            free(node);
            return temp;
        }
        list* temp=minValNode(node->right);
        node->key=temp->key;
        node->right=del_Node(node->right,temp->key);
    }
    return node;
}
void pop(stack* stk){
    if(is_empty(stk))
        printf("STACK EMPTY!\n");
    else
        printf("%d popped from stack.\n",stk->arr[stk->top--]);
}
void preorder(list* node){
    int top=-1;
    list *s[50];
    while(1){
        while(node!=NULL){
            printf(" %d",node->key);
            s[++top]=node;
            node=node->left;
        }
        if(top==-1)
            break;
        node=s[top]->right;
        top=top-1;
    }
    printf("\n");
}
void display(stack* stk){
    if(stk->top==-1)
        printf("STACK EMPTY\n");
    else{
        printf("  STACK\n");
        for(int i=stk->top; i>=0; i--)
            printf("    %d\n",stk->arr[i]);
    }
}
void display_tree(list* root, int n){
    if (root==NULL){
        for (int i = 0; i < n-2; i++)
            printf(" ");
        printf("NULL\n");
    }
    else{
        display_tree(root->right,n+5);
        for (int i = 0; i < n+2; i++)
            printf(" ");
        printf("/\n");
        for (int i = 0; i < n; i++)
            printf(" ");
        printf("%d\n",root->key);
        for (int i = 0; i < n+2; i++)
            printf(" ");
        printf("\\\n");
        display_tree(root->left,n+5);
    }
}
int main(){
    int ch,d,x;
    stack *stk;
    list *T, *root;
    while(1){
        printf("\n");
        printf("1. Initialise Binary Search Tree \n");
        printf("2. Initialise the stack \n");
        printf("3. Insert in Tree \n");
        printf("4. Push in stack \n");
        printf("5. Delete an element from tree \n");
        printf("6. Pop from stack \n");
        printf("7. Pre-Order Traversal of Tree \n");
        printf("8. Display the stack \n");
        printf("9. Display Graphical Tree \n");
        printf("10. Exit Program \n");
        printf("Enter your choice: ");
        scanf("%d",&ch);
        if(ch==1){
            root=initialise_tree(root);
            printf("Binary Search Tree Initialised. \n");
        }
        else if(ch==2){
            printf("Enter size of the working Stack:\n");
            scanf("%d",&x);
            stk=initialise_stack(x);
            printf("Stack initialised. \n");
        }
        else if (ch==3){
            int n;
            printf("Enter the element: ");
            scanf("%d",&n);
            root=insert(root,n);
            printf("%d inserted in Binary Tree\n",n);
        }
        else if (ch==4){
            int n;
            printf("Enter the element: ");
            scanf("%d",&n);
            push(stk,n);
        }
        else if (ch==5){
            int d;
            printf("Enter No.to be deleted: ");
            scanf("%d",&d);
            if(find(root,d)==1){
                root=del_Node(root,d);
                printf("%d has been Deleted \n",d);
            }
            else
                printf("%d not found in tree.\n");
        }
        else if(ch==6)
            pop(stk);
        else if(ch==7){
            if(root==NULL)
                printf("SORRY, TREE EMPTY\n");
            else{
                printf("\nPRE-ORDER:\n");
                preorder(root);
            }
        }
        else if(ch==8)
            display(stk);
        else if(ch==9)
            display_tree(root,1);
        else if(ch==10){
            printf("Exitting, Thank You.\n");
            break;
        }
        else
            printf("Invalid Choice.\n");
    }
    return 0;
}