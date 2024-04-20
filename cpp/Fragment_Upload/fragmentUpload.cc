#include "json.hpp"
#include <func.h>
#include <iostream>
#include <string>
#include <chrono>
#include <workflow/WFFacilities.h>
#include <workflow/WFHttpServer.h>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <sw/redis++/redis++.h>

using std::cout;
using std::endl;
using std::string;

using namespace sw::redis;


/**
 * @brief 文件分片上传类
*/
class FragmentUpload {
public:
    FragmentUpload(WFHttpTask *httpTask) :_httpTask(httpTask) {} 
    void init();
    void uppart();
    void complete();
private:
    WFHttpTask *_httpTask;
    string _fileDir = "./file/"; // 文件存储目录 
    size_t _chunkSize = 1024 * 10; // 分片大小
};

/**
 * @brief 获取用户名
 * @return 用户名
*/
string getUserName() {
    return "lg";
}

// /file/mupload/init 初始化文件分片上传
void FragmentUpload::init() {
    // 1. 从body获取请求参数
    protocol::HttpRequest *req = _httpTask->get_req();
    char *body;
    size_t bodySize;
    req->get_parsed_body((const void **)&body, &bodySize);
    // 2. json解析
    nlohmann::json json = nlohmann::json::parse(body);
    string fileName = json["fileName"];     
    string fileHash = json["fileHash"];     
    size_t fileSize = json["fileSize"];     
    // 3. 生成分片信息（uploadId、分片个数、分片大小（允许最后一片不一样大）)
    int chunkSize = _chunkSize; // 分片大小
    int chunkCount = fileSize / chunkSize + 1;  // 分片个数
    string uploadId = getUserName() + "_" + fileHash;
    // 4. 保存分片信息到redis
    bool ret = true;
    WFRedisTask *redisTask = WFTaskFactory::create_redis_task(
        "redis://:tiger@8.137.12.216:6379", 0, [&ret](WFRedisTask *redisTask) {
            protocol::RedisResponse *resp = redisTask->get_resp();
            protocol::RedisValue value;
            resp->get_result(value);
            ret = value.is_ok();
        }
    );
    redisTask->get_req()->set_request("HSET", {uploadId, 
        "fileName", fileName,
        "fileHash", fileHash,
        "fileSize", std::to_string(fileSize),
        "chunkCount", std::to_string(chunkCount),
        "chunkSize", std::to_string(chunkSize)
    });
    redisTask->start();
    // 5. 存入数据库（文件主表、用户-文件表）----暂时不做 
    // 6. 返回响应 
    nlohmann::json respJson;
    respJson["status"] = ret;
    if (ret) {
        json["chunkCount"] = chunkCount;
        json["chunkSize"] = chunkSize;
        json["uploadId"] = uploadId;
        respJson["data"] = json;
    }
    _httpTask->get_resp()->append_output_body(respJson.dump());
    cout << "init" << endl;
}

// /file/mupload/uppart 上传分片
void FragmentUpload::uppart() {
    // 1. 从头部取出请求参数
    protocol::HttpRequest *req = _httpTask->get_req();
    const http_parser_t *parser = req->get_parser();
    protocol::HttpHeaderCursor cursor(req);
    string name;
    string value;
    string uploadId;
    size_t chunkId;
    size_t chunkSize;
    string chunkHash;
    while(cursor.next(name, value)) {
        if ("uploadId" == name) {
            uploadId = value;
        } 
        else if ("chunkId" == name) {
            chunkId = std::stoi(value);
        }
        else if ("chunkSize" == name) {
            chunkSize = std::stoi(value);
        }
        else if ("chunkHash" == name) {
            chunkHash = value;
        }
    }
    // 2. 从body获取分片数据
    char *body;
    size_t bodySize;
    req->get_parsed_body((const void **)&body, &bodySize);
    string bodyStr(body, bodySize);
    bodyStr = bodyStr.substr(bodyStr.find("\r\n\r\n") + 4);
    bodyStr = bodyStr.substr(0, bodyStr.find("\r\n------"));
    // 3. 更新redis中的分片信息
    WFRedisTask *redisTask = WFTaskFactory::create_redis_task(
        "redis://:tiger@8.137.12.216:6379", 0, nullptr);
    string fileHash = uploadId.substr(uploadId.find("_") + 1);
    redisTask->get_req()->set_request("SADD", {fileHash, std::to_string(chunkId)});
    // 4. 保存分片数据到本地
    SeriesWork *series = Workflow::create_series_work(redisTask, nullptr);
    body = (char *)malloc(bodyStr.length());
    memcpy(body, bodyStr.c_str(), bodyStr.length());
    WFFileIOTask *pwriteTask = WFTaskFactory::create_pwrite_task(
        (_fileDir + chunkHash).c_str(), body, strlen(body), 0, [](WFFileIOTask *task) {
        if (task->get_state()) {
            cout << "sys error" << strerror(task->get_error()) << endl;
        }
        cout << "write success" << endl;
    });
    series->push_back(pwriteTask);
    series->start();
    // 5. 存入数据库（文件子表）----暂时不做 
    // 6. 返回响应
    nlohmann::json respJson;
    respJson["status"] = true;
    respJson["data"] = "success";
    _httpTask->get_resp()->append_output_body(respJson.dump());
    cout << "uppart" << endl;
}

// /file/mupload/complete 查询是否上传完成
void FragmentUpload::complete() {
    // 1. 从头部取出请求参数
    protocol::HttpRequest *req = _httpTask->get_req();
    string url(req->get_request_uri());
    string uploadId = url.substr(url.find('=') + 1);
    cout << "uploadId = " << uploadId << endl;
    // 2. 查询redis判断是否上传完成
    Redis redis("tcp://8.137.12.216:6379");
    redis.auth("tiger");
    string totalCount = *redis.hget(uploadId, "chunkCount"); 
    string fileHash = uploadId.substr(uploadId.find("_") + 1);
    int uploadedCount= redis.scard(fileHash);
    // 3. 若已完成，更新数据库（文件主表、用户-文件表、文件子表）----暂时不做
    // 4. 返回响应
    nlohmann::json respJson;
    respJson["status"] = true;
    respJson["data"] = uploadedCount == std::stoi(totalCount) ? "yes" : "no";
    _httpTask->get_resp()->append_output_body(respJson.dump());
}



/**
 * 信号处理函数
*/
WFFacilities::WaitGroup gWaitGroup(1);
void handler(int signum) {
    cout << "signal: " << signum << endl;   
    gWaitGroup.done();
}

/**
 * @brief 业务分发函数
*/
void process(WFHttpTask *httpTask) {
    FragmentUpload fragmentUpload(httpTask);
    protocol::HttpRequest *req = httpTask->get_req();
    string url(req->get_request_uri());
    url = url.substr(0, url.find("?"));
    cout << "url = " << url << endl;
    if (url == "/file/mupload/init") {
        fragmentUpload.init();
    } else if (url == "/file/mupload/uppart") {
        fragmentUpload.uppart();
    } else if (url == "/file/mupload/complete") {
        fragmentUpload.complete();
    }
}

/**
 * @brief 服务端测试函数
*/
void test0() {
    signal(SIGINT, handler);
    WFHttpServer server(process);
    server.start(8888);
    gWaitGroup.wait();
    server.stop();
}

int main(void) {
    auto begin = std::chrono::high_resolution_clock::now();
    test0();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

