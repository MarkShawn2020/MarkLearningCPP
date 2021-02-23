//
// Created by 南川 on 2021/2/13.
//

#include "cstdio"

const int M = 10007;

void extern_gcd(int a, int b, int & x, int & y)
{
    if(!b) {x = 1, y = 0; return;}
    extern_gcd(b, a % b, y, x);
    y -= (a / b) * x;
}

int mod_inv(int a)
{
    int x, y;
    extern_gcd(a, M, x, y);
    return ( M+ x % M) % M; // avoid x to be negative
}


int main()
{
    freopen("/Users/mark/MarkLearningCPP/Acwing/211. 计算系数/case4.txt", "r", stdin);
    int a, b, k, n, m;
    scanf("%d %d %d %d %d", &a, &b, &k, &n, &m);

    int ans = 1;
    for(int i=0; i<k; ++i) ans = ans * (a % M) % M;
    for(int i=1; i<=m; ++i)
        ans = ans * (k-i+1) % M * (b % M) % M * mod_inv(i) % M * mod_inv(a) % M;
    printf("%d", ans % M);
}