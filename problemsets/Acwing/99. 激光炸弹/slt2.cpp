//
// Created by 南川 on 2021/1/26.
//

#include <bits/stdc++.h>
using namespace std;

const int SZ = 5000;
static int data[SZ][SZ];
int N, R, x, y, w;


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    freopen("/Users/mark/CLionProjects/MarkLearningCPP/Acwing/99. 激光炸弹/case1.txt", "r", stdin);

    cin >> N >> R;
    for(int i=0; i<N; i++)
        cin >> x >> y >> w, data[x][y] += w;

    const int K = min(R, SZ);
    int ans = 0;
    for(int i=0; i<K; i++)
        for(int j=0; j<K; j++)
            ans += data[i][j];

    int areaSum = ans, areaSumNextRow = ans;

    for(int i=K; i<SZ; i++)
    {

        for(int k=0; k<K; k++)
            areaSumNextRow += data[i][k] - data[i-K][k];
        ans = max(ans, areaSumNextRow);
        for(int j=K; j<SZ; j++)
        {
            for(int k=0; k<K; k++)
                areaSum += data[i-k-1][j] - data[i-k-1][j-K];
            ans = max(ans, areaSum);
        }
        areaSum = areaSumNextRow;
    }

    cout << ans;

}