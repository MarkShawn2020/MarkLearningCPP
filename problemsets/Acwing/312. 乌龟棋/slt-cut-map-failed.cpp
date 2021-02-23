#include "cstdio"
#include "algorithm"
#include "unordered_map"
using namespace std;

const int N = 350 + 1;
const int M = 120 + 1;
int n, m, k, ans, a[N], bi, key;
unordered_map<int, int> mps[N];


int main()
{
    freopen("/Users/mark/MarkLearningCPP/Acwing/312. 乌龟棋/case1.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    for(int i=1; i<=n; ++i) scanf("%d", &a[i]);
    for(int i=1; i<=m; ++i) scanf("%d", &bi), key += 1 << (6 * (bi - 1));
    mps[1][key] = a[1];

    for(int i=1; i<n; i++)
        for(auto & mp: mps[i])
            for(int d=1; d<=4; d++)
                if((mp.first >> (6 * (d-1))) % (1 << (6 * d)) > 0)  // 第d位为正
                {
                    int key2 = mp.first - (1 << (6 * (d - 1)));
                    mps[i + d][key2] = max(mps[i+d][key2], mp.second + a[i + d]);
                }

    printf("%d", mps[n][0]);
}
