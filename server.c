#include <netinet/ip_icmp.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define PACKET_SIZE 64// Increased packet size to account for IP header

int main() {
    int sockfd;
    char buffer[PACKET_SIZE];
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    struct icmp *icmp_hdr;
    struct ip *ip_hdr;

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

        // IP header (first part of the packet)
        ip_hdr = (struct ip *)buffer;
        int ip_header_len = ip_hdr->ip_hl * 4;  // ip_hl is in 4-byte words

        // Parse ICMP header (after the IP header)
        icmp_hdr = (struct icmp *)(buffer + ip_header_len);

        // Check if the packet is an ICMP Echo Request (ping)
        if (icmp_hdr->icmp_type == ICMP_ECHO) {
            // Interpret the leftover area as data
            char *data = (char *)(buffer + ip_header_len + sizeof(struct icmp));
            printf("Received ICMP Echo Request from %s with data: %s\n", inet_ntoa(addr.sin_addr), data);
        }
    }

    close(sockfd);
    return 0;
}
