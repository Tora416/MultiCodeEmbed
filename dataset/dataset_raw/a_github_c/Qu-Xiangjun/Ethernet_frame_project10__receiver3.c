
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
# include "crc32.h"

unsigned char frame[2000];  
unsigned char sta_addr[6];
unsigned char des_addr[6];
unsigned short protocol;
unsigned char *payload;
unsigned int frame_len;
unsigned int payload_len;
unsigned char my_addr[6] = {0x42,0x23,0x52,0xb5,0xa6,0xc3};  


void welcome()
{
    printf("[INFO] Usage: frame receiver process.\n");
    printf("[INFO] My address  : ");
    output_octal(my_addr,6);
}

 
int addr_check(unsigned char des_addr[6]){
    int flag = 1;
    int i =0;
    for(i = 0;i<6;i++){
        if(des_addr[i] != my_addr[i]) flag = 0;
    }
    if(flag){
        printf("[INFO] Address check success!\n");
    }else {
        printf("[Error] Address check error!\n");
    }
    return flag;
}

 
int output_octal(unsigned char *x,unsigned int len) {
    int i;
    for (i =0;i<len;i++) {
        printf("%02x",x[i]);
        if (i != len-1) printf(" ");
        if(i %9 == 0 && i!=0) printf("\n");
    }
    printf("\n");
    return 0;
}

 
int receive_frame(){
    FILE *file = fopen("pipe.bin", "r");

    
    fread(&frame_len,sizeof(frame_len),1,file);
    printf("[INFO] frame length: %d\n",frame_len);
    if(frame_len < 64){  
        printf("[Error] Payload length too low!\n");
        exit(1);
    }else if(frame_len >1518){
        printf("[Error] Payload length too long!\n");
        exit(1);
    }

    
    fread(&frame,sizeof(char),frame_len,file);
    
    memcpy(&des_addr,&frame[0],6);
    memcpy(&sta_addr,&frame[6],6);
    memcpy(&protocol,&frame[12],sizeof(protocol));
    payload = &frame[14];    
    
    
    if(!addr_check(des_addr))   exit(1);

    
    init_crc_table();
    unsigned int crc32_temp = crc32(frame,frame_len-4);
    unsigned char crc32_result[4];
    memcpy(crc32_result,&crc32_temp,sizeof(crc32_temp));

    int i = 0;
    int flag_crc32 = 1;
    for(i = 3;i<sizeof(crc32_result);i--){
        if(crc32_result[i] != frame[frame_len-(4-i)]) flag_crc32 = 0;
    }
    if(flag_crc32){
        printf("[INFO] CRC32 check success!\n");
    }else {
        printf("[Error] CRC32 check error!\n");
        printf("[Error] frame's CRC32 : ");
        printf("%02x %02x %02x %02x\n",frame[frame_len-4],frame[frame_len-3],frame[frame_len-2],frame[frame_len-1]);
        printf("[Error] calculated CRC32 : ");
        output_octal(crc32_result,4);
        exit(1);
    }

    
    printf("******Received frame information******\n");
    printf("Start address: ");
    output_octal(sta_addr,6);
    printf("Des address  : ");
    output_octal(des_addr,6);
    printf("protocol     : %d\n",protocol);
    printf("payload      : ");
    output_octal(payload,frame_len-6-6-2-4);
    printf("CRC32        : ");
    output_octal(crc32_result,4);
    printf("**************************************\n");
    printf("[INFO] Frame received success!\n");
}

int main(){
    welcome();
    receive_frame();
}



