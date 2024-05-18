#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int sharedResource = 0;

void threadFunction()
{
    std::lock_guard<std::mutex> lock(mtx);

    // 临界区代码
    for (int i = 0; i < 100000; ++i) {
        sharedResource++;
    }
}

int main()
{
    std::thread t1(threadFunction);
    std::thread t2(threadFunction);

    t1.join();
    t2.join();

    std::cout << "Shared resource value: " << sharedResource << std::endl;

    return 0;
}
