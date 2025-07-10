void insertNode(nptr root, int x, char path[])
{
    int i = 0;
    nptr parent = NULL, curr = root;

    while(curr && path[i])
    {
        parent = curr;

        if (path[i] == 'L')
            curr = parent -> lchild;
        else if (path[i] == 'R')
            curr = parent -> rchild;

        i++;
    }

    if (curr == NULL || path[i] == '\0')
    {
        if (path[i - 1] == 'R')
            parent -> rchild = createNode(x);
        else if (path[i - 1] == 'L')
            parent -> lchild = createNode(x);
    }
    else
        printf("Path error!");
}

nptr createBT()
{
    int x;    printf("Insert Element: ");    scanf("%d", &x);

    if(x == -1)
        return NULL;

    nptr temp = createNode(x);
    temp -> lchild = createBT();
    temp -> rchild = createBT();
    return temp;
}