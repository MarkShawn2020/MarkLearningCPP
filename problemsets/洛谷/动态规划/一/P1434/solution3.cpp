
//
// Created by 南川 on 2021/1/17.
//

#include "cstdio"
#include "vector"

using namespace std;

static const vector<vector<int>> offsets = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
int ans = 0;



int main()
{
//    freopen("/Users/mark/CLionProjects/MarkLearningCPP/洛谷/动态规划/P1434/case1.txt", "r", stdin);

    int n, m;
    scanf("%d %d", &n, &m);

    int temp, max_i, max_j, max_v = 0;
    vector<vector<int>> data(n+2, vector<int>(m+2, -1));
    vector<vector<int>> dp(n+2, vector<int>(m+2, 0));


    printf("%d", ans);
    return 0;
}