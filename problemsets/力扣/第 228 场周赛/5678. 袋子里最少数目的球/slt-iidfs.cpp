//
// Created by 南川 on 2021/2/14.
//

#include "vector"
#include "functional"
#include "algorithm"
#include "iostream"
#include "sstream"
using namespace std;

vector<int> readIntVector1D(string s)
{
    vector<int> ret;

    for(char & ch: s)
        if(!isdigit(ch) && ch!='-' && ch!='+')
            ch = ' ';

    stringstream ss;
    ss << s;
    int t;
    while (ss >> t)
        ret.push_back(t);
    return ret;
}

class Solution {
public:
    int solve(vector<int> & nums, int start, int ops)
    {
        cout << "start: " << start  << ", num: " << nums[start] << ", ops: " << ops << endl;
        if(ops == 0) return nums[start];
        if(start == nums.size() - 1) return (nums[start] - 1) / (ops + 1) + 1;

        int ans = nums[start];
        for(int i=ops; i>0; i--)
        {
            int firstMin = (nums[start] - 1) / (i + 1) + 1;
//            cout << "i: " << i << ", firstMin: " << firstMin << endl;
            if(firstMin >= nums[start + 1]) {
                ans = min(ans, firstMin);
                break;
            }
            else if(firstMin <= (nums[start + 1] - 1) / (ops-i+1) + 1)
                continue;
            ans = min(ans, max(firstMin, solve(nums, start + 1, ops - i)));
        }
        return ans;
    }


    int minimumSize(vector<int>& nums, int maxOperations) {
        sort(nums.begin(), nums.end(), greater<int>());
        return solve(nums, 0, maxOperations);
    }
};



int main()
{
    freopen("/Users/mark/MarkLearningCPP/力扣/第 228 场周赛/5678. 袋子里最少数目的球/case1.txt", "r", stdin);
    string s;
    int maxOperations;
    cin >> s >> maxOperations;
    cout << s << endl << maxOperations << endl;

    vector<int> nums = readIntVector1D(s);
    Solution slt;
    cout << slt.minimumSize(nums, maxOperations);
}