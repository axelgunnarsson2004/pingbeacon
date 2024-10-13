#include <stdio.h> 
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <unistd.h>



#define PACKET_SIZE 128 

unsigned short checksum(void *b, int len){
  unsigned short *buf = b;
  unsigned int sum = 0;
  unsigned short result;
  
  for (sum = 0; len>1;len-=2)
    sum += *buf++;
  if (len ==1)
    sum += *(unsigned char*) buf;
  sum = (sum >> 16) + (sum & 0xFFFF);
  sum += (sum>>16);
  result = ~sum; 
  
  return result;

}
  
int main(int argc, char *argv[]){ 
  if (argc !=3 ){
    printf("Usage: %s <destination IP> <data>\n", argv[0]);
      return 1;
  }
  int sockfd;
  char packet[PACKET_SIZE];
  struct icmp *icmp_hdr;
  struct sockaddr_in dest_addr;
  
  sockfd = socket(AF_INET,SOCK_RAW,IPPROTO_ICMP);
  if (sockfd<0){
    perror("Socket Error");
    return 1;
  }
  
  memset(&dest_addr,0,sizeof(dest_addr));
  dest_addr.sin_family = AF_INET;
  dest_addr.sin_addr.s_addr = inet_addr(argv[1]);
  
  memset(packet,0,PACKET_SIZE);
  
  icmp_hdr = (struct icmp *)packet;
  icmp_hdr->icmp_type = ICMP_ECHO;
  icmp_hdr->icmp_code = 0;
  icmp_hdr->icmp_id = getpid();
  icmp_hdr->icmp_seq = 0; 

  strncpy(packet + sizeof(struct icmp), argv[2], PACKET_SIZE - sizeof(struct icmp));

  icmp_hdr->icmp_cksum = checksum(icmp_hdr,PACKET_SIZE);
 
  if (sendto(sockfd, packet, PACKET_SIZE, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
        perror("Sendto error");
        return 1;
    } 

  printf("ICMP packet sent to %s with data: %s\n", argv[1], argv[2]);
  close(sockfd);
  return 0;

}
