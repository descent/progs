// unix domain socket client
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "common.h"

int main(int argc, char *argv[])
{
connect_:
  int sockfd = socket(PF_LOCAL, SOCK_STREAM, 0);

  if (sockfd < 0)
  {
    PF("socket fail!!\n");
    return -1;
  }

  struct sockaddr_un my_addr, server_addr;
  char my_path[]="/tmp/cli-XXXXXX";
  //char *my_path;

  mktemp(my_path);
  PF("my_path: %s\n", my_path);
  //return 0;

  my_addr.sun_family = AF_UNIX;
  strncpy(my_addr.sun_path, my_path, sizeof(my_addr.sun_path) - 1);
  PF("my_addr.sun_path: %s\n", my_addr.sun_path);

  server_addr.sun_family = AF_UNIX;
  strncpy(server_addr.sun_path, UDS_ADDR, sizeof(server_addr.sun_path) - 1);
  
  //socklen_t addr_len = sizeof(my_addr);
  int ret = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

  if (ret == -1)
  {
    perror("connect()");
    return -1;
  }


#if 0
  bind(sockfd, (struct sockaddr*)&my_addr, sizeof(my_addr));

  if (ret == -1)
  {
    perror("bind()");
    return -1;
  }
#endif


  //ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
  char buf[MAX_MESG_SIZE]="abc test";

  if (argc > 1)
    strncpy(buf, argv[1], 99);


  ssize_t send_len = send(sockfd, buf, strlen(buf), 0);
  if (send_len == -1)
  {
    perror("send");
  }

  PF("send_len: %d\n", send_len);
  
  socklen_t sz=100;

  int read_size = recv(sockfd, buf, MAX_MESG_SIZE, 0);
  PF("read_size: %d\n", read_size);
  PF("buf: %s\n", buf);

#if 0
  read_size = recv(sockfd, buf, MAX_MESG_SIZE, 0);
  PF("read_size: %d\n", read_size);
  if (read_size == 0)
  {
    close(sockfd);
    goto connect_;
  }
#endif
  unlink(my_path);

  return 0;
}
