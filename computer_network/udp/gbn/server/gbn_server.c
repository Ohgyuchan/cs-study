#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/timeb.h>
#include <strings.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define TRUE 1
#define FALSE 0
#define MAX_PACKET_SIZE 1024

#define START 1 // 처음 패킷전송시
#define DATA 2  // 두번째이후 데이터 전송시
#define ACK 3   // ACK전송시
#define END 4   // 연결을 종료

typedef struct PACKET
{
    int type; // 1.START 2.DATA 3.ACK 4.END
    unsigned int packet_number;
    unsigned int seqnumber; // sequence number
    unsigned short checksum;
    char data[MAX_PACKET_SIZE]; // application data (variable length)
    unsigned int packet_data_size;
    unsigned int ack;
    int loss;
    int error;
} PACKET;

char timestring[30];

void initialize_packet(PACKET *pkt);
int tcp_listen(int port);
int tcp_connect(int servsock);
// int udp_connect(int port);
int rdt_tcp_rcv(PACKET *pkt, int accp_sock, int seqnum);
void make_ack(PACKET *ack_pkt, PACKET pkt);
unsigned short make_ack_checksum(PACKET *pkt);
unsigned short make_checksum(PACKET *pkt);
int is_corrupt(PACKET *pkt);
int hasseqnum(PACKET *pkt, int seqnum);
void occur_loss(PACKET *ack_pkt, int loss);
void occur_error(PACKET *ack_pkt, int error);
void delay_ack(int delay);
void udt_send(PACKET ack_pkt, int accp_sock);
void get_time(char timestring[]);
void write_data_file(char file_name[], PACKET *pkt);

int main(int argc, char *argv[])
{
    PACKET ACK_pkt;
    int port;
    int loss;
    int error;
    char mode[10];
    int delay;
    int expectedseqnum = 0;

    PACKET pkt;
    int servsock;
    int accp_sock;
    int addrlen;
    struct sockaddr_in cliaddr;
    int sock;
    struct sockaddr_in servaddr;

    if (argc != 6)
    {
        printf("사용 방법 : (서버 프로그램) (TCP/UDP) (손실 확률) (에러 확률) (전송 지연) (포트번호)\n");
        return 0;
    }

    strcpy(mode, argv[1]);
    loss = atoi(argv[2]);
    error = atoi(argv[3]);
    delay = atoi(argv[4]);
    port = atoi(argv[5]);

    // 패킷 초기화
    initialize_packet(&pkt);
    system("clear");
    while (1)
    {
        // 연결 준비

        if (strcmp(mode, "TCP") == 0 || strcmp(mode, "UDP") == 0)
        {
            servsock = tcp_listen(port);
            accp_sock = tcp_connect(servsock);
        }

        /*if(strcmp(mode, "UDP") == 0)
        {

           if((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
           {
              printf("sock error\n");

              exit(1);
           }

           bzero((char*)&servaddr, sizeof(servaddr));
           servaddr.sin_family = AF_INET;
           servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
           servaddr.sin_port = htons(port);

           if(bind(sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) <0)
           {
              printf("bind error");
              exit(1);
           }

        }
  */
        while (1)
        {
            // 패킷수신
            if (strcmp(mode, "TCP") == 0 || strcmp(mode, "UDP") == 0)
                expectedseqnum = rdt_tcp_rcv(&pkt, accp_sock, expectedseqnum);

            // if(strcmp(mode, "UDP") == 0)
            //{
            //    addrlen = sizeof(cliaddr);
            //
            //    if(recvfrom(sock, (char*)&pkt, sizeof(PACKET), 0, (struct sockaddr*)&cliaddr, &addrlen) > 0)
            //    {
            //       //체크섬 검사
            //       if(is_corrupt(&pkt) == TRUE)
            //       {
            //          printf("패킷 에러\n");

            //      }
            //
            //      //시퀀스 번호 검사
            //      else if(hasseqnum(&pkt, expectedseqnum) == TRUE){
            //         expectedseqnum = pkt.seqnumber+pkt.packet_data_size;
            //      }
            //
            //   }
            //   else
            //      perror("recv error\n");

            //}
            usleep(1000);
            get_time(timestring);
            // printf("expectedseqnum : %d\n", expectedseqnum);
            pkt.ack = expectedseqnum;
            printf("[%s][패킷 수신][패킷 번호%d][%s][expectedseqnum %d]\n", timestring, pkt.packet_number, (pkt.error == TRUE) ? "에러유" : "에러무", expectedseqnum);

            // ACK 생성
            make_ack(&ACK_pkt, pkt);

            // 손실 함수
            occur_loss(&ACK_pkt, loss);

            // 에러 함수
            occur_error(&ACK_pkt, error);

            // 지연 함수
            delay_ack(delay);

            // ACK 전송
            if (strcmp(mode, "TCP") == 0 || strcmp(mode, "UDP") == 0)
                udt_send(ACK_pkt, accp_sock);
            /*if(strcmp(mode, "UDP") == 0)
            {
               if(ACK_pkt.loss == TRUE) {
                  get_time(timestring);
                  continue;
               }

               if((sendto(sock, (char*)&ACK_pkt, sizeof(PACKET), 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr))) < 0)
               {
                  perror("send error");

                  exit(1);
               }
            }*/
            printf("[%s][ACK 전송][ACK 번호 %d][%s][%s]\n", timestring, ACK_pkt.packet_number, (ACK_pkt.loss == TRUE) ? "유손실" : "무손실", (ACK_pkt.error == TRUE) ? "유에러" : "무에러");

        } // end of while
    }

    return 0;
}

