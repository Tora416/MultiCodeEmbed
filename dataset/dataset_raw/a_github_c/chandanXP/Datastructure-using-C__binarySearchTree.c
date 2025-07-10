
#include<stdio.h>
#include<stdlib.h>


struct Node{
     int data;
     struct Node*left;
     struct Node*right;
     };

struct Node*create(int x){
     struct Node*temp=(struct Node*)malloc(sizeof(struct Node));
     temp->data=x;
     temp->left=NULL;
     temp->right=NULL;
}


void inOrderTraversal(struct Node *root){
     if(root==NULL){
          return;
     }else{
          inOrderTraversal(root->left);
          printf("%d ",root->data);
          inOrderTraversal(root->right);
          return;
     }
}


struct Node*insert(struct Node*root, int value){
     if(root==NULL){
          root = create(value);
     }
     else if(value<root->data){
          root->left = insert(root->left, value);
     }
     else if (value > root->data){
          root->right = insert(root->right, value);
     }

     
     else{
          printf("\nValue: %d you enterd is already exist\n", value);
     }

     return root;
}

struct Node*findMinimum(struct Node*root){
     
     if(root==NULL){
          return NULL;
     }
     else if(root->left!=NULL){
          return findMinimum(root->left);
     }
     return root;
}
struct Node*delete(struct Node*root, int value){
     if(root==NULL){
          printf("\nValue: %d is not present or the tree is empty!\n", value);
          return NULL;
     }
     else if(value<root->data){
          root->left = delete(root->left, value);
     }
     else if(value>root->data){
          root->right= delete(root->right, value);
     }
     else{
          
          if(root->left == NULL && root->right==NULL){
               
               free(root);
               return NULL;
          }
          
          else if(root->left ==NULL || root->right==NULL){
               
               
               struct Node*temp=root;
               if(root->left==NULL){
                    root=root->right;
               }
               else{
                    root=root->left;
               }
               free(temp);
               
          }
          
          else{
               
               
               struct Node*temp = findMinimum(root->right);
               root->data=temp->data;
               

               root->right= delete(root->right, temp->data);

          }
     }
     return root;
}

struct Node*verify(struct Node*root, int value){
     if(root==NULL){
          printf("\nThe Tree maybe Empty or value is not present...\n");
          return root;
     }
     else if(value<root->data){
          root->left= verify(root->left, value);
     }
     else if(value>root->data)
     {
          root->right= verify(root->right, value);
     }
     else if(root->data==value){
          printf("\nThe value you mentioned is present in this tree..(value: %d)\n", root->data);
     }
     else{
          printf("\nValue you entered is no present..\n");
     }
     return root;
     
}

int main(){
     
     struct Node*root=NULL;
     
     root=create(10);
     
     insert(root, 5);
     insert(root, 7);
     insert(root, 13);
     insert(root, 1);
     insert(root, 49);
     insert(root, 50);
     insert(root, 35);
     insert(root, 8);
     insert(root, 8);

     delete(root,49);
     delete(root,99);

     verify(root, 70);

     printf("\n--inOrder Traversal--\n");
     inOrderTraversal(root);

     return 0;
}