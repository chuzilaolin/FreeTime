#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <regex>
#include <fstream>
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

struct RssItem
{
    string title;
    string link;
    string description;
    string content;
    RssItem();
    RssItem(string title, string link, string description, string content);
};
RssItem::RssItem() {}
RssItem::RssItem(string title, string link, string description, string content) 
: title(title)
, link(link)
, description(description)
, content(content)
{}

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
    // 打开xml
    XMLDocument doc;
    doc.LoadFile(filename.c_str());
    if (doc.ErrorID()) {
        cerr << "load file fail" << endl;
        return;
    }
    // 开始读取文件
    XMLElement *itemNode = doc.FirstChildElement("rss")->FirstChildElement("channel")->FirstChildElement("item");
    while (itemNode) {
        // 获取数据
        string title = itemNode->FirstChildElement("title")->GetText();
        string link = itemNode->FirstChildElement("link")->GetText();
        string description = itemNode->FirstChildElement("description")->GetText();
        string content = itemNode->FirstChildElement("content:encoded")->GetText();
        // 处理html标签
        regex reg("<[^>]*>");
        description = regex_replace(description, reg, "");
        content = regex_replace(content, reg, "");
        // 存入vector
        RssItem rssItem(title, link, description, content);
        _rss.push_back(rssItem);
        // 下一个结点
        itemNode = itemNode->NextSiblingElement("item");
    }
}

void RssReader::dump(const string &filename) {
    ofstream ofs(filename);
    if (!ofs) {
        cerr << "open file is error" << endl;
        return; 
    }
    int idx = 0;
    for (const RssItem &item : _rss) {
        ofs << "<doc><docid>" << ++idx
            << "</docid><title>" << item.title
            << "</title><link>" << item.link
            << "</link><description>" << item.description
            << "</description><content>" << item.content
            << "</content></doc>" << endl;
    }
    ofs.close();
}


void test0() {
    RssReader rr(4000);
    rr.parseRss("./coolshell.xml");
    rr.dump("./pagelib.dat");
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

