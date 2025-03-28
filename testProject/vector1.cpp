#include "pub.h"

/* test 1 ****************** 42.接雨水 *************************/
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

/* test 2 ****************** 239.滑动窗空最大值 *************************/
// 给你一个整数数组nums，有一个大小为k的滑动窗口从数组的最左侧移动到数组的最右侧。
// 你只可以看到在滑动窗口内的k个数字。滑动窗口每次只向右移动一位。返回滑动窗口中的最大值.
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

/* test 3 ****************** 1.两数之和 *************************/
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
/* test 4 ****************** 283.移动零 *************************/
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
/* test 5 ****************** 15.三树之和 *************************/
// 判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，
// 同时还满足 nums[i] + nums[j] + nums[k] == 0 。请你返回所有和为 0 且不重复的三元组。
vector<vector<int>> threeSum(vector<int>& nums) {
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
/* test 6 ****************** 560.和为k的子数组 *************************/
// 给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k 的子数组的个数 。
// 子数组是数组中元素的连续非空序列。
int subarraySum(vector<int>& nums, int k) {
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
/*********************测试例子构造***********************/
TEST(vector_test, test1_trap){
    vector<int> vec={0,1,0,2,1,0,1,3,2,1,2,1};
    EXPECT_EQ(trap(vec), 6);
}

TEST(vector_test, test2_maxSlidingWindow){
    vector<int> vec={1,3,-1,-3,5,3,6,7};
    vector<int> res = maxSlidingWindow(vec,3);
    pVector(res,"maxSlidingWindow");
    vector<int> rightResult = {3,3,5,5,6,7};
    EXPECT_EQ(res , rightResult);
}

TEST(vector_test, test3_twoSum){
    vector<int> vec={1,2,3,4,5};
    vector<int> res = twoSum(vec,9);
    vector<int> rightResult = {3,4};
    EXPECT_EQ(res , rightResult);
}

TEST(vector_test, test4_moveZeroes){
    vector<int> in = {1,0,3,0,5};
    moveZeroes(in);
    vector<int> rightResult = {1,3,5,0,0};
    EXPECT_EQ(in , rightResult);
}

TEST(vector_test, test5_threeSum){
    vector<int> vec={-1,0,1,2,-1,-4};
    vector<vector<int>> res = threeSum(vec);
    vector<vector<int>> rightResult = {{-1,-1,2},{-1,0,1}};
    EXPECT_EQ(res , rightResult);
}

TEST(vector_test, test6_subarraySum){
    vector<int> vec1={6,4,3,1};
    int res1 = subarraySum(vec1,10);
    EXPECT_EQ(res1, 1);

    vector<int> vec2={1,1,1};
    int res2 = subarraySum(vec2,2);
    EXPECT_EQ(res2, 2);
}

