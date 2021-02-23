//
// Created by 南川 on 2021/1/24.
//
#include "unordered_map"
#include "climits"
#include "string"
#include "iostream"
using namespace std;

class Solution {
public:

    inline int minTheSame(const string & a, const string & b)
    {
        int M = 0;
        unordered_map<char, int> mp;
        const int N = a.size() + b.size();
        for(const char & ch: a) ++mp[ch];
        for(const char & ch: b) ++mp[ch];
        for(auto & iter : mp)
            M = max(M, iter.second);
        return N - M;
    }

    inline int algoComp(int c1[], int c2[])
    {
        int sum1[28], sum2[28], sum=INT_MAX;
        fill(sum1, sum1+28, 0);
        fill(sum2, sum2+28, 0);
        sum1[0] =  sum2[27] = 0;
        for(int i=1; i<=26; i++)
            sum1[i] += sum1[i-1] + c1[i-1];
        for(int j=26; j>=1; j--)
            sum2[j] += sum2[j+1] + c2[j-1];
        for(int k=1; k<=25; k++)
            sum = min(sum, sum1[k] + sum2[k+1]);
        sum = min(sum, sum2[1] + c1[0]);
        sum = min(sum, sum1[26] + c2[25]);
        return sum;
    }

    int minStrictComp(const string & a, const string & b, int i=0, int j=25)
    {
        int c1[26], c2[26];
        fill(c1, c1+26, 0);
        fill(c2, c2+26, 0);
        for(const char & ch: a) ++c1[ch - 'a'];
        for(const char & ch: b) ++c2[ch - 'a'];

        return min(algoComp(c1, c2), algoComp(c2, c1));
    }

    int minCharacters(string a, string b) {
        return min(minStrictComp(a, b), minTheSame(a, b));
    }
};


int main()
{
//    string a = "dabadd";
//    string b = "cda";
//    string a = "ba";
//    string b = "ae";
//    string a = "ace";
//    string b = "abe";

    freopen("/Users/mark/CLionProjects/MarkLearningCPP/力扣/双周赛/5662. 满足三条件之一需改变的最少字符数/case4.txt", "r", stdin);
    string a, b;
    cin >> a >> b;
    a.erase(a.size() - 1);
    a.erase(0, 1);
    b.erase(b.size() - 1);
    b.erase(0, 1);

    Solution slt;
    cout << slt.minCharacters(a, b);
}