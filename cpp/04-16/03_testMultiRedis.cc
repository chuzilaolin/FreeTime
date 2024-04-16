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
    WFRedisTask *task1= WFTaskFactory::create_redis_task(
        "redis://8.137.12.216:6379", 0, [](WFRedisTask *redisTask){
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
                cout << "task1 success" << endl;
                break;
        }
        protocol::RedisValue value;
        resp->get_result(value);
        SeriesContex *context = (SeriesContex*)series_of(redisTask)->get_context(); 
        if (value.is_string()) {
            cout << value.string_value() << endl;
            context->str = value.string_value();
        }
    });

    WFRedisTask *task2 = WFTaskFactory::create_redis_task(
        "redis://8.137.12.216:6379", 0, [](WFRedisTask *redisTask) {
        SeriesContex *context = (SeriesContex*)series_of(redisTask)->get_context(); 
        protocol::RedisRequest *req = redisTask->get_req();
        req->set_request("Get", {context->str});
        protocol::RedisResponse *resp = redisTask->get_resp();
        int state = redisTask->get_state();
        int error = redisTask->get_error();
        // sleep(3);
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
            context->str = value.string_value();
        }
    });

    WFRedisTask *task3 = WFTaskFactory::create_redis_task(
        "redis://8.137.12.216:6379", 0, [](WFRedisTask *redisTask) {
        SeriesContex *context = (SeriesContex*)series_of(redisTask)->get_context();
        protocol::RedisRequest *req = redisTask->get_req();
        req->set_request("Get", {context->str});
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
                cout << "task3 success" << endl;
                break;
        }
        protocol::RedisValue value;
        resp->get_result(value);
        if (value.is_string()) {
            cout << value.string_value() << endl;
            context->str = value.string_value();
        }
    });

    WFRedisTask *task4 = WFTaskFactory::create_redis_task(
        "redis://8.137.12.216:6379", 0, [](WFRedisTask *redisTask) {
        SeriesContex *context = (SeriesContex*)series_of(redisTask)->get_context();
        protocol::RedisRequest *req = redisTask->get_req();
        req->set_request("Get", {context->str});
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
                cout << "task3 success" << endl;
                break;
        }
        protocol::RedisValue value;
        resp->get_result(value);
        if (value.is_string()) {
            cout << value.string_value() << endl;
            context->str = value.string_value();
        }
    });

    protocol::RedisRequest *req1 = task1->get_req();
    req1->set_request("Get", {"x1"});
    protocol::RedisRequest *req2 = task2->get_req();
    req2->set_request("Get", {"x2"});
    protocol::RedisRequest *req3 = task3->get_req();
    req3->set_request("Get", {"x3"});
    protocol::RedisRequest *req4 = task4->get_req();
    req4->set_request("Get", {"x4"});


    SeriesContex *contex1 = new SeriesContex();
    SeriesWork *series = Workflow::create_series_work(task1, [](const SeriesWork *series){
        SeriesContex *context = (SeriesContex *)series->get_context();
        delete context; 
    });
    series->set_context(contex1);

    series->push_back(task2);
    series->push_back(task3);
    series->push_back(task4);

    series->start();
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

