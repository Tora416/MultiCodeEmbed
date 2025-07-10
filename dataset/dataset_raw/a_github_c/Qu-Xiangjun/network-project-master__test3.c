
#include <stdio.h>
#include <stdlib.h>

unsigned short Checksum(unsigned char* buffer, unsigned short size){
    unsigned int sum = 0;
    unsigned short cksum;
    unsigned char lower,higher;
    unsigned short temp;
    while(size > 1){
        lower = buffer[size-1];
        higher = buffer[size - 2];
        temp = higher;
        temp = (temp << 8) + lower;
        printf("%04x\n",temp);
        sum += temp;
        size -= 2;
    }
    if(size == 1){  
        lower = buffer[size-1];
        higher = 0x00;
        temp = higher;
        temp = (temp << 8) + lower;
        sum += temp;
    }
    cksum = (sum >> 16) + (sum & 0xffff);
    cksum = ~cksum;
    printf("%04x\n",cksum);
    return cksum;
}

  int main(){
      unsigned char data[] = {0x47,0x00,0x87,0x00,0x00,0x00,0x00,0x00,0x14,0x00,0x4d,0x5f,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x02,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x00};
      unsigned short ck = Checksum(data,sizeof(data));
      printf("%04x",ck);
  }
