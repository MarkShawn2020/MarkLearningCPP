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

        using mypair = pair<int, int>;

        unordered_map<int, int> mp;
        for(int num: nums) ++mp[num];
        sort(mp.begin(), mp.end(), [](const mypair& a, const mypair &b){
            return b.second >= a.second;
        });
        vector<int> ans;
        auto iter = mp.begin();
        for(auto iter=mp.begin(); iter->second > nums.size() / 3.0; iter++)
            ans.emplace_back(iter->second);
        return ans;
    }
};

int main()
{
    Solution slt;
    vector<int> data ={3,2,3};
    for(int item: slt.majorityElement(data))
        cout << item << '\t';
}