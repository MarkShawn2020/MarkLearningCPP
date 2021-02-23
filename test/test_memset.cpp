//
// Created by 南川 on 2021/1/18.
//
#include "cstdio"
#include "string"

int main()
{
    const int N = 10;
    int a[N];
    memset(a, 1, sizeof a);

    for(int i=0; i<N; ++i)
        printf("%d ", a[i]);

    return 0;
}