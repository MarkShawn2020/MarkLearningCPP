//
// Created by 南川 on 2021/1/17.
//

#include "climits"
#include "cstdio"
#include "array"
#include "iostream"
using namespace std;

static const int N = 300 + 1;

int getMinDP(array<array<int, N>, N> dp, int i, int j){
    if(i == 0) return 0;
    int md = INT_MAX;
    for(int k=0; k<i; k++){
        int dpOfLeftK = dp[k][j] + dp[i-k-1][j+k+1];
        if(dpOfLeftK < md) md = dpOfLeftK;
    }
    return md;
}

int main(){

//    freopen("/Users/mark/CLionProjects/MarkLearningCPP/ACW282/case3.txt", "r", stdin);

    int n;
    cin >> n;

    int arr[N];
    for(int i=0; i<n; i++) cin >> arr[i];

    array<array<int, N>, N> sm{};
    array<array<int, N>, N> dp{};

    // 构建总和数组，第n行第m列的值表示从第m个数起往右n个数的总和
    for(int i=0; i<n; i++) sm[0][i] = arr[i];
    for(int i=1; i<n+1; i++)
        for(int j=0; j<n-i; j++)
            sm[i][j] = sm[i-1][j] + sm[0][i+j];

    // 构建代价数组，第n行第m列的值表示从第m个数起往右n个数的最小代价
    for(int i=1; i<n+1; i++)
        for(int j=0; j<n-i; j++)
            dp[i][j] = sm[i][j] + getMinDP(dp, i, j);

    printf("%d", dp[n-1][0]);
    return 0;
}