#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PACKET_SIZE 128

int main() {
    int sockfd;
    char buffer[PACKET_SIZE];
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    struct icmp *icmp_hdr;

    // Create raw socket
    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0) {
        perror("Socket error");
        return 1;
    }

    printf("Listening for ICMP packets...\n");

    while (1) {
        // Receive ICMP packet
        int recv_len = recvfrom(sockfd, buffer, PACKET_SIZE, 0, (struct sockaddr *)&addr, &addr_len);
        if (recv_len < 0) {
            perror("Recvfrom error");
            return 1;
        }

        // Parse ICMP header
        icmp_hdr = (struct icmp *)buffer;
        if (icmp_hdr->icmp_type == ICMP_ECHO) {
            // Interpret the leftover area as data
            char *data = buffer + sizeof(struct icmp);
            printf("Received ICMP packet from %s with data: %s\n", inet_ntoa(addr.sin_addr), data);
        }
    }

    close(sockfd);
    return 0;
}
