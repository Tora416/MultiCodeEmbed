


#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s)\
    if(!((p)=malloc(s))){\
        fprintf(stderr,"Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
typedef struct howto{
    int toplat;
    int tostat;
}howto;

int min;
howto fewstep(int now,int target,int* plat){
    min=-1;
    int i;
    howto ans;
    int sum;
    int toplat,tostat;
    int right,left;
    int pr,pl;
    for(i=0;i<20;i++){
        if(i-now<0){
            pr=i+1+19-now;
        }
        else{
            pr=i-now;
        }
        if(now-i<0){
            pl=i+1+19-now;
        }
        else{
            pl=now-i;
        }
        toplat= (pr<pl)? pr:-pl;
        if(target-plat[i]<0){
            right = (90-plat[i])+1+target-64;
        }
        else{
            right=target-plat[i];
        }
        if(plat[i]-target<0){
            left = plat[i]-64+1+90-target;
        }
        else{
            left=plat[i]-target;
        }
        tostat= (right<left)? right:-left;
        sum=abs(tostat)+abs(toplat);
        if(min==-1 || sum<min){
            min=sum;
            ans.toplat=toplat;
            ans.tostat=tostat;
        }
    }
    return ans;
}

typedef struct howto2{
    int toplat;
    int tostat;
    int toplat2;
    int tostat2;

}howto2;
howto2 fewstep2(int now,int target,int target2,int* plat){
    min=-1;
    int i,j;
    howto2 ans;
    int sum;
    int toplat,tostat;
    int right,left;
    int pr,pl;
    int sum2;
    int toplat2,tostat2;
    int right2,left2;
    int pr2,pl2;
    int temp;
    for(i=0;i<20;i++){
        if(i-now<0){
            pr=i+1+19-now;
        }
        else{
            pr=i-now;
        }
        if(now-i<0){
            pl=i+1+19-now;
        }
        else{
            pl=now-i;
        }
        toplat= (pr<pl)? pr:-pl;
        
        if(target-plat[i]<0){
            right = (90-plat[i])+1+target-64;
        }
        else{
            right=target-plat[i];
        }
        if(plat[i]-target<0){
            left = plat[i]-64+1+90-target;
        }
        else{
            left=plat[i]-target;
        }
        tostat= (right<left)? right:-left;
        
        sum=abs(tostat)+abs(toplat);
        
        temp=plat[i];
        plat[i]=target;
        

        for(j=0;j<20;j++){

            
            if(j-i<0){
                pr2=j+1+19-i;
            }
            else{
                pr2=j-i;
            }
            
            if(i-j<0){
                pl2=j+1+19-i;
            }
            else{
                pl2=i-j;
            }
            
            toplat2= (pr2<pl2)? pr2:-pl2;
            
            if(target2-plat[j]<0){
                right2 = (90-plat[j])+1+target2-64;
            }
            else{
                right2=target2-plat[j];
            }
            if(plat[j]-target2<0){
                left2 = plat[j]-64+1+90-target2;
            }
            else{

                left2=plat[j]-target2;
            }
            

            tostat2= (right2<left2)? right2:-left2;
            
            sum2=abs(tostat2)+abs(toplat2);
            
            
            if(min==-1 || sum+sum2<min){
                min=sum+sum2;
                ans.toplat=toplat;
                ans.tostat=tostat;
                ans.toplat2=toplat2;
                ans.tostat2=tostat2;
            }

        }
        plat[i]=temp;
    }
    return ans;
}
int main(){
    int i;
    int *plat=malloc(20*sizeof(int));
    int *plat2=malloc(20*sizeof(int));
    for(i=0;i<20;i++){
        plat[i]=64;
        plat2[i]=plat[i];
    }
    FILE* rptr;
    FILE* wfile;
    rptr=fopen("test2-2.txt","r");
    wfile=fopen("output2-2.txt","w");
    if(rptr==NULL || wfile==NULL){
        printf("open failure\n");
        return 1;
    }
    else{
        min = -1;
        int now=0;
        int now2=0;
        char target;
        char lasttarget;
        howto ans;
        howto2 ans2;
        int i;
        int count=1;
        char *command;
        char *command2;
        MALLOC(command,10000*sizeof(char));
        MALLOC(command2,10000*sizeof(char));
        target=fgetc(rptr);
        int totalstep=0;
        int totalstep2=0;
        int j1=0,j2=0;
        while(target!='\n' && target!=EOF){
            if(target==' '){
                target='@';
                
            }
            ans=fewstep(now,target,plat);
            now+=ans.toplat;
            plat[now]=target;
            for(i=0;i<abs(ans.toplat);i++){
                if(ans.toplat>0){
                    
                    command[j1++]='>';
                }
                else{
                    
                    command[j1++]='<';
                }
                totalstep++;
            }
            for(i=0;i<abs(ans.tostat);i++){
                if(ans.tostat>0){
                    
                    command[j1++]='+';
                }
                else{
                    
                    command[j1++]='-';
                }
                totalstep++;
            }
            
            command[j1++]='.';
            totalstep++;
            
            if(count==1){
                lasttarget=target;
                count++;
            }
            else if(count==2){
                count=1;
                ans2=fewstep2(now2,lasttarget,target,plat2);
                now2+=ans2.toplat;
                plat2[now2]=lasttarget;
                for(i=0;i<abs(ans2.toplat);i++){
                    if(ans2.toplat>0){
                        
                        command2[j2++]='>';
                    }
                    else{
                        
                        command2[j2++]='<';
                    }
                    totalstep2++;
                }
                for(i=0;i<abs(ans2.tostat);i++){
                    if(ans2.tostat>0){
                        
                        command2[j2++]='+';
                    }
                    else{
                        
                        command2[j2++]='-';
                    }
                    totalstep2++;
                }
                
                
                command2[j2++]='.';
                totalstep2++;
                now2+=ans2.toplat2;
                plat2[now2]=target;
                for(i=0;i<abs(ans2.toplat2);i++){
                    if(ans2.toplat2>0){
                        
                        command2[j2++]='>';
                    }
                    else{
                        
                        command2[j2++]='<';
                    }
                    totalstep2++;
                }
                for(i=0;i<abs(ans2.tostat2);i++){
                    if(ans2.tostat2>0){
                        
                        command2[j2++]='+';
                    }
                    else{
                        
                        command2[j2++]='-';
                    }
                    totalstep2++;
                }
                
                command2[j2++]='.';
                totalstep2++;
                
                
            }

            target=fgetc(rptr);
        }
        if(count==2){
            
            ans=fewstep(now2,target,plat2);
            now2+=ans.toplat;
            plat2[now2]=target;
            for(i=0;i<abs(ans.toplat);i++){
                if(ans.toplat>0){
                    
                    command2[j2++]='>';
                }
                else{
                    
                    command2[j2++]='<';
                }
                totalstep2++;
            }
            for(i=0;i<abs(ans.tostat);i++){
                if(ans.tostat>0){
                    
                    command2[j2++]='+';
                }
                else{
                    
                    command2[j2++]='-';
                }
                totalstep2++;
            }
            
            command2[j2++]='.';
            totalstep2++;
        }
        printf("\ntotalstep1 %d \n",totalstep );
        if(totalstep<=totalstep2){
            for(i=0;i<j1;i++){
                printf("%c",command[i]);
                fprintf(wfile,"%c",command[i]);
            }
            
            fprintf(wfile,"\ntotalstep :%d\n",totalstep );
        }
        else{
            for(i=0;i<j2;i++){
                printf("%c",command2[i]);
                fprintf(wfile,"%c",command2[i]);
            }
            
            fprintf(wfile,"\ntotalstep :%d\n",totalstep );
        }
    }
    fclose(rptr);
    fclose(wfile);
}
