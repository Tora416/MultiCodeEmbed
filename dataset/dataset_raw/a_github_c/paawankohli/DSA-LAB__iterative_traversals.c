void Levelorder(Nodeptr root) 
{
    queue q;
    q.front = MAX/2;
    q.rear = MAX/2;

    InsertQ(&q, root);
    
    while (!QIsEmpty(&q)) 
    {
        Nodeptr temp = DeleteQ(&q);
        printf("%d ", temp->data);
    
        if (temp->lchild) 
            InsertQ(q, temp->lchild);
        
        if (temp->rchild) 
            InsertQ(q, temp->rchild);
    }
}

void iterative_inorder(Nodeptr root)
{
    Nodeptr cur = root;
    int done = false;
    
    STACK s; s.top = -1;
    
    while (!done) 
    {
        while (cur != NULL) 
        {
            push(&s, cur);
            cur = cur -> lchild;
        }
        
        if (isEmptyStack(s) == 0) 
        {
            cur = pop(&s);
            printf("%d ", cur -> data);
            cur = cur -> rchild;
        }
        else
            done = true;
    }
}

void iterative_preorder(nptr root)
{
    stack s; s.top = -1;
    nptr cur;

    push(&s, root);
    
    while (!IsEmpty(s)) 
    {
        cur = Pop(s);
        printf("%d", cur->data);
        
        if (cur -> rchild) 
            push(&s, cur -> rchild);
        
        if (cur -> lchild) 
            push(&s, cur -> lchild);
    }
}

void iterative_postorder(Nodeptr root)
{
    cur = root;
    for (; ;) 
    {
        while (cur != NULL) 
        { 
            s[++top].node = cur;
            s[top].flag = 1;
            cur = cur -> llink;
        }
        
        while (s[top].flag < 0) 
        {
            cur = s[top--].node;
            printf(“ % d”, curinfo);
            if (stack_empty(top))
                return;

        }
        cur = s[top].node; 

        cur = cur -> rlink;
        s[top].flag = -1;
    }
}