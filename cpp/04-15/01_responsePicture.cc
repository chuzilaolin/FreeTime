#include <arpa/inet.h>
#include <func.h>
#include <cstdio>
#include <cstdlib>
#include <ios>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <vector>

using namespace std;

class HttpServer {
public:
    HttpServer(string ip, unsigned short port)
    : _ip(ip)
    , _port(port)
    , _sockfd(-1)
    {}
    ~HttpServer() {
        ::close(_sockfd);
    }
    void start();
    void recvAndShow();
    void responsePicture(int netfd);
    string response();
private:
    int _sockfd;
    string _ip;
    unsigned short _port;
};


void HttpServer::start() {
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_sockfd < 0) {
        perror("socket");
        exit(-1);
    }

    int reuse = 1;
    int ret =  setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    if (ret < 0) {
        perror("setsockopt");
        exit(-1);
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(_ip.c_str());
    serverAddr.sin_port = htons(_port);
    ret = ::bind(_sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (ret < 0) {
        perror("bind");
        exit(-1);
    }

    listen(_sockfd, 10);
}
void HttpServer::recvAndShow() {
    while (true) {
        int netfd = accept(_sockfd, nullptr, nullptr);
        char buf[4096] = {0};        
        ssize_t sret = recv(netfd, buf, sizeof(buf), 0);
        printf("sret = %ld, buf = %s\n", sret, buf);
        responsePicture(netfd); 
        /* string resp = response(); */
        /* send(netfd,resp.c_str(),resp.size(),0); */
        ::close(netfd);
    }
}

string HttpServer::response(){
    string startLine = "HTTP/1.1 200 OK\r\n";
    string headers = "Server: MyHttpServer\r\n";
    string body = "<html>Hello world</html>";
    headers += "Content-Type: text/html\r\n";
    //headers += "Content-Type: text/plain\r\n";
    //headers += "Content-Type: application/octet-stream\r\n";
    headers += "Content-Length:" + std::to_string(body.size()) + "\r\n";
    string emptyLine = "\r\n";
    return startLine + headers + emptyLine + body;
}

void HttpServer::responsePicture(int netfd) {
    string pictureName = "/home/parker/document/favicon.png";
    
    ifstream ifs(pictureName, std::ios::binary | std::ios::ate);

    streampos filesize = ifs.tellg();
    ifs.seekg(0, ios::beg);

    string body(filesize, '\0');                                                
    ifs.read(&body[0], filesize);

    string startLine = "HTTP/1.1 200 ok\r\n";
    string headers = "Server: MyHttpServer\r\n"; // 服务器名
    headers + "Content-Type: image/png\r\n"; // 类型
    headers + "Content-Length: " + to_string(filesize) + "\r\n"; // 类型
    string data = startLine + headers + "\r\n" + body;
    ::send(netfd, data.c_str(), data.size(), 0);

    ifs.close();
}


void test0() {
    HttpServer server("0.0.0.0", 12345);
    server.start();
    server.recvAndShow();
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

