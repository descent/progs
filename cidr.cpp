#include <stdio.h>
#include <stdint.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
  struct in_addr ip, mask, network_ip;

#if 0
  inet_aton("192.168.6.60", &ip);
  inet_aton("255.255.255.252", &mask);
#endif

#if 0
  inet_aton("192.168.6.60", &ip);
  inet_aton("255.255.255.0", &mask);
#endif

#if 1
  inet_aton("192.168.6.70", &ip);
  inet_aton("255.255.255.192", &mask);
#endif

  printf("ip (%x): %s\n", ntohl(ip.s_addr), inet_ntoa(ip));
  printf("mask (%x): %s\n", ntohl(mask.s_addr), inet_ntoa(mask));

  uint32_t host = 0xffffffff ^ ntohl(mask.s_addr); // mask is network order, host is host order


  uint32_t network = ntohl(ip.s_addr & mask.s_addr); // host order
  printf("host: %d\n", host);

  network_ip.s_addr = htonl(network);
  printf("network: %x\n", network);
  printf("network_ip: %s\n", inet_ntoa(network_ip));

  uint32_t host_begin = network+1;
  uint32_t host_end = host-1;

  uint32_t valid_ip_val_begin = network | host_begin;
  uint32_t valid_ip_val_end = network | host_end;

  struct in_addr valid_ip_begin, valid_ip_end;
  valid_ip_begin.s_addr = htonl(valid_ip_val_begin);
  valid_ip_end.s_addr = htonl(valid_ip_val_end);

  printf("valid_ip_begin: %s\n", inet_ntoa(valid_ip_begin));
  printf("valid_ip_end: %s\n", inet_ntoa(valid_ip_end));
  printf("valid_ip_end_val: %x\n", valid_ip_val_end);

  return 0;
}
