//
// Created by 南川 on 2021/1/20.
//

#include "cstdio"

const inline int max(const int & a, const int & b){
    return a > b ? a : b;
}

int dp[1000];

int main()
{
    freopen("/Users/mark/CLionProjects/MarkLearningCPP/Acwing/ACW02-01背包问题/case1.txt", "r", stdin);

    int n, m, k, v;
    scanf("%d %d", &n, &m);

    for(int i=0; i<n; i++)
    {
        scanf("%d %d", &k, &v);
        for(int j=m; j>=k; j--)
            dp[j] = max(dp[j], dp[j-k]+v);
    }

    int ans = 0;
    for(int p: dp)
        ans = max(ans, p);
    printf("%d", ans);
}