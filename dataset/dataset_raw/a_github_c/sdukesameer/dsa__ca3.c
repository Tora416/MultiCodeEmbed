#include <stdio.h>
#include <stdlib.h>
#define MAX 50
typedef struct bs_tree{
    int data;
    struct bs_tree *left, *right;
}BS_TREE; 
typedef struct queue{
   BS_TREE *elements[MAX];
    int front, rear; 
}QUEUE;
void initialiseQueue (QUEUE *aq){
    aq->front =-1; 
    aq->rear =-1;
}
void addQueue (BS_TREE * at, QUEUE *aq){

    if (aq->rear == MAX-1)
        exit(0); 
 
    else
        aq->elements [++(aq->rear)]=at;

}
BS_TREE* deleteQueue (QUEUE *aq){
     BS_TREE *p;
    
    if (aq->front != aq->rear){
        p= aq->elements [++(aq->front)];
        if (aq->front == aq->rear)
        
        initialiseQueue (aq);
        return p; 
    }
    else 
        return NULL; 
}
int  isEmptyQueue (QUEUE q) {
    return (q.front == -1);
}
void initialise_tree (BS_TREE **aar){
        *aar = NULL;
}
void rec_insert (BS_TREE **aar, int n){
    if (*aar == NULL){
       *aar=(BS_TREE *)malloc(sizeof(BS_TREE));
        (*aar)->data=n;
        (*aar)->left=(*aar)->right=NULL;
    } 
    else if (n<(*aar)->data)
        rec_insert(&((*aar)->left), n); 
    else
        rec_insert(&((*aar)->right), n); 
}
void level_order_Traversal (BS_TREE *ar){
    QUEUE q;
    BS_TREE *ptr;
    
    initialiseQueue (&q);
    
    addQueue (ar, &q);
        
    while (! isEmpty(q)){
            
        ptr = deleteQueue (&q);
            
        if ( ptr->left != NULL ) 
            addQueue (ptr->left, &q);
            
        if ( ptr->right != NULL ) 
            addQueue (ptr->right, &q);
        printf("\t %d", ptr->data);            
    }
}