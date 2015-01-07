// unix domain socket client
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/un.h>
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

  socklen_t addr_len = sizeof(my_addr);

  //ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
  char buf[100]="abc test";
  ssize_t send_len = sendto(sockfd, buf, strlen(buf), 0, (sockaddr *)&my_addr, addr_len);
  if (send_len == -1)
  {
    perror("sendto");
  }

  PF("send_len: %d\n", send_len);
  
  return 0;
}
