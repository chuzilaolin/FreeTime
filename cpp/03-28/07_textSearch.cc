#include <cctype>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <unordered_map>
#include <fstream>
#include <sstream>

using namespace std;

class Dictionary {
public:
    void read(const string &filename);
    void store(const string &filename);
private:
    unordered_map<string, size_t> _dict;
};

void Dictionary::read(const string &filename) {
    // 打开文件
    ifstream ifs(filename);
    if (!ifs) {
        ifs.close();
        cout << "open " << filename << " is fail!" << endl; 
        return;
    }
    // 处理数据 
    string line;
    while (getline(ifs, line)) {
        string word;
        stringstream ss(line);
        // 一行一行处理
        while (getline(ss, word, ' ')) {
            word.erase(remove_if(word.begin(), word.end(), [](const char c) {
                return !isalpha(c);
            }), word.end());     
            if (word.size() == 0) {
                continue; // 不加入空字符
            }         
            ++_dict[word];
        }
        
    }
    // 关闭文件
    ifs.close();
}

void Dictionary::store(const string &filename) {
    ofstream ofs(filename);
    if (!ofs) {
        ofs.close();
        cout << "open " << filename << " is fail!" << endl; 
        return;
    }
    // 排序
    vector <pair<string,int>> sortData(_dict.begin(), _dict.end());
    sort(sortData.begin(), sortData.end(), [](const pair<string,int> &p1, const pair<string,int> &p2){
            return p1.second > p2.second;
         });
    // 输出到文件
    for (const auto &it : sortData) {
        ofs << it.first << " " << it.second << endl;
    }
    ofs.close();
}



void test0() {
    Dictionary dict;
    dict.read("../../The_Holy_Bible.txt");
    dict.store("store2.txt");
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

