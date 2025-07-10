           




           

#include "read_data_print.h"

int main()
{
   int fd,m_sync,unmap;
   char *addr;
   ssize_t rd;
   char buffer[20];

   
   fd = shm_open("/posix", O_RDWR , 0);
   perror("shm_open");

   
   addr = mmap(NULL, 20 , PROT_READ | PROT_WRITE , MAP_SHARED, fd, 0);
   perror("mmap");

   printf("%s\n",addr);

   
   
   shm_unlink("/posix");
}
