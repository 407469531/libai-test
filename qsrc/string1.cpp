#include "string1.h"

/********无重复字符的最长子串长度**********/
int lengthOfLongestSubstring(string& s) {
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

/*********************测试例子构造***********************/
int lengthOfLongestSubstringTest(string s1){
    int len = lengthOfLongestSubstring(s1);
    printf("%s lengthOfLongestSubstring result:%d \n",s1.c_str(),len);
    return len;
}

TEST(stringtest, lengthOfLongestSubstring) {
    //    string s1="pwwkew";
    //    string s1="aab";
    //    string s1="dvdf";
    //    string s1="asjrgapa";
    EXPECT_EQ(6,lengthOfLongestSubstringTest("asjrgapa"));
}
