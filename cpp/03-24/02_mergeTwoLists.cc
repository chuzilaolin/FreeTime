#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <leetcode.h>

using namespace std;

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // 处理特殊情况
        if (list1 == nullptr) {
            return list2;
        }
        if (list2 == nullptr) {
            return list1;
        }       
        // 合并链表
        ListNode *head = list1->val < list2->val ? list1 : list2;
        ListNode *p = head;
        ListNode *p1 = head == list1 ? list1->next : list1;
        ListNode *p2 = head == list2 ? list2->next : list2;
        while (p1 != nullptr && p2 != nullptr) {
            if (p1->val < p2->val) {
                p->next = p1;
                p1 = p1->next;
            }else {
                p->next = p2;
                p2 = p2->next;
            }
            p = p->next;
        }
        // concat residual node
        p->next = p1 != nullptr ? p1 : p2;
        return head;
    }
};

void test0 () {
    
}

int main(void) {
    auto begin = chrono::high_resolution_clock::now();
    test0();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end -begin);
    cout << "用时: " << duration.count() << "毫秒" << endl;
    return 0;
}

