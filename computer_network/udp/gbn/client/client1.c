#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define SIZE 125

void send_file_data(FILE *fp, int sockfd, struct sockaddr_in addr)
{
    int n;
    char buffer[SIZE];

    // Sending the data
    size_t s;
    while ((s = fread(buffer, sizeof(char), SIZE, fp)) != 0)
    {
        printf("[SENDING] Data: %s", buffer);
        printf("[Data size] %lu bytes", s);

        n = sendto(sockfd, buffer, SIZE, 0, (struct sockaddr *)&addr, sizeof(addr));
        if (n == -1)
        {
            perror("[ERROR] sending data to the server.");
            exit(1);
        }
        bzero(buffer, SIZE);
    }

    // Sending the 'END'
    strcpy(buffer, "END");
    sendto(sockfd, buffer, SIZE, 0, (struct sockaddr *)&addr, sizeof(addr));

    fclose(fp);
}

int main(int argc, char *argv[])
{

    // Defining variables
    int server_sockfd;
    struct sockaddr_in server_addr;
    char *filename = "free_test_100kb.docx";
    FILE *fp = fopen(filename, "rb");

    // Creating a UDP socket
    server_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_sockfd < 0)
    {
        perror("[ERROR] socket error");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    // Reading the text file
    if (fp == NULL)
    {
        perror("[ERROR] reading the file");
        exit(1);
    }

    // Sending the file data to the server
    send_file_data(fp, server_sockfd, server_addr);

    printf("[SUCCESS] Data transfer complete.\n");
    printf("[CLOSING] Disconnecting from the server.\n");

    close(server_sockfd);

    return 0;
}