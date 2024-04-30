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
    // 5. 创建epoll监听集合
    int epfd = epoll_create(OPEN_MAX);
    if (-1 == epfd) {
        perror("epoll_create error");
        exit(-1);
    }
    // 6. 把socketfd加入监听集合
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = socketfd;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, socketfd, &ev);
    if (-1 == ret) {
        perror("epoll_ctl error");
        exit(-1);
    }
    // 7. loop循环
    while (1) {
        // 8. 开启select监听
        struct epoll_event readEvents[OPEN_MAX]; 
        int nready = epoll_wait(epfd, readEvents, OPEN_MAX, -1);
        if (nready < 0) {
            perror("select error");
            exit(-1);
        }
        // 9. 处理socketfd就绪事件
        for (int i = 0; i < nready; ++i) {
            if (readEvents[i].data.fd == socketfd) {
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
                // 9.1 把netfd加入监听集合
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = netfd;
                ret = epoll_ctl(epfd, EPOLL_CTL_ADD, netfd, &ev);
                if (-1 == ret) {
                    perror("epoll_ctl error");
                    exit(-1);
                }
            } else {
                // 9.2 处理客户端就绪事件
                int netfd = readEvents[i].data.fd;
                char buf[BUFSIZ] = {0};
                int len = recv(netfd, buf, sizeof(buf), 0);
                if (len == 0) {
                    printf("客户端下线...\n");
                    ret = epoll_ctl(epfd, EPOLL_CTL_DEL, netfd, NULL);
                    if (-1 == ret) {
                        perror("close: epoll_ctl error");
                        exit(-1);
                    }
                    close(netfd);
                } else {
                    for (int j = 0; j < len; ++j) {
                        buf[j] = toupper(buf[j]);
                    }
                    send(netfd, buf, len, 0);
                    write(STDOUT_FILENO, buf, len);
                }
            } 
        }
    }
}

int main(int argc,char*argv[]) {
    test();
    return 0;
}


