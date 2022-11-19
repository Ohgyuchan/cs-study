#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 256
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int sd;
    FILE *fp;

    char buf[BUF_SIZE];
    char file_name[BUF_SIZE];
    char new_name[BUF_SIZE];
    memset(buf, 0, BUF_SIZE);

    int read_cnt;
    socklen_t adr_sz;
    struct sockaddr_in serv_adr, from_adr;
    if (argc != 3)
    {
        printf("Usage: %s <IP> <filename>\n", argv[0]);
        exit(1);
    }

    printf("Input file name: ");
    scanf("%s", file_name);

    printf("Input new file name: ");
    scanf("%s", new_name);

    sd = socket(PF_INET, SOCK_DGRAM, 0);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    sendto(sd, file_name, BUF_SIZE, 0, (struct sockaddr *)&serv_adr, sizeof(serv_adr));
    adr_sz = sizeof(from_adr);
    printf("file name:%s\n", file_name);

    fp = fopen(new_name, "wb");

    read_cnt = recvfrom(sd, buf, BUF_SIZE, 0, (struct sockaddr *)&from_adr, &adr_sz);
    printf("recvfrom's return value: %d, %s\n", read_cnt, buf);

    fwrite((void *)buf, 1, BUF_SIZE, fp);
    printf("***********************************************************\n");
    printf("'%s' is written in '%s'\n", buf, new_name);
    printf("***********************************************************\n");

    fclose(fp);
    close(sd);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}