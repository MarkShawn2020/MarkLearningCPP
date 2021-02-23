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

class Violent{

    set<int> hss;
    
    int violentRecur(vector<int> & nums, int goal, int cur, int i)
    {
        if(i == nums.size()) return abs(cur - goal);

        int a1 = violentRecur(nums, goal, cur+nums[i], i+1);
        int a2 = violentRecur(nums, goal, cur, i+1);
        if(a1 < a2) hss.insert(i);
        return min(a1, a2);
    }

public:
    void violent(vector<int> & nums, int goal)
    {
        cout << "goal: " << goal << endl;
        sort(nums.begin(), nums.end());
        for(auto & c: nums)
            cout << c << "\t";
        cout << endl;
        int ans = violentRecur(nums, goal, 0, 0);
        cout << "sequence:\t";
        for(auto & c: hss)
            cout << c << "\t";
        cout << endl;
        cout << "ans: " << ans << endl;
    }
};


class Solution {
    int p=0, sn=0, sp=0, best=0;

    int recur(vector<int> & nums, int & goal, int cur, int i)
    {
        // 判等退出
        int val = abs(cur - goal);
        best = min(best, val);
        if(cur == goal) return 0;

        // 负数的深递归与剪枝【新加的负数与所有正数之和比goal更小时剪枝】
        if(cur + sp > goal)
            for(int j=i+1; j<p; j++)
            {
                printf("i: %d, j: %d, cur: %d, cur-goal: %d, best: %d\n", i, j, cur, val, best);
                if(!recur(nums, goal, cur+nums[j], j)) return 0;
            }
        
        // 正数的深递归与剪枝【新加的正数导致cur比goal还要大时剪枝】
        if(cur < goal)
            for(int j=max(p, i+1); j<nums.size(); j++)
            {
                printf("i: %d, j: %d, cur: %d, cur-goal: %d, best: %d\n", i, j, cur, val, best);
                if(!recur(nums, goal, cur+nums[j], j)) return 0;
            }

        return val;
    }

public:
    int minAbsDifference(vector<int>& nums, int goal) {
        sort(nums.begin(), nums.end());

        // // 暴力搜索：对拍
        // Violent vio;
        // vio.violent(nums, goal);

        // p is the divider of negative and positive nums
        p = nums.size();
        sp = sn = 0;
        for(int i=0; i<nums.size(); i++)
            nums[i] < 0 ? sn -= nums[i] : (sp += nums[i], p = min(p, i));

        // Recur Algo
        best = abs(goal);
        printf("p: %d, sp: %d, sn: %d\n", p, sp, sn);
        for(int i=0; i<nums.size(); i++)
        {
            cout << "--- " << i << " ---\n";
            if(!recur(nums, goal, nums[i], i))
                return 0;
        }
        return best;
        
    }
};


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
    ifstream fin("/Users/mark/MarkLearningCPP/力扣/5675. 最接近目标值的子序列和/case3.txt");
    run(fin.good() ? fin : cin);
}

