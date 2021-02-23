//
// Created by 南川 on 2021/1/8.
//


class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int N = nums.size();
        int K = k % N;
        int cur, pivot, next;
        vector<bool> moved(K, false);

        if(K == 0) return;

        for(int offset=0; offset<K; offset++)
        {
            if(!moved[offset])
            {
                pivot = nums[offset];
                cur = offset;
                next = (cur-K+N) % N;
                // cout << "offset: " << offset << endl;
                while(next!=offset){
                    nums[cur] = nums[next];
                    if(cur<K) moved[cur] = true;
                    cur = next;
                    next = (next-K+N) % N;
                }
                nums[cur] = pivot;
            }
        }
    }
};