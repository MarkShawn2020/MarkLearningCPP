//
// Created by 南川 on 2021/1/25.
//

#include "cstdio"
#include "string"

using std::fill;

const int N = 5 * 1e5 + 1;

inline int lowbit(int x)
{
    return x & -x;
}

class TreeArray{
    // todo
};


void add(int dp[], int i, int v, const int n)
{
    while (i<=n)
        dp[i] += v, i+=lowbit(i);
}


int getSum(const int *dp, int i)
{
    int ans = 0;
    while (i>0)
        ans += dp[i], i-=lowbit(i);
    return ans;
}

void rangeAdd(int dp[], int i, int j, int v, const int n)
{
    add(dp, i, v, n);
    add(dp, j+1, -v, n);
}

/**
 * 在差分建树的基础上，原前缀和函数的结果就是数据单点的值
 * @param dp
 * @param i
 * @return
 */
int getSingle(const int *dp, int i)
{
    return getSum(dp, i);
}

int main()
{
      freopen("/Users/mark/CLionProjects/MarkLearningCPP/洛谷/P3368 【模板】树状数组 2/case1.txt", "r", stdin);

    int dp[N];
    fill(dp, dp+N, 0);

    int n, m, r1, r2, r3, r4 = 0;
    scanf("%d %d", &n, &m);

    for(int i=1; i<=n; i++) // 要从1开始
        scanf("%d", &r1), add(dp, i, r1-r4, n), r4=r1;

    for(int i=0; i<m; i++)
    {
        scanf("%d %d", &r1, &r2);
        if(r1 == 2)
            printf("%d\n", getSingle(dp, r2));
        else
        {
            scanf("%d %d", &r3, &r4);
            rangeAdd(dp, r2, r3, r4, n);
        }
    }

}