void initialize_packet(PACKET *pkt)
{
    pkt->ack = 0;
    pkt->checksum = 0;
    memset(pkt->data, 0, sizeof(pkt->data));
    pkt->packet_data_size = 0;
    pkt->packet_number = 0;
    pkt->seqnumber = 0;
    pkt->type = 0;
}

int tcp_listen(int port)
{
    int sock;
    struct sockaddr_in servaddr;
    // struct sockaddr_in cliaddr;

    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("sock error\n");
        exit(1);
    }

    bzero((char *)&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    if (bind(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("bind error");
        exit(1);
    }

    listen(sock, 1);
    return sock;
}

// int udp_connect(int port)
//{
//
// }

int tcp_connect(int servsock)
{
    int accp_sock;
    unsigned int addrlen;
    struct sockaddr_in cliaddr;
    fd_set read_fds, fd_sock;

    FD_ZERO(&read_fds);
    FD_SET(servsock, &read_fds);
    addrlen = sizeof(struct sockaddr_in);

    fd_sock = read_fds;
    // accept
    if (FD_ISSET(servsock, &fd_sock))
    {
        accp_sock = accept(servsock, (struct sockaddr *)&cliaddr, &addrlen);
        if (accp_sock == -1)
        {
            printf("accept error\n");
            exit(1);
        }
        // gbn 파라메터 초기화
    }

    return accp_sock;
}

int rdt_tcp_rcv(PACKET *pkt, int accp_sock, int seqnum)
{
    // 패킷 수신
    read(accp_sock, pkt, sizeof(PACKET));

    // 체크섬 검사
    if (is_corrupt(pkt) == TRUE)
    {
        printf("패킷 에러\n");
        return seqnum;
    }

    // 시퀀스 번호 검사
    if (hasseqnum(pkt, seqnum) == TRUE)
    {
        seqnum = pkt->seqnumber + pkt->packet_data_size;
        // printf("검사했는데 둘 다 맞았다. 패킷 사이즈 :%dTRUE\n", pkt->packet_data_size);
    }

    get_time(timestring);

    // printf("번호 검사후 seqnum : %d\n", seqnum);
    write_data_file("data.dat", pkt);

    return seqnum;
}

void make_ack(PACKET *ack_pkt, PACKET pkt)
{
    ack_pkt->ack = pkt.ack;
    ack_pkt->checksum = make_ack_checksum(ack_pkt);
    strcpy(ack_pkt->data, pkt.data);
    ack_pkt->error = 0;
    ack_pkt->loss = 0;
    ack_pkt->packet_data_size = pkt.packet_data_size;
    ack_pkt->packet_number = pkt.packet_number;
    ack_pkt->seqnumber = pkt.seqnumber;
    ack_pkt->type = pkt.type;
}

int is_corrupt(PACKET *pkt)
{
    unsigned short receive_checksum;

    // 체크섬 생성
    receive_checksum = make_checksum(pkt);

    // 수신측 체크섬과 보낸 패킷의 체크섬을 비교하여 에러 체크
    if (receive_checksum != pkt->checksum)
        return TRUE;

    return FALSE;
}

int hasseqnum(PACKET *pkt, int seqnum)
{
    // 시퀀스 넘버 체크
    // printf("시퀀스 번호 체크 : 수신된 패킷의 시퀀스 번호 : %d 수신받는 쪽의 seq: %d\n", pkt->seqnumber, seqnum);
    if (seqnum != pkt->seqnumber)
        return FALSE;

    return TRUE;
}

unsigned short make_checksum(PACKET *pkt)
{
    register unsigned int sum = 0;
    register int i;
    register unsigned short word16;

    // 2개의 8비트를 가져와서
    // 16비트 워드를 sum과 더해서 누적시킨다.
    for (i = 0; i < pkt->packet_data_size; i += 2)
    {
        word16 = ((pkt->data[i] << i) & 0xFF00) + ((pkt->data[i + 1] >> i) & 0xFF);
        sum = sum + (unsigned int)word16;
    }

    //// keep only the last 16 bits of the 32bit calculated sum
    //// and add the carries
    // while(sum>>16)
    //     sum = (sum & 0xFFFF) + (sum >> 16);

    // 1의 보수화
    sum = ~sum;

    return (unsigned short)sum;
}

unsigned short make_ack_checksum(PACKET *pkt)
{
    register unsigned int sum = 0;
    register int i;

    // 2개의 8비트를 가져와서
    // 16비트 워드를 sum과 더해서 누적시킨다.
    for (i = 16; i >= 0; i--)
        sum = sum + ((pkt->ack) >> i) & 0xFF;

    //// keep only the last 16 bits of the 32bit calculated sum
    //// and add the carries
    // while(sum>>16)
    //     sum = (sum & 0xFFFF) + (sum >> 16);

    // 1의 보수화
    sum = ~sum;

    return (unsigned short)sum;

    //   //make 16bit words out of every two adjacent 8 bit word and
    //   //calculate the sum of all 16 bit words
    //   for(i = 0; i < sizeof(pkt->data) ; i+=2)
    //   {
    //       word16 = ((pkt->data[i] << 8) & 0xFF00) + (pkt->data[i+1] & 0xFF);
    //    sum = sum + (unsigned int)word16;
    //   }
    //   // keep only the last 16 bits of the 32bit calculated sum
    //   // and add the carries
    //   while(sum>>16)
    //       sum = (sum & 0xFFFF) + (sum >> 16);

    //   // Take the one's complement of sum
    //   sum = ~sum;

    // return (unsigned short)sum;
}

void occur_loss(PACKET *ack_pkt, int loss)
{
    int value;
    static int cnt;
    cnt += 2;

    srand(time(NULL) + cnt);
    value = rand() % 100;

    if (value > 0 && value <= loss)
    {
        ack_pkt->loss = TRUE;
        return;
    }

    ack_pkt->loss = FALSE;
}

void occur_error(PACKET *ack_pkt, int error)
{
    int value;
    static int cnt;
    cnt += 2;

    srand(time(NULL) + cnt);
    value = rand() % 100;

    if (value > 0 && value <= error)
    {
        ack_pkt->error = TRUE;
        ack_pkt->ack = ack_pkt->ack << 1;
        return;
    }

    ack_pkt->error = FALSE;
}

void delay_ack(int delay)
{
    usleep(delay * 1000);
}

void udt_send(PACKET ack_pkt, int accp_sock)
{
    if (ack_pkt.loss == TRUE)
    {
        get_time(timestring);
        return;
    }

    if ((send(accp_sock, (char *)&ack_pkt, sizeof(PACKET), 0)) < 0)
    {
        perror("send error");
        exit(1);
    }
    // printf("패킷전송\n");
}

void get_time(char timestring[])
{
    struct timeval val;
    struct tm *ptm;

    gettimeofday(&val, NULL);
    ptm = localtime(&val.tv_sec);

    memset(timestring, 0x00, sizeof(timestring));

    // format : YYMMDDhhmmssuuuuuu
    sprintf(timestring, "%02d:%02d.%02d.%06ld ms", ptm->tm_hour, ptm->tm_min, ptm->tm_sec, val.tv_usec);
}

void write_data_file(char file_name[], PACKET *pkt)
{
    FILE *fp;
    int i;
    char ch;

    fp = fopen(file_name, "a");

    for (i = 0; i < pkt->packet_data_size; i++)
    {
        ch = pkt->data[i];
        putc(ch, fp);
    }
    // fprintf(fp, "%s", pkt->data);

    fclose(fp);
}