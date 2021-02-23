#include "cstdio"
#include "algorithm"
using namespace std;

const int N = 350 + 1;
const int M = 120 + 1;
const int M2 = 40 + 1;
int n, m, a[N], bi, b[5];
short dp[M2][M2][M2][M2];


int recurMemorized(int k, int b1, int b2, int b3, int b4)
{
    if(dp[b1][b2][b3][b4]) return dp[b1][b2][b3][b4];
    int maxNext = 0;
    if(b1 > 0) maxNext = max(maxNext, recurMemorized(k+1, b1-1, b2, b3, b4));
    if(b2 > 0) maxNext = max(maxNext, recurMemorized(k+2, b1, b2-1, b3, b4));
    if(b3 > 0) maxNext = max(maxNext, recurMemorized(k+3, b1, b2, b3-1, b4));
    if(b4 > 0) maxNext = max(maxNext, recurMemorized(k+4, b1, b2, b3, b4-1));
    dp[b1][b2][b3][b4] = a[k] + maxNext;
    printf("k: %d, dp[%2d][%2d][%2d][%2d] = %d\n", k, b1, b2, b3, b4, dp[b1][b2][b3][b4]);
    return dp[b1][b2][b3][b4];
}

int main()
{
    freopen("/Users/mark/MarkLearningCPP/Acwing/312. 乌龟棋/case3.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    for(int i=1; i<=n; ++i) scanf("%d", &a[i]);
    for(int i=1; i<=m; ++i) scanf("%d", &bi), ++b[bi];
    printf("%d", recurMemorized(1, b[1], b[2], b[3], b[4]));
}
