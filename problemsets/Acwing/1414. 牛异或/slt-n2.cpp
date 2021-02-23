//
// Created by 南川 on 2021/1/28.
//

#include <cstdio>

const int N = 1e5 + 1;
int dta1[N], dta2[N];

int main()
{
    int n; scanf("%d", &n);
    for(int i=1; i<=n; i++)
        scanf("%d", &dta1[i]);

    int Max = 0, Left = 0, Right = N;
    for(int delta=0; delta<n; delta++)  // 遍历n趟，第一趟单位为1，有n个单位；第n趟单位为n，有1个单位
        for(int start=1, end=start+delta; end<=n; ++start, ++end)  
        {   // dta2[start]记录区间[start, end]的异或和，并不断维护满足题意的最大值相关信息
            dta2[start] ^=  dta1[end];
            if(dta2[start] > Max || dta2[start] == Max && (end < Right || end == Right && delta<Right-Left))
                Max = dta2[start], Left = start, Right = end;
        }

    printf("%d %d %d", Max, Left, Right);
}