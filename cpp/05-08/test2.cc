#include <iostream>
#include <queue>
#include <string>

class TestClass {
public:
  void runPriorityQueueTest() {
    auto compareCacheData = [](const std::pair<std::string, std::string>& data1,
                               const std::pair<std::string, std::string>& data2) {
      // 根据词频进行降序排序
      return data1.second < data2.second;
    };

    std::priority_queue<std::pair<std::string, std::string>,
                        std::vector<std::pair<std::string, std::string>>,
                        decltype(compareCacheData)>
        pq(compareCacheData);

    // 添加测试数据
    pq.push(std::make_pair("apple", "3"));
    pq.push(std::make_pair("banana", "2"));
    pq.push(std::make_pair("orange", "5"));
    pq.push(std::make_pair("grape", "1"));
    pq.push(std::make_pair("kiwi", "4"));

    // 输出优先队列中的元素
    while (!pq.empty()) {
      const std::pair<std::string, std::string>& topData = pq.top();
      std::cout << "Word: " << topData.first << ", Frequency: " << topData.second << std::endl;
      pq.pop();
    }
  }
};

int main() {
  TestClass test;
  test.runPriorityQueueTest();

  return 0;
}
