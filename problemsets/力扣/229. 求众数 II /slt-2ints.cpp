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

    vector<int> majorityElement(vector<int>& nums) {
        const int K = 2;
        int vals[K], cnts[K], realCnts[K];
        fill(vals, vals+K, -1);
        fill(cnts, cnts+K, 0);
        fill(realCnts, realCnts+K, 0);

        for(int num: nums)
        {
            if(vals[0] == num)
                cnts[0] += 2, ++realCnts[0], --cnts[1];
            else if(vals[1] == num)
                cnts[1] += 2, ++realCnts[1], --cnts[0];
            else
            {
                if(--cnts[0] <= 0)
                    vals[0] = num, cnts[0] = 2, realCnts[0] = 1;
                else if(--cnts[1] <= 0)
                    vals[1] = num, cnts[1] = 2, realCnts[1] = 1;
            }
        }

        vector<int> ans;
        for(int i=0; i<2; i++)
            if(cnts[i] > 0 && realCnts[i] * 3 > nums.size())
                ans.emplace_back(vals[i]);

        return ans;
    }
};
int main()
{
    Solution slt;
    vector<int> data ={0, 3, 4, 0};
    for(int item: slt.majorityElement(data))
        cout << item << '\t';
}