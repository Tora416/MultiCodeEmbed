node* mergeTwoLLs(node *head1, node *head2) 
{
    node* t1 = head1;
    node* t2 = head2;
    
    node* head;
    node* tail;
    
    if(head1->data <= head2->data)
    {
        head = head1;
        tail = head1;
        t1 = t1->next;
    }   
    else 
    {
        head = head2;  
        tail = head2;
        t2 = t2->next;
    }
        
    while(t1 != NULL && t2 != NULL)
        if(t1->data <= t2->data)
        {
            tail->next = t1;
            tail = t1;
            t1 = t1->next;
        }   
        else
        {
            tail->next = t2;
            tail = t2;
            t2 = t2->next;
        }
    
    if(t1 == NULL)
        tail->next = t2;
    
    else
        tail->next = t1;
    
    return head;
}