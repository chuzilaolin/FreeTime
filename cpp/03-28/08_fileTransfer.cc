#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <sstream>

using namespace std;

const static string transferRuleFileName = "map.txt";

class FileTransfer {
public:
    FileTransfer(string ruleFileName = transferRuleFileName);
    void transfer(string sourceFileName, string targetFileName);
private:
    map<string, string> _rules; // 转换规则
};

FileTransfer::FileTransfer(string ruleFileName) {
    ifstream ifs(ruleFileName); 
    if (!ifs) {
        ifs.close();
        cerr << "open " << ruleFileName << " is fail!" << endl; 
        return;
    }
    string line;
    while (getline(ifs, line)) {
        stringstream ss(line);
        string key;
        getline(ss, key, ' ');
        string value;
        getline(ss, value);
        _rules[key] = value;
    }
    ifs.close();
}
void FileTransfer::transfer(string sourceFileName, string targetFileName) {
    // 打开文件
    ifstream ifs(sourceFileName);
    if (!ifs) {
        ifs.close();
        cerr << "open " << sourceFileName << " is fail!" << endl; 
        return;
    }
    ofstream ofs(targetFileName);
    if (!ofs) {
        ifs.close();
        ofs.close();
        cerr << "open " << targetFileName << " is fail!" << endl; 
        return;
    }
    // 转换
    string inLine;
    while (getline(ifs, inLine)) {
        stringstream in(inLine);
        string word;
        while(getline(in, word, ' ')) {
            map<string, string>::iterator it = _rules.find(word); 
            if (it != _rules.end()) {
                word = it->second;
            } 
            ofs << word << " ";
        }
        ofs  << endl; 
    }
    // 关闭
    ifs.close();
    ofs.close();
}


void test0() {
    FileTransfer ft;
    ft.transfer("file.txt", "result.txt");
}

void test1() {
    string word;
    stringstream ss;
    ss << "nihao" << endl;
    ss >> word;
    cout << "word:" << word << endl;
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    /* test1(); */
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

