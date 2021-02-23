//
// Created by 南川 on 2021/1/8.
//


class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int N = nums.size();
        int K = k % N;
        int cur, pivot, next;

        if(K == 0) return;

        for(int offset=0; offset<gcd(K, N); offset++)
        {
            pivot = nums[offset];
            cur = offset;
            next = (cur-K+N) % N;

            while(next!=offset){
                nums[cur] = nums[next];
                cur = next;
                next = (next-K+N) % N;
            }
            nums[cur] = pivot;

        }
    }
};