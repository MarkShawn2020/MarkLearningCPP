#include "cstdio"
#include "algorithm"
using namespace std;

const int N = 350 + 1;
const int M = 120 + 1;
const int M2 = 40 + 1;
int n, m, a[N], bi, b[5];
short dp[6][M2][M2][M2][M2];



int main()
{
    freopen("/Users/mark/MarkLearningCPP/Acwing/312. 乌龟棋/case3.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    for(int i=1; i<=n; ++i) scanf("%d", &a[i]);
    for(int i=1; i<=m; ++i) scanf("%d", &bi), ++b[bi];

    dp[1][b[1][b2][b3][b4]] = a[1];
    for(int i=1; i<n; ++i)
    {
        
    }

    printf("%d", recurMemorized(1, b));
}
