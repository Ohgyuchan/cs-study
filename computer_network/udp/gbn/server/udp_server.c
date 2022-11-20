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
        int serv_sd, clnt_sd;
        int str_len;
        FILE *fp;
        char buf[BUF_SIZE];
        char file_name[BUF_SIZE];
        int read_cnt;

        struct sockaddr_in serv_adr, clnt_adr;
        socklen_t clnt_adr_sz;

        if (argc != 2)
        {
            printf("Usage: %s <port>\n", argv[0]);
            exit(1);
        }

        serv_sd = socket(PF_INET, SOCK_DGRAM, 0);

        memset(buf, 0, BUF_SIZE);
        memset(&serv_adr, 0, sizeof(serv_adr));
        serv_adr.sin_family = AF_INET;
        serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_adr.sin_port = htons(atoi(argv[1]));

        bind(serv_sd, (struct sockaddr *)&serv_adr, sizeof(serv_adr));

        clnt_adr_sz = sizeof(clnt_adr);

        if (fp != NULL)
        {
            while (1)
            {
                recvfrom(serv_sd, file_name, BUF_SIZE, 0, (struct sockaddr *)&clnt_adr, &clnt_adr_sz);
                printf("file name : %s\n", file_name);
                fp = fopen(file_name, "rb"); // get out
                if (fp == NULL) {
                    printf("fopen error\n");
                    return -1;
                }

                read_cnt = fread(buf, 1, BUF_SIZE, fp);

                if (read_cnt < BUF_SIZE)
                {
                    sendto(serv_sd, buf, read_cnt, 0, (struct sockaddr *)&clnt_adr, clnt_adr_sz);
                    printf("case 1]fread() return value : %d\n", read_cnt);
                    printf("**********************************************************\n");
                    printf("I read '%s' from '%s'\n", buf, file_name);
                    printf("**********************************************************\n");
                    break;
                }
                printf("read : %s\n", buf);
                sendto(serv_sd, buf, BUF_SIZE, 0, (struct sockaddr *)&clnt_adr, clnt_adr_sz);
                printf("case 2]fread() return value : %d\n", read_cnt);
                // fclose:w!
            }
        }
        else
            printf("fopen() failed\n");

        fclose(fp);
        close(clnt_sd);
        close(serv_sd);
        return 0;
    }

    void error_handling(char *message)
    {
        fputs(message, stderr);
        fputc('\n', stderr);
        exit(1);
    }