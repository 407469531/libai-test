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

#include <stdio.h>
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

size_t getMemInUse();
std::string memStr(size_t bytes);

class MemStamp{
protected:
    size_t _startMem;
    const char* _name;
public:
    MemStamp(const char* name = NULL, bool enable = true) : _startMem(enable ? getMemInUse() : 0), _name(name){}
    ~MemStamp();
};
