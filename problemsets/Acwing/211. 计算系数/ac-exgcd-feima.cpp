//
// Created by 南川 on 2021/2/13.
//

#include "cstdio"

const int M = 10007;

int fastPow(int a, int n)
{
    a %= M;         // 细节
    int res = 1;
    while(n > 0)
    {
        if(n & 1)
            res = res * a % M;
        a = a * a % M;
        n >>= 1;
    }
    return res;
}

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
    return (M + x % M) % M; // avoid x to be negative
}


int main()
{
     freopen("/Users/mark/MarkLearningCPP/Acwing/211. 计算系数/case3.txt", "r", stdin);
    int a, b, k, n, m;
    scanf("%d %d %d %d %d", &a, &b, &k, &n, &m);

    int res = (fastPow(a, n) * fastPow(b, m)) % M;
    printf("res: %d\n", res);
    for(int i=1, j=k; i<=n; ++i, --j)
        res = res * j % M * mod_inv(i) % M % M,
        printf("i: %d, res: %d\n", i, res);
    printf("%d", res);
}