#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#define BUFSIZE 500
#define TIMEOUT_SECS 3

typedef struct Packet
{
    int type;
    int seq_no;
    int length;
    char data[501];
} PCK;

typedef struct ACKPacket
{
    int type;
    int ack_no;
} ACK;

void exitByError(char *errorMessage, int debug_key);
void catchAlarm(int ignored);
void send_file_data(int sock, struct sockaddr_in server_addr, struct sockaddr_in client_addr, int debug_key, int window_size);
PCK createDataPacket(int seq_no, int length, char *data);
PCK createTerminalPacket(int seq_no, int length);
void wc_command(int sock, struct sockaddr_in server_addr, struct sockaddr_in client_addr, int debug_key, int window_size);

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

    if (window_size > 10)
    {
        fprintf(stderr, "Usage: <Window Size> must be <= 10. You typed <Window Size>:%s.\n", argv[3]);
    }
    debug_key = atoi(argv[4]);

    if ((server_sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        exitByError("[ERROR] socket error", debug_key);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    send_file_data(server_sock, server_addr, client_addr, debug_key, window_size);
    close(server_sock);
    printf("[SUCCESS] Data transfer complete.\n");
    if ((server_sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        exitByError("[ERROR] socket error", debug_key);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));
    sleep(1);
    wc_command(server_sock, server_addr, client_addr, debug_key, 1);
    close(server_sock);

    return 0;
}

void wc_command(int sock, struct sockaddr_in server_addr, struct sockaddr_in client_addr, int debug_key, int window_size)
{
    char buffer[5][50];
    char *command = "wc free_test_100kb.docx";
    FILE *fp;
    int base = -1;
    int segment_num = 4;
    int i = 0;

    for (i = 0; i < 5; i++)
    {
        fp = popen(command, "r");
        if (NULL == fp)
        {
            exitByError("popen() error", debug_key);
        }
        memset(buffer[i], 0, sizeof(buffer[i]));
        if (fread(buffer[i], 1, sizeof(buffer[i]), fp) == 0)
            exitByError("fread() error\n", debug_key);

        pclose(fp);
    }
    int seq_num = 0;
    struct sigaction action;

    action.sa_handler = catchAlarm;
    if (sigemptyset(&action.sa_mask) < 0)
        exitByError("sigemptyset() failed", debug_key);

    action.sa_flags = 0;

    if (sigaction(SIGALRM, &action, 0) < 0)
        exitByError("sigaction() failed for SIGALRM", debug_key);

    int no_tier_down_ack = 1;
    int tries = 0;

    while (no_tier_down_ack)
    {
        while (seq_num <= segment_num && (seq_num - base) <= window_size)
        {
            PCK pck;

            if (seq_num == segment_num)
            {
                pck = createTerminalPacket(seq_num, 0);
                printf("Sending Terminal Packet\n");
            }
            else
            {
                pck = createDataPacket(seq_num, sizeof(buffer), buffer[seq_num]);
                printf("Sending Packet: %d\n", seq_num);
                if (debug_key)
                    printf("Chunk Length: %lu\n", sizeof(buffer));
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

                printf("Timeout: Resending\n");
                if (tries >= 10)
                {
                    printf("Tries exceeded: Closing\n");
                    exit(1);
                }
                else
                {
                    alarm(0);
                    while (seq_num <= segment_num && (seq_num - base) <= 1)
                    {
                        PCK pck;
                        if (seq_num == segment_num)
                        {
                            pck = createTerminalPacket(seq_num, 0);
                            printf("Sending Terminal Packet\n");
                        }
                        else
                        {
                            pck = createDataPacket(seq_num, sizeof(buffer[i]), buffer[seq_num]);
                            printf("Sending Packet: %d\n", seq_num);
                            if (debug_key)
                                printf("Chunk: %s\n", buffer[seq_num]);
                        }
                        if (sendto(sock, &pck, sizeof(pck), 0,
                                   (struct sockaddr *)&server_addr, sizeof(server_addr)) != sizeof(pck))
                            exitByError("sendto() sent a different number of bytes than expected", debug_key);
                        seq_num++;
                    }
                    alarm(TIMEOUT_SECS - 1);
                }
                tries++;
                if (debug_key)
                {
                    printf("seq: %d, seg: %d\n", seq_num, segment_num);
                }
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
                base = ack.ack_no;
            }
        }
        else
        {
            printf("Received Terminal ACK\n");
            no_tier_down_ack = 0;
        }
        alarm(0);
        tries = 0;
    }
}

void send_file_data(int sock, struct sockaddr_in server_addr, struct sockaddr_in client_addr, int debug_key, int window_size)
{
    int n;
    char buffer[BUFSIZE];
    int base = -1;
    char *filename = "free_test_100kb.docx";
    // char *filename = "test.txt";
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        exitByError("[ERROR] reading the file", debug_key);
    }

    fseek(fp, 0L, SEEK_END);
    int total_data_size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    int segment_num = (total_data_size / BUFSIZE);
    if (total_data_size % BUFSIZE > 0)
    {
        segment_num += 2;
    }
    else
    {
        segment_num += 1;
    }

    if (debug_key)
    {
        printf("total_data_size: %d segment_num: %d\n", total_data_size, segment_num);
    }
    int seq_num = 0;
    int data_len = 0;
    struct sigaction action;

    action.sa_handler = catchAlarm;
    if (sigemptyset(&action.sa_mask) < 0)
        exitByError("sigemptyset() failed", debug_key);

    action.sa_flags = 0;

    if (sigaction(SIGALRM, &action, 0) < 0)
        exitByError("sigaction() failed for SIGALRM", debug_key);

    int no_tier_down_ack = 1;
    int tries = 0;

    while (no_tier_down_ack)
    {
        while (seq_num <= segment_num && (seq_num - base) <= window_size)
        {
            PCK pck;

            if (seq_num == segment_num)
            {
                pck = createTerminalPacket(seq_num, 0);
                printf("Sending Terminal Packet\n");
            }
            else
            {
                char seg_data[BUFSIZE];
                if (seq_num == 0)
                {
                    strncpy(seg_data, (filename), BUFSIZE);
                    data_len = strlen(seg_data);
                }
                else
                {
                    memset(buffer, 0, BUFSIZE);
                    if ((data_len = fread(buffer, 1, sizeof(buffer), fp)) == 0)
                        exitByError("fread() error\n", debug_key);
                    strncpy(seg_data, (buffer), BUFSIZE);
                }

                pck = createDataPacket(seq_num, data_len, seg_data);
                printf("Sending Packet: %d\n", seq_num);
                if (debug_key)
                    printf("Chunk Length: %d\n", data_len);
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
                fseek(fp, (base)*BUFSIZE, SEEK_SET);

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

                        if (seq_num == segment_num)
                        {
                            pck = createTerminalPacket(seq_num, 0);
                            printf("Sending Terminal Packet\n");
                        }
                        else
                        {
                            char seg_data[BUFSIZE];
                            if (seq_num == 0)
                            {
                                strncpy(seg_data, (filename), BUFSIZE);
                                data_len = strlen(seg_data);
                            }
                            else
                            {
                                memset(buffer, 0, BUFSIZE);
                                if ((data_len = fread(buffer, 1, sizeof(buffer), fp)) == 0)
                                    exitByError("fread() error\n", debug_key);
                                strncpy(seg_data, (buffer), BUFSIZE);
                            }
                            pck = createDataPacket(seq_num, data_len, seg_data);
                            printf("Sending Packet: %d\n", seq_num);
                            if (debug_key)
                                printf("Chunk: %s\n", seg_data);
                        }
                        if (sendto(sock, &pck, sizeof(pck), 0,
                                   (struct sockaddr *)&server_addr, sizeof(server_addr)) != sizeof(pck))
                            exitByError("sendto() sent a different number of bytes than expected", debug_key);
                        seq_num++;
                    }
                    alarm(TIMEOUT_SECS);
                }
                tries++;
                if (debug_key)
                {
                    printf("seq: %d, seg: %d, feof(): %d\n", seq_num, segment_num, feof(fp));
                }
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
                base = ack.ack_no;
            }
        }
        else
        {
            printf("Received Terminal ACK\n");
            memset(buffer, 0, BUFSIZE);
            no_tier_down_ack = 0;
        }
        alarm(0);
        tries = 0;
    }
    fclose(fp);
}

void catchAlarm(int ignored)
{
    // printf("In Alarm\n");
}

void exitByError(char *errorMessage, int debug_key)
{
    if (debug_key)
        perror(errorMessage);
    else
        perror("Error Occurred!");
    exit(1);
}

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

PCK createTerminalPacket(int seq_no, int length)
{

    PCK pkt;

    pkt.type = 4;
    pkt.seq_no = seq_no;
    pkt.length = 0;
    memset(pkt.data, 0, sizeof(pkt.data));

    return pkt;
}