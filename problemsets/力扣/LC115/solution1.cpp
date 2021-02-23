//
// Created by 南川 on 2021/1/18.
//

#include "iostream"
#include "vector"
#include "string"

using namespace std;

class Solution {
public:
    int numDistinct(string s, string t) {
        const int n = s.size();
        const int m = t.size();
        vector<int> dp(m+1, 0);
        dp[0] = 1;

        for(int i=0; i<n; ++i)
            for(int j=m; j>0; --j)
                if(s[i] == t[j-1])
                    dp[j] += dp[j-1];

        return dp[m];
    }
};



int main()
{
    freopen("/Users/mark/CLionProjects/MarkLearningCPP/LC115/case1.txt", "r", stdin);
    string s, t;
    cin.get();
    cin >> s;
    s.erase(s.end()-1);
    cin.get();
    cin.get();
    cin >> t;
    t.erase(t.end()-1);
    Solution slt;
    cout << slt.numDistinct(s, t);
}