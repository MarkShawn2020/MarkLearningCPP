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

class Solution {
public:

    int Merge(vector<int> & nums, vector<vector<int>> & dp, vector<vector<bool>> & G,
              const int & stt, const int & end, const int & k)
    {
        if(G[stt][end]) return 1;
        int minDP = dp[k-1][stt];
        for(int i=stt; i<end; i++)
            if(G[end][i]){
                int theDP = dp[i-stt-1][stt];
                if(theDP < minDP)
                    minDP = theDP;
            }
        return minDP+1;
    }

     int Fill(vector<int> & nums, vector<int> & dp, vector<vector<bool>> & G,
              const int end){
        if(G[0][end]) return dp[end]=1;
        int MIN = INT_MAX;
        for(int i=1; i<end; i++)
            if(G[end][i])
                MIN = min(MIN, dp[i-1]);
        if(MIN < INT_MAX)
            dp[end] = MIN+1;
         return 0;
    }

    int splitArray(vector<int>& nums) {
        const int N = nums.size();
        vector<vector<bool>> G(N, vector<bool> (N, true));
        for(int i=0; i<N; i++)
            for(int j=i+1; j<N; j++)
                if(gcd(nums[i], nums[j])==1)
                    G[i][j] = G[j][i] = false;

        vector<int> dp(N, 1);
        for(int end=1; end<N; end++){
            Fill(nums, dp, G, end);
        }
        return dp[N-1];
    }
};

int main()
{
    freopen("/Users/mark/CLionProjects/MarkLearningCPP/力扣/ACP14/case1.txt", "r", stdin);

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