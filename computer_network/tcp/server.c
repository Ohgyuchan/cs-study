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
    int serv_sock;
    int clnt_sock;
    char message[BUFSIZE];
    int str_len, num = 0;
    char MSG1[] = "ABCDEFGHIJKLNMOPQRST\n123123123123";
    char MSG2[] = "Evening123123123123123123123123123\n12312312312312312";
    char MSG3[] = "Everybody!\n123";
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    unsigned int clnt_addr_size;
    
    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    
    if (serv_sock == -1)
        error_handling("socket error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    
    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error");
    
    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");
    
    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_size);
    
    if (clnt_sock == -1)
        error_handling("accept() error");
    
    sleep(5);
    
    str_len = recv(clnt_sock, message, BUFSIZE - 1, 0);
    

    char temp[4] = "";
    temp[0] = message[0];
    temp[1] = message[1];
    temp[2] = message[2];
    temp[3] = message[3];

    int first = atoi(temp);
    
    temp[0] = message[first + 3];
    temp[1] = message[first + 3 + 1];
    temp[2] = message[first + 3 + 2];
    temp[3] = message[first + 3 + 3];

    int second = atoi(temp);

    char result[BUFSIZE];
    
    for(int i = 4; i < first + 4; i++) {
        result[i - 4] = message[i];
    }
    printf("Message 1: %s", result);
    
    for(int i = first + 4 + 4; i < first + 4 + 4 + second; i++) {
        result[i - (first + 4 + 4)] = message[i];
    }
    printf("Message 2: %s", result);

    for(int i = first + 4 + 4 + second; i < str_len; i++) {
        result[i - (first + 4 + 4 + second)] = message[i];
    }
    printf("Message 3: %s", result);
    
    // write(1, message, str_len);
    // write(clnt_sock, message, str_len);
    
    
    close(clnt_sock);
    close(serv_sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}