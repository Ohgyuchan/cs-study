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


void error_handling(char *message);

int main(int argc, char **argv)
{
    int a, serv_sock, newsock, n;
    char str[25], str2[25];
    struct sockaddr_in serv_addr;
    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <Port number>\n You gave %d Arguments\n", argv[0], argc);
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if ((serv_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        error_handling("\n socket");
    }
    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        error_handling("\nBIND");
    }
    if (listen(serv_sock, 1) < 0)
    {
        error_handling("\n LISTEN");
    }
    if ((newsock = accept(serv_sock, (struct sockaddr *)&client_addr, &client_addr_size)) < 0)
    {
        error_handling("\n ACCEPT");
    }
    else
        printf("\n now connected to %s\n", inet_ntoa(client_addr.sin_addr));
    read(newsock, str, sizeof(str));
    do
    {
        printf("\n client msg:%s", str);
        printf("\n server msg:");
        scanf("%s", str2);
        write(newsock, str2, sizeof(str2));
        listen(newsock, 1);
        read(newsock, str, sizeof(str));
        n = strcmp(str, "BYE");
        a = strcmp(str2, "BYE");
    } while (n != 0 || a != 0);
    close(newsock);
    close(serv_sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}