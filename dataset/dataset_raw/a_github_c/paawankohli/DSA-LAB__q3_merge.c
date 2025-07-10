#include<stdio.h>
#include<stdlib.h>
typedef struct node* nodeptr;
typedef struct node{
    int data;
    nodeptr link;
}node;


void add(nodeptr head,int x){
    nodeptr temp=malloc(sizeof(node));
    nodeptr t;
    temp->data=x;
    temp->link=head;
        for(t=head;t->link!=head;t=t->link);
        t->link=temp;
}
void init(nodeptr* head){
    nodeptr temp=malloc(sizeof(node));
    temp->data=-1;
    temp->link=temp;
    *head=temp;
}
void merge(nodeptr a,nodeptr b){
    nodeptr trail1,trail2,temp1,temp2,i;
    trail1=a;
    trail2=b;
    temp1=trail1->link;
    temp2=trail2->link;
    while(temp1!=a&&temp2!=b){
        if(temp1->data<temp2->data){
            trail1=trail1->link;
            temp1=temp1->link;
        }
        else if(temp1->data==temp2->data){
            trail2->link=temp2->link;
            temp2->link=temp1->link;
            temp1->link=temp2;
            temp2=trail2->link;
            trail1=trail1->link->link;
            temp1=temp1->link->link;
        }
        else{
            trail2->link=temp2->link;
            trail1->link=temp2;
            temp2->link=temp1;
            temp2=trail2->link;
            trail1=trail1->link;
        }
    }
    if(temp2!=b){
    trail1->link=temp2;
    for(i=temp2;i->link!=b;i=i->link);
    i->link=temp1;
    free(trail2);
}
}
void display(nodeptr a){
    nodeptr t=a;
    printf("\n");
    for(a=a->link;a!=t;a=a->link){
        printf("\t%d",a->data);
    }
}
int main(){
    nodeptr a,b,u,in;
    int n,m,i,t;
    init(&a);
    init(&b);
    printf("\nEnter number elements of first list");
    scanf("%d",&n);
    printf("\nEnter elements");
    for(i=0;i<n;i++){
        scanf("%d",&t);
        add(a,t);
    }
    printf("\nEnter number elements of second list");
    scanf("%d",&m);
    printf("\nEnter elements");
    for(i=0;i<m;i++){
        scanf("%d",&t);
        add(b,t);
    }
    display(a);
    display(b);
    merge(a,b);
    display(a);
}