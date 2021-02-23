#include "cstdio"
#include "algorithm"
using namespace std;

const int N = 350 + 1;
const int M = 120 + 1;
int n, m, a[N], bi, key, freq[N][1 << 24];


int main()
{
    freopen("/Users/mark/MarkLearningCPP/Acwing/312. 乌龟棋/case4.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    for(int i=1; i<=n; ++i) scanf("%d", &a[i]);
    for(int i=1; i<=m; ++i) scanf("%d", &bi), key += 1 << (6 * (bi - 1));
    freq[1][key] = a[1];

    for(int i=1; i<n; i++)
        for(int j=1; j<=(1<<24); j++)
            if(freq[i][j])
                for(int d=1; d<=4; d++)
                    if((j >> (6 * (d-1))) % (1 << (6 * d)) > 0)  // 第d位为正
                    {
                        int key2 = j - (1 << (6 * (d - 1)));
                        freq[i + d][key2] = max(freq[i+d][key2], freq[i][j] + a[i + d]);
                    }

    printf("%d", freq[n][0]);
}