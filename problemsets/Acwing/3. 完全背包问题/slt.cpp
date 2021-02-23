//
// Created by 南川 on 2021/1/20.
//

#include "cstdio"

const inline int max(const int & a, const int & b){
    return a > b ? a : b;
}

const int N = 1000;
int dp[N + 1];

int main()
{
      freopen("/Users/mark/CLionProjects/MarkLearningCPP/Acwing/ACW03-完全背包问题/case4.txt", "r", stdin);

    int n, m, k, v;
    scanf("%d %d", &n, &m);

    for(int i=0; i<n; i++)
    {
        scanf("%d %d", &k, &v); // k是第i个物品的体积，v是其重量
        for(int j=0; j+k<=m; j++) // dp[j]是背包中已装j份体积时所能达到的最大重量
            dp[j+k] = max(dp[j] + v, dp[j+k]);
    }

    int ans = 0;
    for(int p: dp)
        ans = max(ans, p);
    printf("%d", ans);
}