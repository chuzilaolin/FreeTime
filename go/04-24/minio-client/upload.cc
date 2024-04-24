#include <cstdlib>
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


void test0() {
    string objectName = "Snipaste_2024-04-24_16-53-48.png";
    string filepath = "~/FreeTime/go/04-24/minio-client/Snipaste_2024-04-24_16-53-48.png";
    system(("./uploadToMinIO " +  objectName + " " + filepath).c_str()); 
}

int main(void) {
    auto begin = std::chrono::high_resolution_clock::now();
    test0();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

