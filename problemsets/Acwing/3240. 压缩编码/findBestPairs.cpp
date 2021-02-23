
//
// Created by 南川 on 2021/2/21.
//
#include "vector"
#include "iostream"
#include "cstdio"
#include "algorithm"
using namespace std;


// 第h层的结点需要结 k 对，它们的权重为h；当k==0时，所有的结点权重均为h-1
int findBestPairs(int nums[], int s, int t, int k, int h)
{
    int sum  = 0, min_v = 1e9, min_i = 0;
    if(k == 0) {for(int i=s; i<=t; ++i) sum += (h - 1) * nums[i]; return sum;}
    for(int i=s; i <= t - 2 * k; ++i)
    {
        int new_v = (h - 1) * sum + h * (nums[i] + nums[i + 1]) + findBestPairs(nums, i + 2, t, k - 1, h);
        sum += nums[i];
        if(new_v < min_v) min_v = new_v, min_i = i;
    }
//    printf("k: %d, s: %d, i: %d, (%2d, %2d) r: %d\n", k, s, min_i, nums[min_i], nums[min_i + 1], min_v);
    return min_v;
}


int main()
{
    int k = 2;
    int h = 4;
    int n = 10;
    int nums[] = {11, 17, 4, 13, 18, 14, 18, 15, 9, 5};
    int ans = findBestPairs(nums, 0, 10, k, h);
    cout << "Ans: " << ans;
}