#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <ctype.h>
#include <func.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

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
    int maxfd = socketfd; // maxfd用于记录操作系统分配的最大fd;
    // 5. 创建用于存储客户端连接的数组
    int clients[FD_SETSIZE];
    int i;
    int maxi = -1; // maxi用于记录客户端占用的下标的位置;
    for (i = 0; i < FD_SETSIZE; ++i) {
        clients[i] = -1;
    }
    // 6. 把socketfd加入待监听集合
    fd_set allset; // 用于保存所有文件描述符的集合
    fd_set redyset; // 用于监听并获取就绪描述符的集合 
    FD_ZERO(&allset);
    FD_SET(socketfd, &allset);
    // 7. loop循环
    while (1) {
        // 8. 开启select监听
        redyset = allset;
        int nready = select(maxfd + 1, &redyset, NULL, NULL, NULL);
        if (nready < 0) {
            perror("select error");
            exit(-1);
        }
        // 9. 处理socketfd就绪事件
        if (FD_ISSET(socketfd, &redyset)) {
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
            FD_SET(netfd, &allset);
            // 9.3 把客户端netfd加入客户端数组
            for (i = 0; i < FD_SETSIZE; ++i) {
                if (clients[i] < 0) {
                    clients[i] = netfd;
                    break;
                }
            }
            if (i == FD_SETSIZE) { // 客户端数组存满了
                printf("Too many clients\n");
                exit(-1);
            }
            // 9.4 更新maxfd 和 maxi
            if (netfd > maxfd) {
                maxfd = netfd;
            }
            if (i > maxi) {
                maxi = i;
            }
            // 9.5 判断本次的就绪事件是否已处理完
            if (0 == --nready) {
                continue;
            }
        }
        // 10. 处理客户端就绪事件
        for (i = 0; i < FD_SETSIZE; ++i) {
            int netfd = clients[i];
            char buf[BUFSIZ] = {0};
            if (netfd > 0 && FD_ISSET(netfd, &redyset)) {
                // 10.1 处理客户端断开连接
                if (recv(netfd, buf, sizeof(buf), 0) == 0) {
                    printf("客户端下线...\n");
                    close(netfd);
                    FD_CLR(netfd, &allset);
                    clients[i] = -1;
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


