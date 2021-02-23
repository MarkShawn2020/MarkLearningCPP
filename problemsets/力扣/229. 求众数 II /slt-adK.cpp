//
// Created by 南川 on 2021/1/25.
//
#include "climits"
#include "vector"
#include "string"
#include "iostream"
#include "unordered_map"
using namespace std;


class Solution {
public:

    void addEle_K(vector<int> & vals, vector<int> & cnts, int num, int n, int k)
    {
        for(int i=0; i<n; i++)
            cnts[i]--;

        for(int i=0; i<n; i++)
            if(num == vals[i] || vals[i] == INT_MIN)
            {
                vals[i] = num;
                cnts[i] += k + 1;
                return;
            }

        int min_i, min_v = INT_MAX;
        for(int i=0; i<n; i++)
            if(cnts[i] < min_v)
                min_v = cnts[i], min_i = i;
        if(min_v <= 0)
            vals[min_i] = num, cnts[min_i] += k;
    }

    vector<int> majorityElement(vector<int>& nums) {
        vector<int> ans;

        const int K = 2;
        const int N = 4;
        vector<int> vals(N, INT_MIN);
        vector<int> cnts(N, 0);

        for(int num:nums)
            addEle_K(vals, cnts, num, N, K);

        for(int i=0; i<N; i++)
            if(cnts[i] > 0)
                ans.emplace_back(vals[i]);

        return ans;
    }
};

int main()
{
    Solution slt;
//    vector<int> data ={1, 2, 3, 4, 3, 1, 3, 1, 2, 1};
    vector<int> data ={2, 1, 1, 3, 1, 4, 5, 6};
    for(int item: slt.majorityElement(data))
        cout << item << '\t';
}