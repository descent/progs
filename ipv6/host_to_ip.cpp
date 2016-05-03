//ref: http://lists.freebsd.org/pipermail/freebsd-questions/2012-January/237373.html

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <vector>


namespace DS
{

int getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, std::vector<struct addrinfo> &res_vec)
{
  struct addrinfo *res, *p;
  int status;

  if ((status = ::getaddrinfo(node, NULL, hints, &res)) == 0) 
  {
    for(p = res;p != NULL; p = p->ai_next) 
    {
      res_vec.push_back(*p);
    }

    freeaddrinfo(res); // free the linked list
  }
  return status;
}

}

int main(int argc, char *argv[])
{
   struct addrinfo hints, *p;
   int status;
   char ipstr[INET6_ADDRSTRLEN];

   if (argc != 2) {
       fprintf(stderr,"usage: showip hostname\n");
       return 1;
   }

   memset(&hints, 0, sizeof hints);
   hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
   hints.ai_socktype = SOCK_STREAM;

   std::vector<struct addrinfo> res; 
   if ((status = DS::getaddrinfo(argv[1], NULL, &hints, res)) != 0) {
       fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
       return 2;
   }

   printf("IP addresses for %s: %d entry\n\n", argv[1], res.size());

   for(int i=0; i < res.size() ; ++i)
   {
     p = &res[i];
       void *addr;
       const char *ipver;

       // get the pointer to the address itself,
       // different fields in IPv4 and IPv6:
       if (p->ai_family == AF_INET) { // IPv4
           struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
           addr = &(ipv4->sin_addr);/*error*/
           ipver = "IPv4";
       } else { // IPv6
           struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
           addr = &(ipv6->sin6_addr);/*error*/
           ipver = "IPv6";
       }

       // convert the IP to a string and print it:
       inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
       printf("  %s: %s\n", ipver, ipstr);
   }

   return 0;
}
