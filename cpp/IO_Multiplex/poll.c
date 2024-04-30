#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <ctype.h>
#include <func.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/poll.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#define OPEN_MAX 1024

void test() {
    // 1. 创建Socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (-1 == socketfd) {
        perror("socket error");
        exit(-1);
    }
    // 2. 为Socket设置可重用属性
    int opt = 1;
    int ret = setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (-1 == ret) {
        perror("setsockopt error");
        exit(-1);
    }
    // 3. 绑定ip和端口
    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    /* serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); */ 
    serv_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    serv_addr.sin_port = htons(8888);
    ret = bind(socketfd, (struct sockaddr *)(&serv_addr), sizeof(serv_addr));
    if (-1 == ret) {
        perror("bind error");
        exit(-1);
    }
    // 4. 开启监听
    listen(socketfd, 128);
    // 5. 创建用于存储客户端连接的数组
    struct pollfd clients[OPEN_MAX];
    int i;
    for (i = 0; i < FD_SETSIZE; ++i) {
        clients[i].fd = -1;
    }
    // 6. 把socketfd加入监听集合
    clients[0].fd = socketfd;
    clients[0].events = POLLIN;
    int maxi = 0; // maxi用于记录客户端占用的下标的位置;
    // 7. loop循环
    while (1) {
        // 8. 开启select监听
        int nready = poll(clients, maxi + 1, -1);
        if (nready < 0) {
            perror("select error");
            exit(-1);
        }
        // 9. 处理socketfd就绪事件
        if (clients[0].revents & POLLIN) {
            // 9.1 获取客户端连接
            struct sockaddr_in clie_addr;
            socklen_t clie_addr_len = sizeof(clie_addr);
            int netfd = accept(socketfd, (struct sockaddr *)&clie_addr, &clie_addr_len);
            if (-1 == netfd) {
                perror("accept error");
                exit(-1);
            }
            char str[BUFSIZ] = {0};
            printf("%s:%d加入连接\n", inet_ntop(AF_INET, &clie_addr.sin_addr, str, sizeof(str))
                   , ntohs(clie_addr.sin_port));
            // 9.2 客户端的netfd加入待监听集合
            for (i = 1; i < FD_SETSIZE; ++i) { // 0下标为socketfd,所以从1开始
                if (clients[i].fd < 0) {
                    printf("找到位置%d\n", i);
                    clients[i].fd = netfd;
                    clients[i].events = POLLIN;
                    break;
                }
            }
            if (i == OPEN_MAX) { // 客户端数组存满了
                printf("Too many clients\n");
                exit(-1);
            }
            // 9.3 更新maxi
            if (i > maxi) {
                maxi = i;
            }
            // 9.4 判断本次的就绪事件是否已处理完
            if (0 == --nready) {
                continue;
            }
        }
        // 10. 处理客户端就绪事件
        for (i = 1; i < FD_SETSIZE; ++i) {
            int netfd = clients[i].fd;
            char buf[BUFSIZ] = {0};
            if (netfd > 0 && (clients[i].revents & POLLIN)) {
                // 10.1 处理客户端断开连接
                if (recv(netfd, buf, sizeof(buf), 0) == 0) {
                    printf("客户端下线...\n");
                    close(netfd);
                    clients[i].fd = -1;
                }
                // 10.2 回复客户端消息
                for (int j = 0; j < strlen(buf); ++j) {
                    buf[j] = toupper(buf[j]);
                }
                send(netfd, buf, strlen(buf), 0);
                write(STDOUT_FILENO, buf, strlen(buf));
                // 10.3 判断就绪事件是否处理完
                if (0 == --nready) {
                    break;
                }
            }
        } 
    }
}

int main(int argc,char*argv[]) {
    test();
    return 0;
}


