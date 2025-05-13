#include "pub.h"

/* test 1 ******* 3.无重复字符的最长子串长度 **********/
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

/* test 2 ******* 438.找到字符串中所有字母异位词 **********/
//vector<int> findAnagrams(string s, string p) {  //自己想的，复杂度超了
//    int sLen = s.size();
//    int pLen = p.size();
//    vector<int> res;
//    sort(p.begin(), p.end());
//    for(int i = 0; i<=sLen - pLen;++i){
//        if(p.find(s[i]) == string::npos)
//            continue;
//        string tmp = s.substr(i,pLen);
//        sort(tmp.begin(),tmp.end());
//        if(p == tmp)
//            res.push_back(i);
//    }
//    return res;
//}
vector<int> findAnagrams(string s, string p) {
    int sLen = s.size();
    int pLen = p.size();
    if(pLen > sLen){
        return {};
    }
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

