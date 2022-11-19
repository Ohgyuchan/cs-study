#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#define BUFSIZE 500
#define TIMEOUT_SECS 5

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

void exitByError(char *errorMessage, int debug_key); /* Error handling function */
void CatchAlarm(int ignored);                        /* Handler for SIGALRM */
void send_file_data(int sock, struct sockaddr_in server_addr, struct sockaddr_in client_addr, int debug_key, int window_size);
PCK createDataPacket(int seq_no, int length, char *data);
PCK createTerminalPacket(int seq_no, int length);

int main(int argc, char *argv[])
{
    int server_sock;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int debug_key;
    int window_size;
    struct sigaction myAction;

    if (argc != 5)
    {
        fprintf(stderr, "Usage: %s <Server IP> <Server Port> <Window Size> <Debug Key>\n You gave %d Arguments\n", argv[0], argc);
        exit(1);
    }

    window_size = atoi(argv[3]);
    debug_key = atoi(argv[4]);

    // Creating a UDP socket
    if ((server_sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        exitByError("[ERROR] socket error", debug_key);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    // Sending the file data to the server
    send_file_data(server_sock, server_addr, client_addr, debug_key, window_size);

    printf("[SUCCESS] Data transfer complete.\n");
    printf("[CLOSING] Disconnecting from the server.\n");

    close(server_sock);

    return 0;
}

void send_file_data(int sock, struct sockaddr_in server_addr, struct sockaddr_in client_addr, int debug_key, int window_size)
{
    int n;
    int chunk_size = BUFSIZE - 1;
    char buffer[BUFSIZE - 1];
    int base = -1;
    // char *filename = "free_test_100kb.docx";
    char *filename = "test.txt";
    FILE *fp = fopen(filename, "r");
    // Reading the text file
    if (fp == NULL)
    {
        exitByError("[ERROR] reading the file", debug_key);
    }

    fseek(fp, 0L, SEEK_END);
    int total_data_size = ftell(fp);
    int segment_num = total_data_size / chunk_size;
    if (total_data_size % chunk_size > 0)
    {
        segment_num++;
    }
    fseek(fp, 0L, SEEK_SET);
    // while (fread(buffer, sizeof(char), chunk_size, fp) != 0)
    // {
    //     printf("%s", buffer);
    // }

    printf("tds: %d sn: %d\n", total_data_size, segment_num);
    int seq_num = 0;
    int data_len = 0;
    struct sigaction action;

    action.sa_handler = CatchAlarm;
    if (sigemptyset(&action.sa_mask) < 0)
        exitByError("sigemptyset() failed", debug_key);

    action.sa_flags = 0;

    if (sigaction(SIGALRM, &action, 0) < 0)
        exitByError("sigaction() failed for SIGALRM", debug_key);

    int no_tier_down_ack = 1;
    int tries = 0;
    size_t s;

    while (no_tier_down_ack)
    {
        while (seq_num <= segment_num && (seq_num - base) <= window_size)
        {
            PCK pck;
            fseek(fp, chunk_size * seq_num, SEEK_SET);

            if (1 && seq_num == segment_num)
            {
                /* Reached end, create terminal packet */
                pck = createTerminalPacket(seq_num, 0);
                printf("Sending Terminal Packet\n");
            }
            else
            {
                /* Create Data Packet Struct */
                char seg_data[chunk_size];
                if (seq_num == 0)
                    strncpy(seg_data, (filename), chunk_size);
                else
                {
                    if (fread(buffer, sizeof(char), chunk_size, fp) == 0)
                        exitByError("fread() error\n", debug_key);
                    strncpy(seg_data, (buffer), chunk_size);
                }

                pck = createDataPacket(seq_num, data_len, seg_data);
                printf("Sending Packet: %d, %s\n", seq_num, pck.data);
                // printf("Chunk: %s\n", seg_data);
            }

            if (sendto(sock, &pck, sizeof(pck), 0,
                       (struct sockaddr *)&server_addr, sizeof(server_addr)) != sizeof(pck))
            {
                exitByError("sendto() sent a different number of bytes than expected", debug_key);
            }

            seq_num++;
        }

        alarm(TIMEOUT_SECS);

        printf("Window full: waiting for ACKS\n");

        ACK ack;
        int resp_len;
        socklen_t client_addr_size;

        while ((resp_len = recvfrom(sock, &ack, sizeof(ack), 0,
                                    (struct sockaddr *)&client_addr, &client_addr_size)) < 0)
        {
            if (errno == EINTR)
            {
                seq_num = base + 1;
                fseek(fp, chunk_size * seq_num, SEEK_SET);

                printf("Timeout: Resending\n");
                if (tries >= 10)
                {
                    printf("Tries exceeded: Closing\n");
                    exit(1);
                }
                else
                {
                    alarm(0);

                    while (seq_num <= segment_num && (seq_num - base) <= window_size)
                    {
                        PCK pck;

                        if (seq_num == segment_num && 1)
                        {
                            /* Reached end, create terminal packet */
                            pck = createTerminalPacket(seq_num, 0);
                            printf("Sending Terminal Packet\n");
                        }
                        else
                        {
                            /* Create Data Packet Struct */
                            char seg_data[chunk_size];
                            if (seq_num == 0)
                                strncpy(seg_data, (filename), chunk_size);
                            else
                            {
                                if (fread(buffer, sizeof(char), chunk_size, fp) == 0)
                                    exitByError("fread() error\n", debug_key);
                                strncpy(seg_data, (buffer), chunk_size);
                            }

                            pck = createDataPacket(seq_num, data_len, seg_data);
                            printf("Sending Packet: %d, %s\n", seq_num, pck.data);
                            // printf("Chunk: %s\n", seg_data);
                        }

                        /* Send the constructed data packet to the receiver */
                        if (sendto(sock, &pck, sizeof(pck), 0,
                                   (struct sockaddr *)&server_addr, sizeof(server_addr)) != sizeof(pck))
                            exitByError("sendto() sent a different number of bytes than expected", debug_key);
                        seq_num++;
                    }
                    alarm(TIMEOUT_SECS);
                }
                tries++;
                printf("seq: %d, seg: %d, feof(): %d\n", seq_num, segment_num, feof(fp));
            }
            else
            {
                exitByError("recvfrom() failed", debug_key);
            }
        }
        if (ack.type != 8)
        {
            printf("----------------------- Received ACK: %d\n", ack.ack_no);
            if (ack.ack_no > base)
            {
                /* Advances the sending, reset tries */
                base = ack.ack_no;
            }
        }
        else
        {
            printf("Received Terminal ACK\n");
            no_tier_down_ack = 0;
        }

        /* recvfrom() got something --  cancel the timeout, reset tries */
        alarm(0);
        tries = 0;
    }

    // strcpy(buffer, "END");
    // sendto(sock, buffer, BUFSIZE, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

    fclose(fp);
}

void CatchAlarm(int ignored) /* Handler for SIGALRM */
{
    // printf("In Alarm\n");
}

/* If this is called there was an error, Printed and then the process exits */
void exitByError(char *errorMessage, int debug_key)
{
    if (debug_key)
        perror(errorMessage);
    else
        perror("Error Occurred!");
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