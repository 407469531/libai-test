#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include <fstream>

#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void pVector(vector<int>& vs,string name=""){
    printf("%s: ",name.c_str());
    for(auto& v: vs){
        printf("%d,",v);
    }
    printf("\n");
}
void pList(ListNode* in,string name=""){
    ListNode* tmp = in;
    printf("%s: ",name.c_str());
    while(tmp){
        printf("%d ",tmp->val);
        tmp = tmp->next;
    }
    printf("\n");
}

#endif // MAIN_H
