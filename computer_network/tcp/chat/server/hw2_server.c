#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUF_SIZE 100
void error_handling(char *buf);

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    struct timeval timeout;
    fd_set reads, cpy_reads;
    socklen_t adr_sz;
    int fd_max, str_len, fd_num, i;
    char buf[BUF_SIZE];
    char echo_msg[BUF_SIZE];
    char names[100][100];
    char is_new_user[100] = {0};
    char usr_msg[100] = "";
    char welcome_msg[1000] = "";

    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");

    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    FD_ZERO(&reads);

    FD_SET(serv_sock, &reads);

    fd_max = serv_sock;

    while (1)
    {
        cpy_reads = reads;

        timeout.tv_sec = 5;
        timeout.tv_usec = 5000;

        if ((fd_num = select(fd_max + 1, &cpy_reads, 0, 0, &timeout)) == -1)
        {
            break;
        }
        if (fd_num == 0)
        {
            printf("time-out\n");
            continue;
        }
        for (i = 0; i < fd_max + 1; i++)
        {
            if (FD_ISSET(i, &cpy_reads))
            {
                if (i == serv_sock)
                {
                    adr_sz = sizeof(clnt_adr);
                    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &adr_sz);
                    FD_SET(clnt_sock, &reads);
                    if (fd_max < clnt_sock)
                        fd_max = clnt_sock;
                    printf("connected client: %d \n", clnt_sock);
                }
                else
                {
                    bzero(buf, BUF_SIZE);
                    bzero(echo_msg, BUF_SIZE);
                    str_len = read(i, buf, BUF_SIZE);
                    if (str_len == 0)
                    {
                        FD_CLR(i, &reads);
                        close(i);

                        sprintf(echo_msg, "User %s has exited!\n", names[i]);
                        int j = 4;
                        while (1)
                        {
                            if (j >= fd_max + 1)
                            {
                                break;
                            }
                            if (i != j)
                                write(j, echo_msg, strlen(echo_msg));
                            j++;
                        }

                        bzero(names[i], BUF_SIZE);
                        printf("echo: %s\n", echo_msg);
                        printf("closed client: %d \n", i);
                    }
                    else
                    {
                        if (strncmp(buf, "name", 4) == 0)
                        {
                            char *tmp;
                            tmp = strtok(buf, " ");
                            if (strcmp(tmp, "name") == 0)
                            {
                                tmp = strtok(NULL, " ");
                                strcpy(names[i], tmp);
                                is_new_user[i] = 1;
                                sprintf(echo_msg, "User %s has entered!\n", tmp);
                                int k;
                                for (k = 4; k < i + 1; k++)
                                {
                                    if (strcmp(names[k], "") == 0)
                                    {
                                        continue;
                                    }
                                    if (k == 4)
                                    {
                                        strcpy(usr_msg, names[k]);
                                        continue;
                                    }
                                    strcat((strcat(usr_msg, ", ")), names[k]);
                                }
                                sprintf(welcome_msg, "Current Users: %s", usr_msg);
                            }
                        }
                        else
                        {
                            sprintf(echo_msg, "%s %s", names[i], buf);
                        }
                        printf("echo: %s\n", echo_msg);
                        int j = 4;
                        while (1)
                        {
                            if (is_new_user[j] == 1)
                            {
                                write(j, welcome_msg, strlen(welcome_msg));
                                is_new_user[j] = 0;
                            }
                            if (j >= fd_max + 1)
                            {
                                break;
                            }
                            if (i != j) // 메시지 발신자를 제외한 모두에게 전송
                                write(j, echo_msg, strlen(echo_msg));
                            j++;
                        }
                    }
                }
            }
        }
    }
    close(serv_sock);
    return 0;
}

void error_handling(char *buf)
{
    fputs(buf, stderr);
    fputc('\n', stderr);
    exit(1);
}
