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
    printf("signum = %d\n", signum);
    gWaitGroup.done();
}
void test0() {
    signal(SIGINT, handler);
    WFRedisTask *task1 = WFTaskFactory::create_redis_task(
    "redis://:tiger@8.137.12.216:6379", 0, [](WFRedisTask *task) {
        protocol::RedisResponse *resp = task->get_resp();
        int state = task->get_state(); 
        int error = task->get_error();
        protocol::RedisValue value;
        resp->get_result(value);
        cout << "------" << endl;
        switch(state) {
            case WFT_STATE_SYS_ERROR:
                cout << "sys error" << strerror(error) << endl;
                break;
            case WFT_STATE_DNS_ERROR:
                cout << "dns error" << gai_strerror(error) << endl;
                break;
            case WFT_STATE_SUCCESS:
                cout << "task2 success" << endl;
                break;
        }
        if (value.is_string()) {
            cout << "name = " << value.string_value() << endl;
        } 
        cout << "name = " << value.string_value() << endl;
    });
    protocol::RedisRequest *req = task1->get_req();
    req->set_request("auth", {"tiger"});
    req->set_request("get", {"name"});
    task1->start();
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

