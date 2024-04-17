#include <func.h>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <workflow/WFFacilities.h>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>


using std::cout;
using std::endl;
using std::string;

struct SeriesContex {
    int i;
    string str;
};

static WFFacilities::WaitGroup gWaitGroup(1);
void handler(int signum) {
    gWaitGroup.done();
}
void test0() {
    signal(SIGINT, handler);
    
    WFHttpTask *task1 = WFTaskFactory::create_http_task(
        "http://www.baidu.com",10 ,0 , [](WFHttpTask *task){
        protocol::HttpRequest *req = task->get_req();
        req->set_header_pair("Accept","*/*");
        protocol::HttpResponse *resp = task->get_resp();
        int state = task->get_state();
        int error = task->get_error();
        switch(state) {
            case WFT_STATE_SYS_ERROR:
                cout << "sys error" << strerror(error) << endl;
                break;
            case WFT_STATE_DNS_ERROR:
                cout << "dns error" << gai_strerror(error) << endl;
                break;
            case WFT_STATE_SUCCESS:
                cout << "task1 success" << endl;
                break;
        }
        protocol::HttpHeaderCursor cursorResp(resp);
        const void *body;
        size_t size;
        resp->get_parsed_body(&body, &size);
    });
    WFRedisTask *task2 = WFTaskFactory::create_redis_task(
        "redis://8.137.12.216:6379", 0, [](WFRedisTask *redisTask) {
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
                cout << "task2 success" << endl;
                break;
        }
        protocol::RedisValue value;
        resp->get_result(value);
        if (value.is_string()) {
            cout << value.string_value() << endl;
        }
        cout << "value:" << value.string_value() << endl;
    });   // cout << string ((char *)body, size) << endl;

    protocol::RedisRequest *req = task2->get_req();
    req->set_request("GET", {"name"});

    // task1->start();
    task2->start();
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

