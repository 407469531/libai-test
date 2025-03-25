#ifndef PUB_H
#define PUB_H
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <vector>
#include <algorithm>
#include <list>

#include <gtest.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void pVector(vector<int>& vs,string name="");
void pList(ListNode* in,string name="");
#endif // MAIN_H
