

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void err_thread(int ret, char *str)
{
    if(ret != 0)
    {
        fprintf(stderr, "%s:%s\n", str, strerror(ret));
        pthread_exit(NULL);
    }
}

struct msg
{
    int num;
    struct msg *next; 
};
struct msg *head;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;      
pthread_cond_t has_data = PTHREAD_COND_INITIALIZER;     

void *producer(void *arg)
{
    while(1)
    {
        struct msg *mp = malloc(sizeof(struct msg));
        mp->num = rand() % 1000 + 1;                    
        printf("-----produce %d\n", mp->num);

        pthread_mutex_lock(&mutex);                     
        mp->next = head;                                
        head = mp;
        pthread_mutex_unlock(&mutex);                   

        pthread_cond_signal(&has_data);              

        sleep(rand()%3);
    }

    return NULL;
}

void *comsumer(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);                     

        while(head == NULL)                             
        {
            pthread_cond_wait(&has_data, &mutex);       
        }                                               

        struct msg *mp = head;
        head = head->next;
         
        pthread_mutex_unlock(&mutex);                   
        printf("----------comsumer id: %lu : %d\n", pthread_self(), mp->num);

        free(mp);
        sleep(rand()%3);
    }

    return NULL;
}

int main()
{
    srand(time(NULL));

    pthread_t pid, cid1, cid2, cid3;
    int ret = pthread_create(&pid, NULL, producer, NULL);   
    if(ret != 0)
        err_thread(ret, "pthread_create producer error");

    ret = pthread_create(&cid1, NULL, comsumer, NULL);       
    if(ret != 0)
        err_thread(ret, "pthread_create comsumer error");

    ret = pthread_create(&cid2, NULL, comsumer, NULL);       
    if(ret != 0)
        err_thread(ret, "pthread_create comsumer error");
    
    ret = pthread_create(&cid3, NULL, comsumer, NULL);       
    if(ret != 0)
        err_thread(ret, "pthread_create comsumer error");

    pthread_join(pid, NULL);
    pthread_join(cid1, NULL);
    pthread_join(cid2, NULL);
    pthread_join(cid3, NULL);

    return 0;
}