#include "pub.h"

/* 滑动窗口1 ******* 3.无重复字符的最长子串长度 **********/
//思路:通过把不重复的字符插入到unordered_set中，再判断新插入的字符是否在set中，从而决定插入还是移除最前面的字符
int lengthOfLongestSubstring(string s) {
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
TEST(string_test, lengthOfLongestSubstring){
    EXPECT_EQ(6,lengthOfLongestSubstring("asjrgapa"));
}
/* 滑动窗口2 ******* 438.找到字符串中所有字母异位词 **********/
//思路:通过比较两个vector，添加条件是：长度相同，vector相同。left是在长度相同时更新，right是每次遍历
vector<int> findAnagrams(string s, string p) {
    int sLen = s.size();
    int pLen = p.size();
    if(pLen > sLen)
        return {};
    vector<int> sCount(26);
    vector<int> pCount(26);
    for(auto & tmp : p){
        pCount[tmp - 'a']++;
    }
    vector<int> res;
    int left(0);
    for(int right = 0;right<sLen; ++right){
        sCount[s[right] - 'a']++;
        if(right - left + 1 == pLen){
            if(sCount == pCount)
                res.push_back(left);
            sCount[s[left]-'a']--;
            left++;
        }
    }
    return res;
}
TEST(string_test, findAnagrams){
    string s = "cbaebabacd", p = "abc";
    vector<int> rightResult = {0,6};
    EXPECT_EQ(findAnagrams(s,p) , rightResult);

    string s1 = "abab", p1 = "ab";
    vector<int> rightResult1 = {0,1,2};
    EXPECT_EQ(findAnagrams(s1,p1) , rightResult1);

    string s2 = "baa", p2 = "aa";
    vector<int> rightResult2 = {1};
    EXPECT_EQ(findAnagrams(s2,p2) , rightResult2);
}
/* 子串3 ****************** 76.最小覆盖子串 ************* o(m+n) 时间内************/
//
bool check(unordered_map<char,int> &cnt, unordered_map<char,int> &ori){
    for(auto &p : ori){
        if(p.second > cnt[p.first])
            return false;
    }
    return true;
}
string minWindow(string s, string t) {
    int sLen = s.size();
    int tLen = t.size();
    int len = INT_MAX;
    int ansL = -1;
    if(tLen > sLen)
        return "";

    unordered_map<char,int> ori,cnt;
    for(auto &c: t)
        ++ori[c];

    int l=0,r=-1;
    while(r<sLen){
        int tmpr = ++r;
        if(ori.find(s[tmpr]) != ori.end()){
            ++cnt[s[r]];
        }
        while(check(cnt, ori) && l<=r){
            if(r-l+1 < len){
                len = r-l+1;
                ansL = l;
            }
            if(ori.find(s[l]) != ori.end()){
                --cnt[s[l]];
            }
            ++l;
        }
    }
    return ansL == -1 ? "" : s.substr(ansL,len);
}
TEST(vector_test, minWindow){
    string s = "ADOBECODEBANC", t = "ABC";
    string rightResult = "BANC";
    EXPECT_EQ(minWindow(s, t) , rightResult);
}
