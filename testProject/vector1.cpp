#include "pub.h"

/* 哈希1 ****************** 1.两数之和 *************************/
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
TEST(vector_test, twoSum){
    vector<int> vec={1,2,3,4,5};
    vector<int> res = twoSum(vec,9);
    vector<int> rightResult = {3,4};
    EXPECT_EQ(res , rightResult);
}

/* 哈希2 ****************** 49.字母异位词分组 *************************/
//给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string,vector<string>> mp;
    for(auto& str : strs){
        string tmp = str;
        sort(tmp.begin(),tmp.end());
        mp[tmp].emplace_back(str);
    }
    vector<vector<string>> res;
    for(auto& it : mp){
        res.emplace_back(it.second);
    }
    return res;
}
TEST(vector_test, groupAnagrams){
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> res = groupAnagrams(strs);
    vector<vector<string>> right = {{"bat"},{"tan","nat"},{"eat","tea","ate"}};
    EXPECT_EQ(res, right);
}
/* 哈希3 ****************** 128.最长连续序列 *************************/
//给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。
int longestConsecutive(vector<int>& nums) {
    unordered_set<int> all;
    for(auto &n: nums){
        all.emplace(n);
    }
    int maxSequence(0);
    for(auto &per : all){
        if(!all.count(per-1)){
            int perSequence(0);
            int tmp = per;
            while(all.count(tmp++)){
                ++perSequence;
            }
            maxSequence = max(maxSequence,perSequence);
        }
    }
    return maxSequence;
}
TEST(vector_test, longestConsecutive){
    vector<int> nums = {100,4,200,1,3,2};
    int res = longestConsecutive(nums);
    EXPECT_EQ(res, 4);
}
/* 双指针1 ****************** 283.移动零 *************************/
//给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
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
TEST(vector_test, moveZeroes){
    vector<int> in = {1,0,3,0,5};
    moveZeroes(in);
    vector<int> rightResult = {1,3,5,0,0};
    EXPECT_EQ(in , rightResult);
}
/* 双指针2 ****************** 11.盛最多水的容器 *************************/
// 给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。
// 找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
// 返回容器可以储存的最大水量。
int maxArea(vector<int>& height) {
    int left(0);
    int right = height.size()-1;
    int maxValue(0);
    while(left < right){
        int minY = min(height[left], height[right]);
        int curValue = minY * (right - left);
        maxValue = max(maxValue,curValue);
        if(height[left] < height[right])
            left++;
        else
            right--;
    }
    return maxValue;
}
TEST(vector_test, maxArea){
    vector<int> nums = {1,8,6,2,5,4,8,3,7};
    int res = maxArea(nums);
    EXPECT_EQ(res, 49);
}
/* 双指针3 ****************** 15.三树之和 *************************/
// 判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，
// 同时还满足 nums[i] + nums[j] + nums[k] == 0 。请你返回所有和为 0 且不重复的三元组。
vector<vector<int>> threeSum(vector<int>& nums) {
    int n = nums.size();
    std::sort(nums.begin(),nums.end());
    vector<vector<int>> ans;

    for(int first=0;first<n;++first){
        if(first > 0 && nums[first] == nums[first-1])
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
TEST(vector_test, threeSum){
    vector<int> vec={-1,0,1,2,-1,-4};
    vector<vector<int>> res = threeSum(vec);
    vector<vector<int>> rightResult = {{-1,-1,2},{-1,0,1}};
    EXPECT_EQ(res , rightResult);
}
/* 双指针4 ****************** 42.接雨水 *************************/
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
TEST(vector_test, trap){
    vector<int> vec={0,1,0,2,1,0,1,3,2,1,2,1};
    EXPECT_EQ(trap(vec), 6);
}
/*  ****************** 121. 买卖股票的最佳时机 *************************/
int maxProfit(vector<int>& prices) {
    if(prices.empty())
        return 0;
    int minPrice = prices[0];
    int maxMoney = 0;
    int size = prices.size();
    for(int i=0; i<size; ++i){
        if(prices[i]<minPrice)
            minPrice = prices[i];
        maxMoney = max(maxMoney, prices[i] - minPrice);
    }
    return maxMoney;
}
TEST(vector_test, maxProfit){
    vector<int> vec={7,1,5,3,6,4};
    EXPECT_EQ(maxProfit(vec), 5);
}

/* 子串1 ****************** 560.和为k的子数组 *************************/
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
TEST(vector_test, subarraySum){
    vector<int> vec1={6,4,3,1};
    int res1 = subarraySum(vec1,10);
    EXPECT_EQ(res1, 1);

    vector<int> vec2={1,1,1};
    int res2 = subarraySum(vec2,2);
    EXPECT_EQ(res2, 2);
}
/* 子串2 ****************** 239.滑动窗口最大值 *************************/
// 给你一个整数数组nums，有一个大小为k的滑动窗口从数组的最左侧移动到数组的最右侧。
// 你只可以看到在滑动窗口内的k个数字。滑动窗口每次只向右移动一位。返回滑动窗口中的最大值.
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    int n = nums.size();
    deque<int> q;
    for(int i = 0; i < k; ++i){
        while(!q.empty() && nums[i] > nums[q.back()] ){ //新的大于已有的，就移除已有的
            q.pop_back();
        }
        q.push_back(i); //新的小于已有的，继续添加
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
TEST(vector_test, maxSlidingWindow){
    vector<int> vec={1,3,-1,-3,5,3,6,7};
    vector<int> res = maxSlidingWindow(vec,3);
    pVector(res,"maxSlidingWindow");
    vector<int> rightResult = {3,3,5,5,6,7};
    EXPECT_EQ(res , rightResult);
}

/* 普通数组1 ****************** 53.最大子数组和 *************************/
// 给你一个整数数组nums，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
int maxSubArray(vector<int>& nums) {
    int pre(0);
    int ans = nums[0];
    for(auto &n : nums){
        pre = max(n,n+pre);
        ans = max(pre, ans);
    }
    return ans;
}
TEST(vector_test, maxSubArray){
    vector<int> vec={-2,1,-3,4,-1,2,1,-5,4};
    EXPECT_EQ(maxSubArray(vec) , 6);
}
/* 普通数组2 ****************** 56.合并区间 *************************/
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    int size = intervals.size();
    if(size == 0){
        return {};
    }
    sort(intervals.begin(),intervals.end());

    vector<vector<int>> res;
    res.push_back(intervals[0]);
    for(int i = 1; i < size; ++i){
        int L = intervals[i][0], R = intervals[i][1];
        if(res.back()[1] >= L){
            res.back()[1] = max(R, res.back()[1]);
        }else {
            res.push_back(intervals[i]);
        }
    }
    return res;
}
TEST(vector_test, merge){
    vector<vector<int>> vec={{1,3},{2,6},{8,10},{15,18}};
    vector<vector<int>> rightResult={{1,6},{8,10},{15,18}};
    EXPECT_EQ(merge(vec) , rightResult);
}
/* 普通数组5 ****************** 41.缺失的第一个正数 *************************/
//给你一个未排序的整数数组 nums ，请你找出其中没有出现的最小的正整数。
//请你实现时间复杂度为 O(n) 并且只使用常数级别额外空间的解决方案。
int firstMissingPositive(vector<int>& nums) {
    int size = nums.size();
    for(int i = 0; i<size; ++i){
        while( (nums[i]>0)&& (nums[i] < size) && (nums[nums[i]-1] != nums[i]) ){
            swap(nums[i], nums[nums[i]-1]);
        }
    }
    for(int i=0; i<size; ++i){
        if(i != nums[i]-1){
            return i+1;
        }
    }
    return size+1;
}
TEST(vector_test, firstMissingPositive){
    vector<int> vec={3,2,-1,1};
    EXPECT_EQ(firstMissingPositive(vec) , 4);
    vector<int> vec1={3,4,-1,1};
    EXPECT_EQ(firstMissingPositive(vec1) , 2);
    vector<int> vec2={1,2,6,3,5,4};
    EXPECT_EQ(firstMissingPositive(vec2) , 7);

}
/* 矩阵1 ****************** 73.矩阵置零 *************************/
void setZeroes(vector<vector<int>>& matrix) {
    vector<int> xZeros;
    vector<int> yZeros;
    int ySize = matrix.size();
    int xSize = matrix[0].size();
    for(int y=0; y<ySize; ++y){
        for(int x=0; x<xSize; ++x){
            if(matrix[y][x] == 0){
                yZeros.push_back(y);
                xZeros.push_back(x);
            }
        }
    }
    for(int y=0; y<ySize; ++y){
        if(yZeros.end() != std::find(yZeros.begin(),yZeros.end(),y)){
            for(int x=0; x<xSize; ++x){
                matrix[y][x] = 0;
            }
        }else{
            for(int x=0; x<xSize; ++x){
                if(xZeros.end() != std::find(xZeros.begin(),xZeros.end(),x)){
                    matrix[y][x] = 0;
                }
            }
        }
    }
}
TEST(vector_test, setZeroes){
    vector<vector<int>> vec{{1,1,1},{1,0,1},{1,1,1}};
    vector<vector<int>> rightResult={{1,0,1},{0,0,0},{1,0,1}};
    setZeroes(vec);
    EXPECT_EQ(vec , rightResult);

}
