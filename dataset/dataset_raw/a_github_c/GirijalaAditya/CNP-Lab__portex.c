#include<stdio.h> 
#include<sys/socket.h> 
#include<stdlib.h> 
#include<netinet/in.h> 
#include<sys/types.h> 
#include<arpa/inet.h>
#include<time.h> 
#include<string.h> 
int main() 
{ 
int sockfd; 
struct sockaddr_in serv_addr; 
time_t  now; 
char timestr[100]; 
char a[50],a1[50]; 
sockfd=socket(AF_INET,SOCK_STREAM,0); 
if(sockfd<0) 
{ 
printf("\n Socket Failed"); 
exit(0); 
} 
serv_addr.sin_family=AF_INET; 
serv_addr.sin_addr.s_addr=inet_addr("192.168.125.129"); 
serv_addr.sin_port=htons(13); 
if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0) 
{ 
printf("\n Connection Failed"); 
exit(0); 
} 
time(&now); 
sprintf(timestr,"%s",ctime(&now)); 
printf("%s",timestr); 
 
 
 

 
close(sockfd); 
} 
