void postorder(node *t)     
{ 
    STACK s;
    node*curr;
    curr=t;
    s.tos=-1;

    do
    { 
        while (curr!=NULL) 
        { 
            if (curr->right!=NULL) 
                push(&s, curr->right); 
            
            push(&s, curr); 
            curr=curr->left; 
        } 
        
        curr = pop(&s); 
        
        if (curr->right!=NULL && s.s[s.tos]==curr->right) 
        { 
            pop(&s); 
            push(&s,curr);
            curr=curr->right;
        } 
        
        else 
        { 
            printf("%d\t",curr->data); 
            curr=NULL; 
        } 
    
    }while (s.tos!=-1); 
}