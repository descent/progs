// unix domain socket server
#include <sys/types.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <unistd.h>
#include <string.h>

#include "common.h"

int main(int argc, char *argv[])
{
  int sockfd = socket(PF_LOCAL, SOCK_DGRAM, 0);

  if (sockfd < 0)
  {
    PF("socket fail!!\n");
    return -1;
  }

  struct sockaddr_un my_addr;

  my_addr.sun_family = AF_UNIX;
  strncpy(my_addr.sun_path, UDS_ADDR, sizeof(my_addr.sun_path) - 1);
  unlink(UDS_ADDR);

  int ret;
  //ret = bind(sockfd, (struct sockaddr*)&my_addr, SUN_LEN(&my_addr));
  ret = bind(sockfd, (struct sockaddr*)&my_addr, sizeof(my_addr));
  if (ret == -1)
  {
    perror("bind()");
    return -1;
  }


  // socklen_t peer_addr_size;


  fd_set fdvar;
  while(1)
  {
    FD_ZERO(&fdvar);
    FD_SET(sockfd, &fdvar);

#if 0
    struct timeval tv;
    tv.tv_sec  = 0;
    tv.tv_usec = 100000;
#endif
    ret = select(sockfd+1, &fdvar, NULL, NULL, NULL);
    if (ret == -1)
    {
      perror("select()");
    }
    else if (ret)
         {
           char buf[MAX_MESG_SIZE];

           struct sockaddr_un client_addr;

           PF("Data is available now.\n");
           socklen_t sz = sizeof(client_addr);
           PF("xx sz: %d\n", sz);
           int read_size = recvfrom(sockfd, buf, MAX_MESG_SIZE, 0, (struct sockaddr*)&client_addr, &sz);
           if (read_size == -1)
           {
             perror("recvfrom");
             continue;
           }
           PF("sz: %d\n", sz);
           PF("client_addr.sun_family: %d\n", client_addr.sun_family);
           PF("client_addr.sun_path: %s\n", client_addr.sun_path);
           PF("read_size: %d\n", read_size);
           buf[read_size] = 0;
           PF("buf: %s\n", buf);
           PF("================\n");
           strcpy(buf, "back message");
           ssize_t send_len = sendto(sockfd, buf, strlen(buf), 0, (sockaddr *)&client_addr, sizeof(client_addr));

         }
         else // 0
         {
           PF("No data\n");
         }
  }

  //unlink(strcpy(my_addr.sun_path, sock_path));



  
  return 0;
}
