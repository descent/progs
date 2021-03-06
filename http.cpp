#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PACKET_SIZE 2048
//void lee_send(int fd,char *sendmem,int sendmemsz)
int main(void)
{
        struct sockaddr_in peer;
        int s ;                                                                                 //socket description
        int rc;
        char buf[PACKET_SIZE]={0};
        char request[PACKET_SIZE] = {0};
        int recive=1,remain;

        peer.sin_family = AF_INET;                                              //
        peer.sin_port = htons(80);                                      //setup connect port
        peer.sin_addr.s_addr = inet_addr("192.168.20.8");    //      ******

        s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);                  //get a socket,type is SOCK_STREAM
        if ( s < 0 )
        {
                perror("socket call failed");
                exit(1);
        }
        //printf("連結中...\n");
        rc = connect(s, (struct sockaddr *) &peer, sizeof(peer));
        if ( rc )
        {
                perror("connect call failed");
                exit(1);
        }
        //printf("已建立連線....\n");

        strcpy(request,"GET /~descent/play.mp4 HTTP/1.1\r\n");  
        //strcpy(request,"GET /~descent/n1.txt HTTP/1.0\r\n");     
        strcat(request,"USER-AGENT: myhttpclient\r\n");
        strcat(request,"ACCEPT: */*\r\n");
        strcat(request,"HOST: 192.168.20.8\r\n");
        //strcat(request,"user-Agent: Mozilla/5.0 (Window NT 6.1; rv:19.0) Gecko/20100101 Firefox/19.0\r\n");
        //strcat(request,"Accept: text/html,application/xhtml+xml.application/xml;q=0.9,*/*;q=0.8\r\n");
        //strcat(request,"Accept-Language: zh-tw,zh;q=0.8,en-us;q=0.5,en;q=0.3\r\n");
        //strcat(request,"Accept-Encoding: gzip, deflate\r\n");
        //strcat(request,"Connection: keep-alive\r\n");
        //strcat(request,"Content-Type: ...\r\n");
        strcat(request,"\r\n");

        //printf("%s",request);

        if(!send(s,request,strlen(request),0))
        {
                printf("send fail");
                exit(1);
        }
        else
        {
                printf("send request\n");
        }
        ssize_t recv_len = recv(s,buf,PACKET_SIZE,0);                                              /******worked*******/
        printf("recv_len : %zu\n", recv_len);
        char *p  ,*q;
        //q=strstr(buf,"video/mp4");
        q=strstr(buf,"\r\n\r\n");
        ssize_t idx;
        if (q)
        {
          idx = q-&buf[0];
          printf("idx: %zu\n", idx);
          remain = recv_len - (idx+4);
          printf("remain: %d\n", remain);
        }
        //printf("buf : %s",buf);

        int i,filesize,first=1;
        char *save;
        FILE * fd;
        if((fd=fopen("d.mp4","w"))==NULL)
        {
                perror("open file fail.");
                exit(1);
        }
        else
                printf("\ncreat recive file.\n");

        ssize_t w_len = fwrite(buf+idx+4, 1, remain, fd);
        printf("w_len: %zu\n", w_len);
#if 0
        p=strstr(buf,"Content-Length: ");
        q=strstr(buf,"Content-Type: ");
        p+=strlen("Content-Length: ");

        for( i = 0;*(p+i)!='\n'&&*(p+i)!='\r';++i);
        *(p+i)='\0';

        filesize = atoi(p);
        printf("1.file size is %d\n",filesize);
        int total_rec;
        q=strstr(q,"\r\n");
        q+=strlen("\r\n");
        q=strstr(q,"\r\n");
        q+=strlen("\r\n");
        total_rec = strlen(q);
        printf("buf %zu, q %zu\n",strlen(buf),strlen(q));
        filesize-=strlen(q);


        fwrite(q,1,strlen(q),fd);


        save = (char*)malloc(strlen(q));
        int j=0;
#endif
        //filesize>0&&(recive=recv(s,buf,PACKET_SIZE,0))>0)

        ssize_t total_len=0;
        while(1)
        {
          recv_len = recv(s,buf,PACKET_SIZE,0);

          //printf("recv_len: %zu\n", recv_len);
          total_len += recv_len;
          if (recv_len == 0)
            break;
          else
            fwrite(buf,1,recv_len,fd);

#if 0
                total_rec+=recive;

                fwrite(buf,1,recive,fd);
                //printf("recive %d",recive);
                filesize-=recive;
                //printf("\tremine %d\n",filesize);
                if(filesize<=0)
                        break;
                memset(buf,0,PACKET_SIZE);                                     
#endif
        }
        printf("total_len: %zu\n", total_len);
        //printf("save size is %d\n",total_rec);
        printf("recv size is %d\n",recive);
        printf("2.file size is %d\n",filesize);
        fclose(fd);
        //free(save);
        close(s);
        return 0;
}
