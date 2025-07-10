

   




#include "tree.h"



struct database {
    int roll_no;
    struct database *left;
    struct database *right;
};

extern struct database * root;
struct database *root = NULL;


void add_element(void);


void print_element(void);


void inorder(struct  database *node);
void preorder(struct  database *node);
void postorder(struct  database *node);

void inorder_1(struct  database *node);
void preorder_1(struct  database *node);
void postorder_1(struct  database *node);

int main(){
    add_element();
    add_element();
    add_element();
    add_element();
    add_element();
    add_element();

    printf("Inorder\n");
    inorder(root);
    printf("preorder\n");
    preorder(root);
    printf("postorder\n");
    postorder(root);
    printf("Inorder_1\n");
    inorder_1(root);
    printf("preorder_1\n");
    preorder_1(root);
    printf("postorder_1\n");
    postorder_1(root);

    return 0;
}

void add_element(void) 
{
    struct database * current_node = root;
    struct database * temp_ptr = (struct database* )malloc (sizeof(struct database ));

    printf("Enter the value:");
    scanf("%d",&temp_ptr->roll_no);

    temp_ptr->left = NULL;
    temp_ptr->right = NULL;
    
    if(root == NULL){
        root = temp_ptr;
    } else {
        while (current_node != NULL) {
            if(temp_ptr->roll_no > current_node->roll_no){
                if (current_node->right !=NULL){
                    current_node = current_node ->right;
                } else {
                    current_node->right = temp_ptr;
                    return;
                }
            }else {
                if(current_node->left !=NULL){
                    current_node = current_node->left;
                }else {
                    current_node->left = temp_ptr;
                    return;
                }
            }
        }
    }

}



void inorder(struct  database *node){
    if(node == NULL){
        return;
    } else { 
        inorder(node->left);
        printf("%d\n",node->roll_no);
        inorder(node->right);
    }
}

void preorder(struct database *node){
    if(node == NULL) {
        return;
    } else {
        printf("%d\n",node->roll_no);
        preorder(node->left);
        preorder(node->right);
    }
}

void postorder(struct database *node){
    if(node == NULL) {
        return;
    } else {
        postorder(node->left);
        postorder(node->right);
        printf("%d\n",node->roll_no);
    }
}

void inorder_1(struct database *node){
    if(node == NULL){
        return;
    } else {
        inorder_1(node->right);
        printf("%d\n",node->roll_no);
        inorder_1(node->left);
    }
}

void preorder_1(struct database *node){
    if(node == NULL) {
        return;
    } else {
        printf("%d\n",node->roll_no);
        preorder_1(node->right);
        preorder_1(node->left);
    }
}

void postorder_1(struct database *node){
    if(node == NULL) {
        return;
    } else {
        postorder_1(node->right);
        postorder_1(node->left);
        printf("%d\n",node->roll_no);
    }
}
