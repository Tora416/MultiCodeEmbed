
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crc16.h"
#include "output_octal.h"

int fragmention(){
    
}


unsigned int datagram_construction(unsigned char datagram[65535],unsigned char Version,
                            unsigned char Differentialted_Services,unsigned short Identification,
                            unsigned short DF, unsigned short MF,
                            unsigned short Fragment_offset, unsigned char TTL, 
                            unsigned char Protocol,
                            unsigned char *Source_address, unsigned char *Destination_address,
                            unsigned char *Option,unsigned int Option_len,
                            unsigned *payload,unsigned short payload_len){
    
    if (payload_len > 65515){
        printf("[Error] Payload length too long!\n");
        exit(1);
    }
    
    
    unsigned char IHL = 5 + Option_len; 
    printf("IHL%d\n",IHL);

    
    unsigned char temp = 0x00;
    Version = Version << 4;  
    temp = temp | IHL; 
    temp = temp | Version; 
    memcpy(&datagram[0],&temp,1);

    memcpy(&datagram[1],&Differentialted_Services,1);

    
    unsigned short Total_length = payload_len + IHL*4; 
    memcpy(&datagram[2],&Total_length,2);
    memcpy(&datagram[4],&Identification,2);

    
    unsigned short temp2;
    short df = DF;
    df = df << 14;
    df = df & 0x4000;  
    short mf = MF;
    mf = mf << 13;
    mf = mf & 0x2000; 
    Fragment_offset = Fragment_offset & 0x1FFF; 
    temp2 = df | mf | Fragment_offset;
    memcpy(&datagram[6],&temp2,2);

    memcpy(&datagram[8],&TTL,1);
    memcpy(&datagram[9],&Protocol,1);
    memcpy(&datagram[12],Source_address,4);
    memcpy(&datagram[16],Destination_address,4);
    memcpy(&datagram[20],Option,Option_len*4);
    
    
    unsigned char Header[IHL * 4 - 2]; 
    memcpy(&Header[0],&datagram[0],10);
    memcpy(&Header[10],&datagram[12],8 + Option_len * 4);
    unsigned short Header_checksum = CRC16(Header,IHL * 4 - 2);
    memcpy(&datagram[10],&Header_checksum,2); 
    
    unsigned char crc16_result[2];
    memcpy(crc16_result, &Header_checksum, sizeof(Header_checksum));

    memcpy(&datagram[20 + Option_len*4],payload,payload_len);

     
    printf("******Send datagrame information******\n");
    printf("Source address: ");
    output_octal(Source_address,4);
    printf("Destinamtion address  : ");
    output_octal(Destination_address,4);
    printf("payload      : %s\n",payload);
    printf("CRC16        : ");
    output_octal(crc16_result, 2);    
    printf("payload length  : %d\n", payload_len);
    printf("Header length   : %d(row*4bytes)\n", IHL);
    printf("datagram length : %d\n", Total_length);
    printf("**************************************\n");
    printf("[INFO] datagram send success!\n");
    return Total_length;
}

int send_datagram(){

}

