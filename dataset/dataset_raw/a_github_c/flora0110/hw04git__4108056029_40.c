#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct all{
    int *ori;
    int *chan_to;
}All;
int at_where(char**,char*,int*);
int pass(All*,int*,int,int,int);
int main(){
    FILE* rptr;
    rptr=fopen("test8.txt","r");
    if(rptr==NULL){
        printf("error\n");
        return 0;
    }
    int n,i,j;
    fscanf(rptr,"%d\n",&n);
    char* token;
    const char* delim = " ";
    All* all=(All*)malloc(300*sizeof(All));
    int alln=0;
    char **obj=(char**)malloc(18000*sizeof(char*));
    int objn=0;
    int flyat,pigat;
    int* ori;
    int* chan_to;
    for(i=0;i<n;i++){
        char str[300];
        fgets(str,300,rptr);
        token = strtok(str,delim);
        int chan=0;
        ori=(int*)malloc(18000*sizeof(int));
        chan_to=(int*)malloc(18000*sizeof(int));
        int orin=0,chan_ton=0;
        int isthat=0;
        while( token != NULL ){
            if('Z'>=token[0] && token[0]>='A'){
                if(token[strlen(token)-1]=='\n') token[strlen(token)-1]='\0';
                int at=at_where(obj,token,&objn);
                if(chan==0){
                    ori[orin++]=at;
                }
                else if(chan==1){
                    chan_to[chan_ton++]=at;
                }
                if (strlen(token)==3 && strncmp("FLY",token,strlen(token))==0) flyat=at;
                else if (strlen(token)==4 && strncmp("PIGS",token,strlen(token))==0) pigat=at;

            }
            if((strlen(token)==3 && strncmp("are",token,strlen(token))==0)||\
                (strlen(token)==3 && strncmp("can",token,strlen(token))==0) && isthat==0 ||\
                (strlen(token)==4 && strncmp("have",token,strlen(token))==0)){
                chan=1;
            }
            if(strlen(token)==4 && strncmp("that",token,strlen(token))==0){
                isthat=1;
            }
            if(strlen(token)==3 && strncmp("can",token,strlen(token))==0 && isthat==1){
                isthat=0;
            }
            token=strtok(NULL,delim);
        }
        ori[orin]=-1;
        chan_to[chan_ton]=-1;
        all[alln].ori=ori;
        all[alln++].chan_to=chan_to;
    }
    int *test=(int*)malloc((objn+1)*sizeof(int));
    memset(test,0,objn+1);
    test[pigat]=1;
    int allcheck=pass(all,test,alln,flyat,pigat);
    while(allcheck!=0 && allcheck!=2){
        allcheck=pass(all,test,alln,flyat,pigat);
    }
    if(allcheck==2){
        printf("All pigs can fly\n");
    }
    else{
        for(i=0;i<objn;i++){
            for(j=0;j<objn;j++){
                test[j]=0;
                if(j==i) test[j]=1;
            }
            allcheck=pass(all,test,alln,flyat,pigat);
            while(allcheck!=0 && allcheck!=2){
                allcheck=pass(all,test,alln,flyat,pigat);
            }
            if(allcheck==2) {
                break;
            }
        }
        if(allcheck==2){
            printf("Some pigs can fly\n");
        }
        else{
            printf("No pigs can fly\n");
        }
    }
}
int pass(All all[300],int* test,int alln,int flyat,int pigat){
    int i,j,allcheck=0;
    for(i=0;i<alln;i++){
        int check=1;
        for(j=0;all[i].ori[j]!=-1;j++){
            if(test[all[i].ori[j]]==0) {
                check=0;
                break;
            }
        }
        if(check){
            for(j=0;all[i].chan_to[j]!=-1;j++){
                if(test[all[i].chan_to[j]]==0) allcheck=1;
                test[all[i].chan_to[j]]=1;
            }
        }
    }
    if(test[flyat]==1 && test[pigat]==1){
        return 2;
    }
    else {
        return allcheck;
    }
}
int at_where(char** obj,char* token,int* objn){
    int i,j,check=0;
    char *new=(char*)malloc(300*sizeof(char));
    for(i=0;i<strlen(token);i++){
        new[i]=token[i];
    }
    new[i]='\0';
    for(i=0;i<*objn;i++){
        if(strcmp(obj[i],token)==0 && strncmp(obj[i],token,strlen(token))==0){
            check=1;
            return i;
        }
    }
    if(!check){
        obj[(*objn)++]=new;
        return (*objn)-1;
    }
}
