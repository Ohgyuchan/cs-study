#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFSIZE 500

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

void exitByError(char *errorMessage, int debug_key);
struct ACKPacket createACKPacket(int ack_type, int base); /* Creates a ACK packet to be sent */
int is_lost(float loss_rate);                             /* Given function for lose rate */

void write_file(int sock, struct sockaddr_in addr, int debug_key);

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFSIZE];
    int port_num, debug_key;

    if (argc < 3)
    {
        fprintf(stderr, "Usage:  %s <PORT NUMBER> <DEBUG KEY(0: OFF / 1: ON)>\n You gave %d Arguments\n", argv[0], argc);
        exit(1);
    }

    debug_key = atoi(argv[2]);
    port_num = atoi(argv[1]);

    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        exitByError("[ERROR] socket error", debug_key);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port_num);

    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        exitByError("[ERROR] bind error", debug_key);

    printf("[STARTING] UDP File Server started. \n");
    write_file(sock, client_addr, debug_key);

    printf("[SUCCESS] Data transfer complete.\n");
    printf("[CLOSING] Closing the server.\n");

    close(sock);

    return 0;
}

void write_file(int sock, struct sockaddr_in client_addr, int debug_key)
{
    FILE *fp;
    int recv_size;
    char buffer[BUFSIZE];
    int base = -2;
    int seq_num = 0;
    double loss_rate = 0.4;
    socklen_t client_addr_size;

    // fp = fopen("server.txt", "w");
    // Receiving the data and writing it into the file.
    while (1)
    {
        client_addr_size = sizeof(client_addr);
        PCK pck;
        ACK ack;

        if ((recv_size = recvfrom(sock, &pck, sizeof(pck), 0, (struct sockaddr *)&client_addr, &client_addr_size)) < 0)
            exitByError("recvfrom() failed", debug_key);

        // if (strcmp(buffer, "END") == 0)
        //     break;

        seq_num = pck.seq_no;

        // printf("[RECEVING] Data: %s", buffer);
        // if (debug_key)
        //     printf("[RECEIVING] Data size: %d bytes\n", recv_size);
        // fwrite(buffer, sizeof(char), BUFSIZE, fp);
        // bzero(buffer, BUFSIZE);

        if (!is_lost(loss_rate))
        {

            // if (strcmp(buffer, "END") == 0)
            //     break;

            // printf("[RECEVING] Data: %s", buffer);
            // if (debug_key)
            //     printf("[RECEIVING] Data size: %d bytes\n", recv_size);

            /* If seq is zero start new data collection */
            if (pck.seq_no == 0 && pck.type == 1)
            {
                printf("Received Initial Packet from %s\n", inet_ntoa(client_addr.sin_addr));
                memset(buffer, 0, BUFSIZE);
                strcpy(buffer, pck.data);
                printf("%s\n", buffer);
                fp = fopen(buffer, "wb");
                // fwrite(buffer, sizeof(char), BUFSIZE, fp);
                base = 0;
                ack = createACKPacket(2, base);
            }
            /* if base+1 then its a subsequent in order packet */
            else if (pck.seq_no == base + 1)
            {
                /* then concatenate the data sent to the recieving buffer */
                printf("Received Subsequent Packet #%d\n", pck.seq_no);
                strcpy(buffer, pck.data);
                fwrite(buffer, sizeof(char), BUFSIZE, fp);
                base = pck.seq_no;
                ack = createACKPacket(2, base);
            }
            else if (pck.type == 1 && pck.seq_no != base + 1)
            {
                /* if received out of sync packet, send ACK with old base */
                printf("Received Out of Sync Packet #%d\n", pck.seq_no);
                /* Resend ACK with old base */
                ack = createACKPacket(2, base);
            }

            /* type 4 means that the packet received is a termination packet */
            if (pck.type == 4 && seq_num == base)
            {
                base = -1;
                /* create an ACK packet with terminal type 8 */
                ack = createACKPacket(8, base);
            }

            /* Send ACK for Packet Received */
            if (base >= 0)
            {
                printf("------------------------------------  Sending ACK #%d\n", base);
                if (sendto(sock, &ack, sizeof(ack), 0,
                           (struct sockaddr *)&client_addr, sizeof(client_addr)) != sizeof(ack))
                    exitByError("sendto() sent a different number of bytes than expected", debug_key);
            }
            else if (base == -1)
            {
                if (debug_key)
                {
                    printf("Received Tier down Packet\n");
                    // printf("Sending Terminal ACK\n", base);
                    printf("Sending Terminal ACK\n");
                }
                if (sendto(sock, &ack, sizeof(ack), 0,
                           (struct sockaddr *)&client_addr, sizeof(client_addr)) != sizeof(ack))
                    exitByError("sendto() sent a different number of bytes than expected", debug_key);
            }

            /* if data packet is terminal packet, display and clear the recieved message */
            if (pck.type == 4 && base == -1)
            {
                printf("\n MESSAGE RECIEVED\n %s\n\n", buffer);
                memset(buffer, 0, BUFSIZE);
                break;
            }
        }
        else
        {
            if (debug_key)
                printf("PACKET LOSS\n");
        }
    }

    fclose(fp);
}

void exitByError(char *errorMessage, int debug_key)
{
    if (debug_key)
        perror(errorMessage);
    else
        perror("Error Occurred!");
    exit(1);
}

struct ACKPacket createACKPacket(int ack_type, int base)
{
    struct ACKPacket ack;
    ack.type = ack_type;
    ack.ack_no = base;
    return ack;
}

int is_lost(float loss_rate)
{
    double rv;
    rv = drand48();
    if (rv < loss_rate)
    {
        return (1);
    }
    else
    {
        return (0);
    }
}