#include "string1.h"

// string 1
int Solution3::lengthOfLongestSubstring(string& s) {
    int tmpMax(0);
    int len = s.size();
    unordered_set<char> have;
    int ri = -1;
    for(int i = 0; i < len; ++i){
        if(i != 0){
            have.erase(s[i-1]);
        }

        while(ri+1<len && !have.count(s[ri+1])){
            have.insert(s[ri+1]);
            ++ri;
        }

        tmpMax=max(tmpMax,ri-i+1);
    }
    return tmpMax;
}
