//
// Created by 南川 on 2021/1/20.
//

#include "cstdio"

inline int max(const int & a, const int & b){
    return a > b ? a : b;
}

const int N = 5;
int dp[N + 1];

void ZeroOnePack(int dp[], int u, int v, const int packs)
{
    for(int i=packs; i>=u; i--)
        dp[i] = max(dp[i], dp[i-u]+v);
}

void MultiPack(int dp[], int u, int v, const int packs)
{
    for(int i=u; i<=packs; i++)
        dp[i] = max(dp[i], dp[i-u]+v);
}

int main()
{
       freopen("/Users/mark/CLionProjects/MarkLearningCPP/Acwing/ACW04-多重背包问题I、II/case1.txt", "r", stdin);

    int n, m, u, v, K;
    scanf("%d %d", &n, &m);

    for(int i=0; i<n; i++)
    {
        scanf("%d %d %d", &u, &v, &K);
        if(u * K >= m)  // complete pack
        {
            MultiPack(dp, u, v, m);
        }
        else            // zero-one pack
        {
            for(int k=1; k<K; K-=k, k<<=1)
                ZeroOnePack(dp, k*u, k*v, m);
            ZeroOnePack(dp, K*u, K*v, m);
        }
    }

    int ans = 0;
    for(int p: dp)
        ans = max(ans, p);
    printf("%d", ans);
}