#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

struct RssItem
{
    string title;
    string link;
    string description;
    string content;
};

class RssReader {
public:
    RssReader(size_t size);
    void parseRss(const string &filename); // 解析
    void dump(const string &filename); // 输出
private:
    vector<RssItem> _rss;
}; 

RssReader::RssReader(size_t size) {
    _rss.reserve(size);
}

void RssReader::parseRss(const string &filename) {
    
}

void RssReader::dump(const string &filename) {

}


void test0() {

}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

