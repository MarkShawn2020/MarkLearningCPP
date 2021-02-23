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
    void recurAdd(vector<int> & nums, vector<int> & S, int &p, int sm, int i, int end)
    {
        for(int j=i+1; j<end; j++)
            S[++p] = sm + nums[j],
            recurAdd(nums, S, p, sm+nums[j], j, end);
    }

    void init(vector<int> & nums, vector<int> & V, int & p, int s, int t)
    {
        for(int i=s; i<t; i++)
            V[++p] = nums[i],
            recurAdd(nums, V, p, nums[i], i, t);
        sort(V.begin(), V.begin() + p+1);
        for(int i=0; i<p+1; i++) cout << V[i] << "\t"; cout << endl;
    }

public:
    int minAbsDifference(vector<int>& nums, int goal) {
        const int N = nums.size();
        const int MAX_SIZE = (int)2e1;
        int pa = 0, pb = 0;
        vector<int> VA(MAX_SIZE), VB(MAX_SIZE);
        VA[0] = VB[0] = 0;          // 哨兵
        init(nums, VA, pa, 0, N/2);
        init(nums, VB, pb, N/2, N);

        int best = abs(goal);
        for(int i=0, j=pb; i<=pa && j>=0;)  // p是自增的，所以是闭
        {
            int sm = VA[i] + VB[j];
            best = min(best, abs(sm - goal));
            if(sm < goal) i++;
            else if(sm > goal) j--;
            else return 0;
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
    ifstream fin("/Users/mark/MarkLearningCPP/力扣/5675. 最接近目标值的子序列和/case5.txt");
    run(fin.good() ? fin : cin);
}

