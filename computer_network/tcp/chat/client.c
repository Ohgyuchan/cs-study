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
    int a, client_sock;
    char str[20], str2[20];
    char *nickname;
    struct sockaddr_in client_addr;

    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <Server IP> <Server Port> <Nickname>\n You gave %d Arguments\n", argv[0], argc);
        exit(1);
    }
    
    client_addr.sin_port = htons(atoi(argv[2]));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr(argv[1]);
    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    
    nickname = argv[3];

    if (client_sock < 0)
    {
        error_handling("\n SOCKET");
    }
    if (connect(client_sock, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0)
    {
        error_handling("\n CONNECT");
    }
    printf("\nclient connected to %s", argv[1]);
    printf("\nCLIENT");
    scanf("%s", str);
    if (write(client_sock, str, sizeof(str)) < 0)
    {
        printf("\n data could not be sent");
    }
    do
    {
        listen(client_sock, 1);
        read(client_sock, str2, sizeof(str2));
        printf("\nserver msg:%s", str2);
        printf("\nclient msg:");
        scanf("%s", str);
        a = strcmp(str2, "BYE");
        write(client_sock, str2, sizeof(str2));
    } while (a != 0);
    close(client_sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}