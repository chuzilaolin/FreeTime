#include <iostream>
#include <sw/redis++/redis++.h>

using namespace std;
using namespace sw::redis;


int main() {
    Redis redis("tcp://8.137.12.216:6379"); // 服务器ip和端口
    redis.auth("tiger"); // 密码
    redis.set("name", "chuzilaolin"); // 插入一个键值对
    auto val = redis.get("name"); // 获取值
    if (val) {
        cout << "val = " << *val << endl;
    }
    return 0;
}

