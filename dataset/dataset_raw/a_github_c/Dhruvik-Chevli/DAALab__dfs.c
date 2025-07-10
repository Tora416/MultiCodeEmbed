#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define FOR(i,a,b) for(ll i=a;i<b;i++)
typedef long long int ll;
ll** makeGraph(ll v)
{
    ll e;
    ll** graph=(ll**)malloc(v*sizeof(ll*));
    FOR(i,0,v)
    {
        graph[i]=malloc(v*sizeof(ll));
    }
    FOR(i,0,v)
    {
        FOR(j,0,v)
        {
            graph[i][j]=0;
        }
    }
    scanf("%lld",&e);
    ll src,dest;
    FOR(i,0,e)
    {
        scanf("%lld %lld",&src,&dest);
        graph[src][dest]=1;
        graph[dest][src]=1;
    }
    return graph;
}
void dfs(ll** graph, ll* visited, ll v, ll src)
{
    visited[src]=1;
    printf("%lld ",src);
    
    FOR(i,0,v)
    {
        if(graph[src][i])
        {
            if(!visited[i])
            {
                dfs(graph,visited,v,i);
            }
        }
    }
    return;
}
int main()
{
    ll v;
    scanf("%lld",&v);
    ll** graph=makeGraph(v);
    ll* visited=(ll*)malloc(v*sizeof(ll));
    FOR(i,0,v)
    {
        visited[i]=0;
    }
    FOR(i,0,v)
    {
        if(!visited[i])
        {
            dfs(graph,visited,v,i);
            printf("\n");
        }
    }
    return 0;

}