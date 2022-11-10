#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include <netinet/tcp.h>

#define BUFSIZE 1024

void error_handling(char *message);
int main(int argc, char **argv)
{
    int sock;
    char message[BUFSIZE];
    int str_len, i;
    unsigned int addr_size;
    char MSG1[] = "ABCDEFGHIJKLNMOPQRST\n123123123123";
    char MSG2[] = "Evening123123123123123123123123123\n12312312312312312";
    char MSG3[] = "Everybody!\n123";
    struct sockaddr_in serv_addr;
    struct sockaddr_in from_addr;
    
    if (argc != 3)
    {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }
    
    sock = socket(PF_INET, SOCK_STREAM, 0);

    if (sock == -1)
        error_handling("UDP socket error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error!");
    
    int len = strlen(MSG1);
    sprintf(message, "%04d", len);
    strcat(message, MSG1);
    write(sock, message, strlen(message));
    printf("send: %s \n", message);
    
    message[0] = '\0';
    len = strlen(MSG2);
    sprintf(message, "%04d", len);
    strcat(message, MSG2);
    write(sock, message, strlen(message));
    printf("send: %s \n", message);
    
    message[0] = '\0';
    len = strlen(MSG3);
    sprintf(message, "%04d", len);
    strcat(message, MSG3);
    write(sock, message, strlen(message));
    printf("send: %s \n", message);
    

    for (i = 0; i < 3; i++)
    {
        addr_size = sizeof(from_addr);
        str_len = recv(sock, message, BUFSIZE - 1, 0);
        message[str_len] ='\0';
        printf("The message %d from the server: %s \n", i+1, message);
    }
    
    close(sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}