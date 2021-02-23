//
// Created by 南川 on 2021/1/23.
//

#include "cstdio"
#include "cstring"
#include "vector"

#define max(a, b) (a) > (b) ? (a) : (b)

using std::vector;


const int N = 10000 + 1;


int main()
{
    freopen("/Users/mark/CLionProjects/MarkLearningCPP/PAT/B1007 Maximum Subsequence Sum/case1.txt", "r", stdin);

    int n, v;
    scanf("%d", &n);

    int dp[N]; memset(dp, 0, sizeof dp);

    vector<vector<int>> his;
    int l, h, sum;
    l = h = sum = 0;

    for(int i=1; i<=n; i++)
    {
        scanf("%d", &v);
        int nSUm = dp[i-1] + v;
        if(nSUm >= sum){
            if(!sum) l=i;
            sum = nSUm, h=i, dp[i]=nSUm;
        }
        else if(nSUm < 0)
        {
            his.emplace_back(vector<int>{l, h, sum});
            sum = 0, dp[i] = 0;
        }else{
            dp[i] = nSUm;
        }
    }
    his.emplace_back(vector<int>{l, h, sum});

    int L, H, SUM = INT_MIN;
    for(auto item: his)
    {
        if(item[2] > SUM)
            L = item[0], H = item[1], SUM = item[2];
    }
    printf("%d %d %d\n", SUM, L-1, H-1);

}