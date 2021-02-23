//
// Created by 南川 on 2021/2/20.
//
#include "vector"
#include "iostream"
#include "array"
using namespace std;

#include "sstream"
vector<int> readIntVector1D(string s)
{
    vector<int> ret;

    for(char & ch: s)
        if(!isdigit(ch) && ch!='-' && ch!='+')
            ch = ' ';

    std::stringstream ss;
    ss << s;
    int t;
    while (ss >> t)
        ret.push_back(t);
    return ret;
}


int lengthOfLIS(vector<int>& nums) {
    const int N = nums.size();
    array<int, N+1> que;
//    int que[N+1];
//    que[0] = -1e5;

    int k = 0;
    for(auto & num: nums)
        if(num > que[k])
            que[++k] = num;
        else
            que[lower_bound(que, que+k, num) - que] = num;

    return k;
}


int main ()
{
    freopen("/Users/mark/MarkLearningCPP/力扣/300. 最长递增子序列/case5.txt", "r", stdin);

    string s;
    cin >> s;
    vector<int> nums = readIntVector1D(s);
    cout << lengthOfLIS(nums);

}