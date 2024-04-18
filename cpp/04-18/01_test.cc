#include "wfrest/HttpServer.h"
using namespace wfrest;

int main(int argc, char **argv)
{
    HttpServer svr;
    svr.GET("/https", [](const HttpReq *req, HttpResp *resp)
    {
        resp->String("Test Https\n");
    });

    if (svr.start(8888) == 0)
    {
        getchar();
        svr.stop();
    } else
    {
        fprintf(stderr, "Cannot start server\n");
        exit(1);
    }
    return 0;
}
