
//
// Created by 南川 on 2021/1/17.
//

#include "cstdio"
#include "vector"

using namespace std;

static const vector<vector<int>> offsets = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
int ans = 0;


void ensureOne(vector<vector<int>> & data, vector<vector<int>> & dp, const int n, const int m, int i, int j){
    if(i==0 || j==0 || i==n-1 || j==m-1) return;

    int v = data[i][j];
    int maxDp = 0;
    for(auto iter: offsets){
        if(data[i+iter[0]][j+iter[1]] > v){
            if(!dp[i+iter[0]][j+iter[1]])
                return;
            else
                maxDp = max(dp[i+iter[0]][j+iter[1]], maxDp);
        }
    }
    dp[i][j] = ++maxDp;
    if(maxDp>ans) ans = maxDp;
    for(auto iter: offsets)
        if(!dp[i+iter[0]][j+iter[1]])
            ensureOne(data, dp, n, m, i+iter[0], j+iter[1]);
}

int main()
{
//    freopen("/Users/mark/CLionProjects/MarkLearningCPP/洛谷/动态规划/P1434/case1.txt", "r", stdin);

    int n, m;
    scanf("%d %d", &n, &m);

    int temp, max_i, max_j, max_v = 0;
    vector<vector<int>> data(n+2, vector<int>(m+2, -1));
    vector<vector<int>> dp(n+2, vector<int>(m+2, 0));
    for(int i=0; i<n; ++i)
        for(int j=0; j<m; ++j){
            scanf("%d", &temp);
            data[i+1][j+1] = temp;
            if(temp > max_v){
                max_i = i+1;
                max_j = j+1;
                max_v = temp;
            }
        }
    dp[max_i][max_j] = 1;

    for(auto iter: offsets)
        if(!dp[max_i+iter[0]][max_j+iter[1]])
            ensureOne(data, dp, n+2, m+2, max_i+iter[0], max_j+iter[1]);

    printf("%d", ans);
    return 0;
}