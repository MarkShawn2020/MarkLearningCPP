#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int MAX_N  = 100 + 1, MAX_T = 1000 + 1;
int N, T, w[MAX_N], d[MAX_N], c[MAX_N], dp[MAX_N][MAX_T];

int main ()
{
    scanf("%d", &N);
    for(int i=1; i<=N; i++) scanf("%d", &w[i]);
    for(int i=1; i<=N; i++) scanf("%d", &d[i]);
    for(int i=1; i< N; i++) scanf("%d", &c[i]);
    scanf("%d", &T);

    for(int i=1; i<=N; i++)                 // dp每一行存储一个池塘拥有j分钟的最大收益（1<=j<=T)
        for(int j=1; j<=T; j++)
            dp[i][j] = dp[i][j-1] + w[i],
            w[i] = max(w[i] - d[i], 0);

    for(int i=N-1; i>0; i--)                // 从下往上更新第n-1到第1个池塘的最大收益
        for(int j=T; j>c[i]; j--) {         // 从右往左更新，防止可能的覆盖
            int mx = dp[i][j];              // 留在原池塘能获得的最大收益
            for(int k=1; k<=j-c[i]; k++)    // 分配k分钟给下一个池塘，j-c[i]-k就是原池塘的时间
                mx = max(mx, dp[i+1][k] + dp[i][j-c[i]-k]);
            dp[i][j] = mx;
        }
    printf("%d", dp[1][T]);
}