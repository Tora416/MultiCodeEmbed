
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/socket.h> 
#include<netinet/in.h> 




int main()
{
      
      char server_response[256];

      
      int network_socket;
      network_socket = socket(AF_INET,SOCK_STREAM,0); 
                                                      
  
  
      
      struct sockaddr_in server_address;
      server_address.sin_family = AF_INET;         
      server_address.sin_port = htons(9000);       
      server_address.sin_addr.s_addr = INADDR_ANY; 
                                                   
  
  
      
      int connection_status;
      connection_status = connect(network_socket, (struct sockaddr*)&server_address, sizeof(server_address)); 


      
      if(connection_status == -1)
        printf("Error occur during creating the connection.\n");


      
      recv(network_socket, &server_response, sizeof(server_response),0);
  

      
      if(connection_status != -1)
        printf("%s",server_response);
  

      
      
  

      
      close(network_socket);
  
      return 0;
}






