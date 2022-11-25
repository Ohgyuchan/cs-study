#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXPENDING 5 // 서버에서 받을 허용 인원.

int main(int argc, char **argv)
{
    int servSock;               // 서버소켓
    int clntSock;               // 클라이언트소켓
    int iRet;                   // 저장할 변수
    unsigned char uc_buff[500]; // 채팅시에 문자열을 받는 버퍼.

    struct sockaddr_in echoServAddr; // 신구조체의 서버IP를 가지는 변수.
    struct sockaddr_in echoClntAddr; // 신구조체의 클라이언트IP를 가지는 변수

    unsigned short echoServPort; // Port 번호를 가지는 변수. 2byte 크기.
    unsigned int clntLen;        // 클라이언트

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <Port number>\n You gave %d Arguments\n", argv[0], argc);
        exit(1);
    }

    echoServPort = 9999; // Port 번호 0~65535 범위를 가짐.

    // Socket 생성
    // 프로토콜패밀리결정, 소켓의형태(데이타보내는방식,SOCK_STREAM or SOCK_DGRAM)설정,
    // STREAM인지DGRAM인지에 따라서 IPPROTO_TCP , IPPROTO_UDP 로 정해줌.
    // 신뢰성 : STREAM (데이터의 송수신값을 확인하며 보냄),ex)일반파일
    // 비신뢰성 : DGRAM(데이터을 확인없이 한번에 보냄),ex)MP3..
    servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (0 > servSock) // Error 코드
    {
        printf("socket() failed\n");
        return 0;
    }

    // 메모리 크기를 특정값으로 초기화 여기서는 0 으로 만들어줌.
    memset(&echoServAddr, 0, sizeof(echoServAddr));
    // #define AF_INET PF_INET 2 로 define 되어있음.  패밀리선택, 우리는 PF_INET 을 쓴다.
    echoServAddr.sin_family = AF_INET;
    // Host to Network long 으로 host의 크기를 Long형(4byte)만큼
    // 지정하고 little-Endian -> Big-Endian방식으로 보내줌.
    // 0 을 넣어주면 Host에서 주소를 랜덤으로 줌, 고정적으로 사용하고 싶을때는 직접 주소값을 넣어줌.
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // Host to Network short 으로 host의 크기를 short형(2byte)만큼
    // 지정하고 little-Endian -> Big-Endian방식으로 보내줌.
    // 0 을 넣어주면 Host에서 주소를 랜덤으로 줌, 고정적으로 사용하고 싶을때는 직접 주소값을 넣어줌.
    echoServAddr.sin_port = htons(echoServPort); // Port는 정해져있으므로 정해줌.

    // 구조체 안에 설정한것을  소켓에다가 넣어줌. bind()
    iRet = bind(servSock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr));

    // if조건문을 위해서 iRet 변수를 지정.
    if (0 > iRet)
    {
        printf("bind() failed\n");
        close(servSock); // 서버소켓 닫기.
        return 0;
    }

    // listen(서버소켓, 받을 클라이언트 수)
    // if조건문을 위해서 iRet 변수를 지정.
    iRet = listen(servSock, MAXPENDING); // Client 연결할때마다 하나씩 새로운 소켓을 얻는데 사용.
    if (0 > iRet)
    {
        printf("listen() failed\n");
        close(servSock);
        return 0;
    }

    // 서버로 들어오는 클라이언트연결에대해서 accept()를 호출하면서 소켓을 만든다.
    clntLen = sizeof(echoClntAddr); // clntLen로 Client 크기를 받고, clntLen의 주소를 인자로 넘김.
    // 대기중에 있다가 서버에 접속허용을 받으면 Client 소켓을 만듬. 강제로 대기(블로킹함수)
    clntSock = accept(servSock, (struct sockaddr *)&echoClntAddr, &clntLen);
    // 소켓은 2가지가 있는데 랑데뷰소켓, 커뮤니케이션소켓이 있다.
    // accept 함수에 의해서 랑데뷰소켓이 생성됨.(랑데뷰소켓은 Clinet 의 주소를 들고있음)

    if (0 > clntSock) // 클라이언트소켓 생성 확인 구문
    {
        printf("accept() failed\n");
        close(servSock);
        return 0;
    }

    // Network to ASCII, 클라이언트IP를 문자열[(ex)192.211.10.20]로 바꿔서 출력해줌.
    printf("Handling client IP %s\n", inet_ntoa(echoClntAddr.sin_addr));
    // Port 번호를 Network to Host short형 크기로 출력해줌.
    printf("Handling client PORT  %d\n", ntohs(echoClntAddr.sin_port));

    while (1)
    {
        iRet = read(clntSock, uc_buff, sizeof(uc_buff) - 1); // read함수로 상대방말을 읽어옴.
        uc_buff[iRet] = 0;
        write(1, uc_buff, iRet);
        if ('q' == uc_buff[0])
        {
            break; // 'q' 를 눌러서 종료.
        }
    }

    close(servSock); // 서버소켓을 닫기.
    close(clntSock); // 클라이언트소켓을 닫기.

    return 0;
}