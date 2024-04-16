#include <func.h>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <workflow/WFFacilities.h>


using std::cout;
using std::endl;

static WFFacilities::WaitGroup gWaitGroup(1);
void handler(int signum) {
    gWaitGroup.done();
}
void test0() {
    signal(SIGINT, handler);
    WFRedisTask *redisTask = WFTaskFactory::create_redis_task("redis://8.137.12.216:6379", 0, [](WFRedisTask *redisTask){
        protocol::RedisRequest *req = redisTask->get_req();
        protocol::RedisResponse *resp = redisTask->get_resp();
        int state = redisTask->get_state();
        int error = redisTask->get_error();
        switch(state) {
            case WFT_STATE_SYS_ERROR:
                cout << "sys error" << strerror(error) << endl;
                break;
            case WFT_STATE_DNS_ERROR:
                cout << "dns error" << gai_strerror(error) << endl;
                break;
            case WFT_STATE_SUCCESS:
                cout << "success" << endl;
                break;
        }
    });
    protocol::RedisRequest *req = redisTask->get_req();

    redisTask->start();
    gWaitGroup.wait(); 
}

int main(void) {
    auto begin = std::chrono::high_resolution_clock::now();
    test0();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

