#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>


int main(int argc, char *argv[])
{
  int sockfd;
  struct sockaddr_in dest;
  char buffer[20] = "Hi client! ";
  char buffer1[10];


  /* create sockett */
  sockfd = socket(PF_INET, SOCK_STREAM, 0);


  #if 1
  int f_flag = fcntl(sockfd, F_GETFD);
  f_flag |= FD_CLOEXEC;
  fcntl(sockfd, F_SETFD, f_flag);
  #endif

  system("./keep_port&");


  /* initialize structure dest */
  memset(&dest, 0, sizeof(dest));
  dest.sin_family = AF_INET;
  dest.sin_port = htons(8889);
  /* this line is different from client */
  dest.sin_addr.s_addr = INADDR_ANY;

  /* Assign a port number to socket */
  bind(sockfd, (struct sockaddr*)&dest, sizeof(dest));

  /* make it listen to socket with max 20 connections */
  listen(sockfd, 20);


  /* infinity loop -- accepting connection from client forever */
  while(1)
  {
    int clientfd;
    struct sockaddr_in client_addr;
    socklen_t addrlen = sizeof(client_addr);

    printf("wait for connect\n");
    /* Wait and Accept connection */
    clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);

    /* Send message */
    send(clientfd, buffer, sizeof(buffer), 0);
    int res=recv(clientfd, buffer1, sizeof(buffer1), 0);
    printf("receive from client: %s, %d bytes\n", buffer1,res);
    //write(fd, buffer1, sizeof(buffer1));
    /* close(client) */
    close(clientfd);
  }

  /* close(server) , but never get here because of the loop */
  close(sockfd);
  return 0;

}
