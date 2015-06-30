// from man getaddrinfo, domain name to IP
// ref: http://beej-zhtw.netdpi.net/05-system-call-or-bust/5-1-getaddrinfo-start

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <vector>

using namespace std;

#define BUF_SIZE 500

int getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, vector<addrinfo> &res)
{
  struct addrinfo *result, *rp;
  int s = getaddrinfo("www.google.com", 0, hints, &result);

  for (rp = result; rp != NULL; rp = rp->ai_next) 
  {
    res.push_back(*rp);
  }
  return s;
}

int main(int argc, char *argv[])
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s;
    struct sockaddr_storage peer_addr;
    socklen_t peer_addr_len;
    ssize_t nread;
    char buf[BUF_SIZE];
    const char *dm="www.google.com";

    printf("domain name: %s\n", dm);

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */

    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

#if 0
    s = getaddrinfo(dm, NULL, &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
  for (rp = result; rp != NULL; rp = rp->ai_next) 
  {
    char ipstr[INET6_ADDRSTRLEN];
    void *addr;
    const char *ipver;

    // 取得本身位址的指標，
    // 在 IPv4 與 IPv6 中的欄位不同：
    if (rp->ai_family == AF_INET) 
    { // IPv4
      struct sockaddr_in *ipv4 = (struct sockaddr_in *)rp->ai_addr;
      addr = &(ipv4->sin_addr);
      ipver = "IPv4";
    } 
    else 
    { // IPv6
      struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)rp->ai_addr;
      addr = &(ipv6->sin6_addr);
      ipver = "IPv6";
    }

    // convert the IP to a string and print it:
    inet_ntop(rp->ai_family, addr, ipstr, sizeof ipstr);
    printf(" %s: %s\n", ipver, ipstr);
  }

  freeaddrinfo(result);           /* No longer needed */
#endif

  vector<addrinfo> res;
  s = getaddrinfo(dm, NULL, &hints, res);
  if (s != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
    exit(EXIT_FAILURE);
  }

  for (int i=0 ; i < res.size() ; ++i)
  {
    char ipstr[INET6_ADDRSTRLEN];
    void *addr;
    const char *ipver;

    // 取得本身位址的指標，
    // 在 IPv4 與 IPv6 中的欄位不同：
    if (res[i].ai_family == AF_INET) 
    { // IPv4
      struct sockaddr_in *ipv4 = (struct sockaddr_in *)res[i].ai_addr;
      addr = &(ipv4->sin_addr);
      ipver = "IPv4";
    } 
    else 
    { // IPv6
      struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)res[i].ai_addr;
      addr = &(ipv6->sin6_addr);
      ipver = "IPv6";
    }

    // convert the IP to a string and print it:
    inet_ntop(res[i].ai_family, addr, ipstr, sizeof ipstr);
    printf(" %s: %s\n", ipver, ipstr);
  }
  return 0;
}
