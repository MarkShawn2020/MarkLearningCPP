#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int MAX_N  = 100 + 1, MAX_T = 1000 + 1;
int N, T, w[MAX_N], d[MAX_N], c[MAX_N], dp[MAX_N][MAX_T];

int main ()
{
    freopen("/Users/mark/MarkLearningCPP/Acwing/1262. 鱼塘钓鱼/case1.txt", "r", stdin);
    scanf("%d", &N);
    for(int i=1; i<=N; i++) scanf("%d", &w[i]);
    for(int i=1; i<=N; i++) scanf("%d", &d[i]);
    for(int i=1; i< N; i++) scanf("%d", &c[i]);
    scanf("%d", &T);

    for(int i=1; i<=N; i++)                 // dp每一行存储一个池塘拥有j分钟的最大收益（1<=j<=T)
        for(int j=1; j<=T; j++)
            dp[i][j] = dp[i][j-1] + w[i],
            w[i] = max(w[i] - d[i], 0);

    

    printf("%d", dp[1][T]);
}