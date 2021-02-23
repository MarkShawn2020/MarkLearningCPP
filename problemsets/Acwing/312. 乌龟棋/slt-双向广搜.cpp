//
// Created by 南川 on 2021/2/13.
//

#include "cstdio"
#include "algorithm"
#include "array"
#include "queue"
using namespace std;

const int N = 350 + 1;
const int M = 40 / 2 + 4 + 1;
short n, m, bi, a[N];

typedef array<short, 5> Key;  Key bL, bR;
typedef short Dp[M][M][M][M]; Dp dpL, dpR;
queue<Key> que;
#define item(dp, b) dp[b[1]][b[2]][b[3]][b[4]]


int main()
{
    freopen("/Users/mark/MarkLearningCPP/Acwing/312. 乌龟棋/case3.txt", "r", stdin);
    scanf("%hd %hd", &n, &m);
    for(int i=1; i<=n; ++i) scanf("%hd", &a[i]);
    for(int i=1; i<=m; ++i) scanf("%hd", &bi), ++bL[bi];

    que.push(bL);
    item(dpL, bL) = a[0];
    for(int i=1; i<= (n+1) >> 1; i++)
    {
        for(int d=1; d<=4; d++)
        {
            if()
        }
    }

}
