#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SIZE 125

void write_file(int sockfd, struct sockaddr_in addr)
{

    char *filename = "server.docx";
    int n;
    char buffer[SIZE];
    socklen_t addr_size;

    // Creating a file.
    FILE *fp = fopen(filename, "wb");

    // Receiving the data and writing it into the file.
    while (1)
    {
        addr_size = sizeof(addr);
        n = recvfrom(sockfd, buffer, SIZE, 0, (struct sockaddr *)&addr, &addr_size);

        if (strcmp(buffer, "END") == 0)
        {
            break;
        }

        printf("[RECEVING] Data: %s", buffer);
        fwrite(buffer, sizeof(char), SIZE, fp);
        bzero(buffer, SIZE);
    }

    fclose(fp);
}

int main(int argc, char *argv[])
{
    int server_sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[SIZE];
    int e;

    server_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_sockfd < 0)
    {
        perror("[ERROR] socket error");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));

    e = bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (e < 0)
    {
        perror("[ERROR] bind error");
        exit(1);
    }

    printf("[STARTING] UDP File Server started. \n");
    write_file(server_sockfd, client_addr);

    printf("[SUCCESS] Data transfer complete.\n");
    printf("[CLOSING] Closing the server.\n");

    close(server_sockfd);

    return 0;
}