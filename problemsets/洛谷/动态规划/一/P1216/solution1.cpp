//
// Created by 南川 on 2021/1/17.
//

#include "cstdio"
#include "vector"

using namespace std;


int main()
{
//    freopen("/Users/mark/CLionProjects/MarkLearningCPP/洛谷/动态规划/P1216/case1.txt", "r", stdin);

    int k;
    scanf("%d", &k);

    vector<vector<int>> data(k, vector<int>(k, 0));
    for(int i=1; i<k+1; ++i)
        for(int j=0; j<i; ++j)
            scanf("%d", &data[i-1][j]);

    for(int h=k-2; h>-1; --h)
        for(int i=0; i<h+1; i++)
            data[h][i] += max(data[h+1][i], data[h+1][i+1]);

    printf("%d", data[0][0]);
    return 0;
}