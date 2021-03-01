#include <stdio.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include "xtimer.h"

#define DST_ADDRESS "ff02::1"
#define UDP_PORT 0xF0B1
#define PACKET_MAXSIZE 512

uint8_t packet_data[PACKET_MAXSIZE];


static void run_udp_sender(void){
    int fd = 0;

    fd = socket(AF_INET6, SOCK_DGRAM,  IPPROTO_UDP);

    if(fd < 0){
        perror("Error : connot create socket \n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in6 addr_dst;
    addr_dst.sin6_family = AF_INET6;
    if(inet_pton(AF_INET6, DST_ADDRESS, &addr_dst.sin6_addr) != 1){
        printf("Error in the destination address : %s \n",DST_ADDRESS);
        exit(EXIT_FAILURE);
    }

    addr_dst.sin6_port = htons(UDP_PORT);
    memset(packet_data, 'a', PACKET_MAXSIZE);

    while(1){
        int data_size = 32;
        int status = sendto(fd, packet_data, data_size, 0, (struct sockaddr*)&addr_dst, sizeof(addr_dst));

        if(status < 0){
            perror("Error in sento \n");
            exit(EXIT_FAILURE);
        }

        xtimer_sleep(1);
    }

}

int main(void){
    run_udp_sender();
}
