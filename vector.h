#ifndef VECTOR_H
#define VECTOR_H
#include "main.h"

class Solution1 {
public:

    // vector 6
    int trap(vector<int>& height) {
        int len = height.size();
        int left(0);
        int right = len-1;
        int ans(0);
        int leftMax=0,rightMax=0;
        while(left < right){
            leftMax = max(leftMax,height[left]);
            rightMax = max(rightMax,height[right]);
            if(height[left]<height[right]){
                ans+=leftMax-height[left];
                ++left;
            } else{
                ans+=rightMax - height[right];
                --right;
            }
        }
        return ans;
    }

    // vector 5
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        deque<int> q;
        for(int i =0;i<k;++i){
            while(!q.empty() && nums[i] > nums[q.back()] ){
                q.pop_back();
            }
            q.push_back(i);
        }

        vector<int> ans = {nums[q.front()]};

        for(int i = k; k < n-k+1; ++i){
            while(!q.empty() && nums[i] > nums[q.back()] ){
                q.pop_back();
            }
            q.push_back(i);

            while(q.front() <= i-k){
                q.pop_front();
            }
            ans.push_back(nums[q.front()]);
        }
        return ans;
    }

    // vector 4
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> value_key;
        int max = nums.size();

        for(int i=0;i<max;++i){
            if(value_key.find(target-nums[i]) != value_key.end())
                return {value_key[target-nums[i]] , i};
            value_key[nums[i]]=i;

        }
        return {};
    }
    // vector 3
    void moveZeroes(vector<int>& nums) {
        int left(0);
        int right(0);
        int max = (int)nums.size();

        while(right<max){
            if(nums[right]){
                swap(nums[right],nums[left]);
                left++;
            }
            ++right;
        }
    }

    // vector 2
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(),nums.end());
        vector<vector<int>> ans;

        for(int first=0;first<n;++first){
            if(first >0 && nums[first] == nums[first-1])
                continue;
            int target = -nums[first];
            int third = n-1;
            for(int second=first+1; second<n; ++second){
                if(second > first+1 && nums[second] == nums[second-1])
                    continue;
                while(second < third && nums[second] + nums[third] > target)
                    --third;
                if(second == third)
                    break;
                if(nums[second] + nums[third] == target)
                    ans.push_back({nums[first],nums[second],nums[third]});
            }
        }
        return ans;
    }
    // vector 1
    int subarraySum(vector<int>& nums, int k) {
        int len = nums.size();
        int ans(0);
        for(int start=0;start<len;++start) {
            int sum = 0;
            for(int end = start; end >=0; --end ) {
                sum += nums[end];
                if(sum == k){
                    ++ans;
                }
            }
        }
        return ans;
    }
    // vector 1.1
    int subarraySum1(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        mp[0] = 1;
        int count = 0, pre = 0;
        for (auto& x:nums) {
            pre += x;
            if (mp.find(pre - k) != mp.end()) {
                count += mp[pre - k];
            }
            mp[pre]++;
        }
        return count;
    }
};


#endif // VECTOR_H
