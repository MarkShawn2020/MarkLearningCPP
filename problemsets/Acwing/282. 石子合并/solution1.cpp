//
// Created by 南川 on 2021/1/17.
//

#include "climits"
#include "cstdio"
#include "array"
#include "vector"
using namespace std;

static const int N = 300;

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
    int n;
    array<array<int, N>, N> sm{};
    array<array<int, N>, N> dp{};
    array<int, N> arr{};

//    n = 4;
//    arr = {1, 3, 5, 2}; // ans=7742
//    scanf("%d", &n); for(int i=0; i<n; i++) scanf("%d", &(arr[i]));
    n = 10;
    arr = {548 ,592, 715 ,844, 602,
           857, 544 ,847, 423 ,623};

    // 构建和数组，第n行第m列的值表示从第m个数起往右n个数的总和
    for(int i=0; i<n; i++) sm[0][i] = arr[i];
    for(int i=1; i<n+1; i++)
        for(int j=0; j<n-i; j++)
            sm[i][j] = sm[i-1][j] + sm[0][i+j];

    for(int i=1; i<n+1; i++)
        for(int j=0; j<n-i; j++)
            dp[i][j] = sm[i][j] + getMinDP(dp, i, j);

    printf("%d", dp[n-1][0]);
    return 0;
}