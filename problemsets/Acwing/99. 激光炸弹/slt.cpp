//
// Created by 南川 on 2021/1/26.
//

#include <bits/stdc++.h>
using namespace std;

const int SZ = 5000 + 10;
int N, R, X = 0, Y = 0;
int G[SZ][SZ] = {0};


int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

     freopen("/Users/mark/CLionProjects/MarkLearningCPP/Acwing/99. 激光炸弹/case4.txt", "r", stdin);

    // 初始化二维数组
    cin >> N >> R;
    for(int i=0, x, y, w; i<N; i++)
    {
        cin >> x >> y >> w;
        X = max(x+1, X);
        Y = max(y+1, Y);
        G[x + 1][y + 1] += w;
    }

    // 点值 -> 前缀和
    for(int i=1; i<=X; i++)
        for(int j=1; j<=Y; j++)
            G[i][j] += G[i - 1][j] + G[i][j - 1] - G[i - 1][j - 1];

    // 遍历求最大值
    // int ans = G[min(X, R)][min(Y, R)];
    int ans = 0;
    // cout << ans << endl;
    for(int i=min(X, R); i<=X; i++)
        for(int j=min(Y, R); j<=Y; j++)
            ans = max(ans, G[i][j] - G[i - R][j] - G[i][j - R] + G[i - R][j - R]);
    cout << ans;

}