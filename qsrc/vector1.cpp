#include "vector1.h"


void trapTest(){
    Solution1 so;

    vector<int> vec6={0,1,0,2,1,0,1,3,2,1,2,1};
    int res = so.trap(vec6);
    printf("trap:%d \n",res);
}

void maxSlidingWindowTest(){
    Solution1 so;

    vector<int> vec5={1,3,-1,-3,5,3,6,7};
    vector<int> res = so.maxSlidingWindow(vec5,3);
    pVector(res,"maxSlidingWindow");

}

void threeSumTest(){
    Solution1 so;
    vector<int> vec3={-1,0,1,2,-1,-4};
    vector<vector<int>> r3 = so.threeSum(vec3);
}

void twoSumTest(){
    Solution1 so;
    vector<int> vec1={1,2,3,4,5};
    vector<int> res = so.twoSum(vec1,9);
    pVector(res,"twoSum");
}

void moveZeroesTest(){
    Solution1 so;
    vector<int> vec2={1,0,3,0,5};
    so.moveZeroes(vec2);
    pVector(vec2,"moveZeroes");

}

void subarraySumTest(){
    Solution1 so;

//    vector<int> vec4={6,4,3,1};
//    so.subarraySum(vec4,10);

    vector<int> vec1_1={1,1,1};
    so.subarraySum1(vec1_1,2);
}

void vectortest(){
    trapTest();
    maxSlidingWindowTest();
    twoSumTest();
    threeSumTest();
    moveZeroesTest();
}

/******************* 42.接雨水 *************************/
int Solution1::trap(vector<int>& height) {
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

/******************* 239.滑动窗空最大值 *************************/
// 给你一个整数数组nums，有一个大小为k的滑动窗口从数组的最左侧移动到数组的最右侧。
// 你只可以看到在滑动窗口内的k个数字。滑动窗口每次只向右移动一位。返回滑动窗口中的最大值.
vector<int> Solution1::maxSlidingWindow(vector<int>& nums, int k) {
    int n = nums.size();
    deque<int> q;
    for(int i =0;i<k;++i){
        while(!q.empty() && nums[i] > nums[q.back()] ){
            q.pop_back();
        }
        q.push_back(i);
    }

    vector<int> ans = {nums[q.front()]};

    for(int i = k; i < n; ++i){
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

/******************* 1.两数之和 *************************/
vector<int> Solution1::twoSum(vector<int>& nums, int target) {
    unordered_map<int,int> value_key;
    int max = nums.size();

    for(int i=0;i<max;++i){
        if(value_key.find(target-nums[i]) != value_key.end())
            return {value_key[target-nums[i]] , i};
        value_key[nums[i]]=i;

    }
    return {};
}
/******************* 283.移动零 *************************/
void Solution1::moveZeroes(vector<int>& nums) {
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
/******************* 15.三树之和 *************************/
vector<vector<int>> Solution1::threeSum(vector<int>& nums) {
    int n = nums.size();
    std::sort(nums.begin(),nums.end());
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
/******************* 560.和为k的子数组 1 *************************/
int Solution1::subarraySum(vector<int>& nums, int k) {
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
/******************* 560.和为k的子数组 2 *************************/
int Solution1::subarraySum1(vector<int>& nums, int k) {
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
