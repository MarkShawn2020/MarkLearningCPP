const int N = 350 + 1;
const int M = 120 + 1;
int n, m, k, ans, a[N], bi, cnt[5];
bool L[N], R[N];

#include "cstdio"
#include "queue"
#include "cstring"
#include "algorithm"
using namespace std;

/**
 * dp 的核心就是，当还剩余多少路程的时候，其最大收益是多少
 */


int nextStep(int i, const int c[])
{
    int nextMax = 0;
    for(int j=1; j<=4; j++)
        if(c[j] > 0) {
            int cnt2[5];
            memcpy(cnt2, c, sizeof(int) * 5);
            --cnt2[j];
            nextMax = max(nextMax, nextStep(i+j, cnt2));
        }
    // printf("i: %d, nextMax: %d, cnt: [%d, %d, %d, %d]\n", i, nextMax, c[1], c[2], c[3], c[4]);
    return a[i] + nextMax;
}


int main()
{
    freopen("/Users/mark/MarkLearningCPP/Acwing/312. 乌龟棋/case4.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    for(int i=1; i<=n; ++i) scanf("%d", &a[i]);
    for(int i=1; i<=m; ++i) scanf("%d", &bi), ++cnt[bi];
    
    printf("%d", nextStep(1, cnt));
}