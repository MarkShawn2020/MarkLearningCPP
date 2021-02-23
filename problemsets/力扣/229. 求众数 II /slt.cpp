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

    int addEle(int vals[], int cnts[], int num, const int K)
    {
        for(int i=0; i<K; i++)
            if(num == vals[i])
                return cnts[i]++;

        for(int i=0; i<K; i++)
            if(cnts[i] == 0)
                return vals[i] = num, cnts[i]++;

        for(int i=0; i<K; i++)
            cnts[i]--;

        return 0;
    }


    vector<int> majorityElement(vector<int>& nums) {

        const int K = 2;
        int vals[K] = {INT_MIN, INT_MIN};
        int cnts[K] = {0, 0};

        for(int num:nums)
            addEle(vals, cnts, num, K);

        vector<int> ans;
        for(int & val : vals)
        {
            int k = 0;
            for(int num: nums)
                k += num == val;
            if(k * 3 > nums.size())
                ans.emplace_back(val);
        }

        return ans;
    }
};

int main()
{
    Solution slt;
//    vector<int> data ={1, 2, 3, 4, 3, 1, 3, 1, 2, 1};
    vector<int> data ={2, 1, 1, 5, 6};
    for(int item: slt.majorityElement(data))
        cout << item << '\t';
}