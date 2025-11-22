#ifndef PUB_H
#define PUB_H

/*
          ／＞　　   フ
　　　　　|  　_　 _ |
　 　　　／; ミ＿xノ
　　 　 /　　　 　 |
　　　 /　 ヽ　　 ﾉ
　 　 │　　|　|　|
　／￣|　　 |　|　|
　| (￣ヽ＿_ヽ_)__)
　＼二つ
*/

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
#include <forward_list>
#include <stack>
#include <queue>
#include <cmath>
#include <limits.h>

#include <gtest/gtest.h>
using namespace std;

using CStr   = const char*;
using uchar  = unsigned char;
using ushort = unsigned short;
using uint   = unsigned int;
using ulong  = unsigned long;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


void pVector(vector<int>& vs,string name="");
void pVectorMatrix(vector<vector<int>> adjMat);
void pList(ListNode* in,string name="");

size_t getMemInUse();
string memStr(size_t bytes);

class MemStamp{
protected:
    size_t _startMem;
    const char* _name;
public:
    MemStamp(const char* name = NULL, bool enable = true) : _startMem(enable ? getMemInUse() : 0), _name(name){}
    ~MemStamp();
};


#endif // MAIN_H
