//
// Created by 南川 on 2021/1/20.
//
#include "vector"
#include "algorithm"
#include "iostream"
#include "fstream"
#include "sstream"
#include "cmath"
#include "algorithm"
using namespace std;

inline int gcd(int a,int b) {
    while(b ^= a ^= b ^= a %= b);
    return a;
}

int getSub(vector<int> & nums, int a1, int bn){
    if(gcd(nums[a1], nums[bn]) > 1) return 1;

    int an = a1, b1 = bn;
    for(int i=bn; i>a1; i--)
        if(gcd(nums[a1], nums[i]) > 1)
        {an = i; break;}
    --an;
    for(int i=a1; i<=bn; i++)
        if(gcd(nums[i], nums[bn]) > 1)
        {b1 = i; break;}
    ++bn;

    return min(getSub(nums, an+1, bn), getSub(nums, a1, b1-1)) + 1;
        "?"
}

class Solution {
public:
    int splitArray(vector<int>& nums) {
        return getSub(nums, 0, nums.size()-1);
    }
};

int main()
{
    freopen("/Users/mark/CLionProjects/MarkLearningCPP/力扣/ACP14/case4.txt.txt", "r", stdin);

    const int N = 100;
    char s[N];
    scanf("%s", s);
    int n;
    for(int i=0; i<N; i++){
        if(s[i] == '\0'){
            n = i;
            break;
        }
        else if(!isdigit(s[i]))
            s[i] = ' ';
    }

    stringstream ss;
    ss << s;
    int k;
    vector<int> data;
    while (ss >> k){
        data.emplace_back(k);
    }
    Solution slt;
    cout << slt.splitArray(data);

    return 0;
}