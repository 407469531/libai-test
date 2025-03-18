#include "string1.h"
/*********************测试例子构造***********************/

void lengthOfLongestSubstringTest(){
    Solution3 so;
//    string s1="pwwkew";
//    string s1="aab";
//    string s1="dvdf";
    string s1="asjrgapa";
    so.lengthOfLongestSubstring(s1);
}

// string test enter
void stringtest(){
    lengthOfLongestSubstringTest();
}
/********无重复字符的最长子串**********/
int Solution3::lengthOfLongestSubstring(string& s) {
    int tmpMax(0);
    int len = s.size();
    unordered_set<char> have;
    int ri = -1;
    for(int i = 0; i < len; ++i){
        if(i != 0)
            have.erase(s[i-1]);
        while(ri+1<len && !have.count(s[ri+1])){
            have.insert(s[ri+1]);
            ++ri;
        }
        tmpMax=max(tmpMax,ri-i+1);
    }
    return tmpMax;
}
