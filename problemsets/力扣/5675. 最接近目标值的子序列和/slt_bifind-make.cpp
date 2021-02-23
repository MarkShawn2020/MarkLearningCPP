//
// Created by 南川 on 2021/1/28.
//
#include "cstdio"
#include "cstring"
#include "cmath"
#include "cassert"

#include "string"
#include "iostream"
#include "fstream"
#include "sstream"
#include "algorithm"

#include "vector"
#include "stack"
#include "list"
#include "queue"
#include "set"
#include "unordered_set"
#include "map"
#include "unordered_map"

using namespace std;

vector<int> readIntVectorID(string s)
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
    vector<int> make(vector<int> nums){
        vector<int> ans(1 << nums.size());
        for(int i = 0; i < nums.size(); ++i)
            for(int j = 0; j < (1 << i); ++j)
                ans[j + (1 << i)] = ans[j] + nums[i];
        return ans;
        
        for(int & c: nums) printf("%d ", c); printf("\n");
                // printf("i: %d, j: %d, j+(1<<i): %d, val: %d\n", i, j, j+(1<<i), ans[j+(1<<i)]);
    }
    int minAbsDifference(vector<int>& nums, int goal) {
        int n = nums.size();
        vector<int> left = make({nums.begin(), nums.begin() + n / 2});
        vector<int> right = make({nums.begin() + n / 2, nums.end()});
        sort(left.begin(), left.end());
        sort(right.rbegin(), right.rend());
        int ans = INT_MAX, i = 0, j = 0;
        while(i < left.size() && j < right.size()){
            int t = left[i] + right[j];
            ans = min(ans, abs(goal - t));
            if(t > goal) j++;
            else if(t < goal) i++;
            else return 0;
        }
        return ans;
    }
};

// 作者：Monologue-S
// 链接：https://leetcode-cn.com/problems/closest-subsequence-sum/solution/mei-ju-shuang-zhi-zhen-by-monologue-s-zhxq/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

template <typename T>
void run(T & cin)
{
    string s;
    cin >> s;
    vector<int> nums = readIntVectorID(s);
    int goal, ans;
    cin >> goal >> ans;

    Solution slt;
    assert(slt.minAbsDifference(nums, goal) == ans);

}


int main()
{
    // speed up IO
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    // read from local case if possible, otherwise from console
    ifstream fin("/Users/mark/MarkLearningCPP/力扣/5675. 最接近目标值的子序列和/case5.txt");
    run(fin.good() ? fin : cin);
}

