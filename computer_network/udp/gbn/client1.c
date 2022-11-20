#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define BUFSIZE 501

typedef struct Packet
{
    int type;
    int seq_no;
    int length;
    char data[BUFSIZE];
} PCK;

typedef struct ACKPacket
{
    int type;
    int ack_no;
} ACK;

void exitByError(char *errorMessage); /* Error handling function */
void CatchAlarm(int ignored);         /* Handler for SIGALRM */
void send_file_data(FILE *fp, int sockfd, struct sockaddr_in addr);
PCK createDataPacket(int seq_no, int length, char *data);
PCK createTerminalPacket(int seq_no, int length);

int main(int argc, char *argv[])
{
    int server_sockfd;
    struct sockaddr_in server_addr;
    char *filename = "free_test_100kb.docx";
    // char *filename = "test.txt";
    FILE *fp = fopen(filename, "rb");
    int debug_key;
    int window_size;

    if (argc != 5) /* Test for correct number of arguments */
    {
        fprintf(stderr, "Usage: %s <Server IP> <Server Port> <Window Size> <Debug Key>\n You gave %d Arguments\n", argv[0], argc);
        exit(1);
    }

    window_size = atoi(argv[3]);
    debug_key = atoi(argv[4]);

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

void send_file_data(FILE *fp, int sockfd, struct sockaddr_in addr)
{
    int n;
    char buffer[BUFSIZE];
    // int segment_num = BUFSIZE / (BUFSIZE - 1);

    // Sending the data
    size_t s;
    while ((s = fread(buffer, sizeof(char), BUFSIZE, fp)) != 0)
    {
        // printf("[SENDING] Data: %s", buffer);
        printf("[Data size] %lu bytes\n", s);

        n = sendto(sockfd, buffer, BUFSIZE, 0, (struct sockaddr *)&addr, sizeof(addr));
        if (n == -1)
        {
            perror("[ERROR] sending data to the server.");
            exit(1);
        }
        bzero(buffer, BUFSIZE);
    }

    strcpy(buffer, "END");
    sendto(sockfd, buffer, BUFSIZE, 0, (struct sockaddr *)&addr, sizeof(addr));

    fclose(fp);
}

void CatchAlarm(int ignored) /* Handler for SIGALRM */
{
    // printf("In Alarm\n");
}

/* If this is called there was an error, Printed and then the process exits */
void exitByError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}

/* Creates and returns a segment Packet */
PCK createDataPacket(int seq_no, int length, char *data)
{

    PCK pkt;

    pkt.type = 1;
    pkt.seq_no = seq_no;
    pkt.length = length;
    memset(pkt.data, 0, sizeof(pkt.data));
    strcpy(pkt.data, data);

    return pkt;
}

/* Creates and returns a terminal segment Packet */
PCK createTerminalPacket(int seq_no, int length)
{

    PCK pkt;

    pkt.type = 4;
    pkt.seq_no = seq_no;
    pkt.length = 0;
    memset(pkt.data, 0, sizeof(pkt.data));

    return pkt;
}
