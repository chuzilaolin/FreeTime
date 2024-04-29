#include <arpa/inet.h>
#include <func.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>


void test() {
    // 1. 创建socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);   
    if (-1 == socketfd) {
        perror("socket error");
        exit(-1);
    }
    // 2. 连接服务端
    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    serv_addr.sin_port = htons(8888);
    int ret = connect(socketfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (-1 == ret) {
        perror("connect error");
        exit(-1);
    }
    // 3. 循环发送读取数据
    while (1) {
        char buf[BUFSIZ] = {0};
        fgets(buf, sizeof(buf), stdin);
        send(socketfd, buf, strlen(buf), 0);
        bzero(buf, sizeof(buf));
        recv(socketfd, buf, sizeof(buf), 0);
        write(STDIN_FILENO, buf, strlen(buf));

    }
}

int main() {
    test();
    return 0;
}


