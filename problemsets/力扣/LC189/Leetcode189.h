//
// Created by 南川 on 2021/1/8.
//

#ifndef MARKLEARNINGCPP_LEETCODE189_H
#define MARKLEARNINGCPP_LEETCODE189_H
#include "vector"
using namespace std;


class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int temp;
        int N = nums.size();
        int K = k % N;
        for(int offset=0; offset<K; offset++)
        {
            for(int i=0; i*K+offset<N; i++)
            {
                temp = nums[i+offset];
                nums[i+offset] = nums[(i+offset-K)%N];
            }
        }
    }
};


#endif //MARKLEARNINGCPP_LEETCODE189_H
