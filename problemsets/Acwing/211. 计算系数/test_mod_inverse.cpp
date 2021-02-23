//
// Created by 南川 on 2021/2/12.
//
#include "cstdio"
#include "ctime"
using namespace std;

/**
 * 求 ax + by = gcd(a, b)
 */
void extern_gcd(int a, int b, int & x, int & y)
{
    if(b == 0) {x = 1, y = 0; return; }
    extern_gcd(b, a % b, y, x);
    y -= (a / b) * x;
}

/**
 * 求 ax ≡ 1 (mod m)
 * 即 ax + my = 1
 */
int mod_inverse(int a, int m)
{
    int x, y;
    extern_gcd(a, m, x, y);
    return (m + x % m) % m; // x可能为负，需要转正
}

int fastPow(int a, int n, int m)
{
    int ans = 1;
    while (n > 0)
    {
        if(n & 1)
            ans = ans * a % m;
        a = a * a % m;
        n >>= 1;
    }
    return ans;
}

/**
 * 条件： gcd(a, m) = 1
 * 费马小定理： a ^ (m - 1) ≡ 1
 * 目标： 求 a * x ≡ 1
 * 方法： 等价于求 a ^ (m - 2)
 */
int mod_inverse_feima(int a, int m)
{
    return fastPow(a, m-2, m);
}


int main()
{
    const int N = 1;
    int a = 2, m = 5, x1, x2;

    auto c1 = clock();

    for(int i=0; i<N; i++)
        x1 = mod_inverse(a, m);

    auto c2 = clock();

    for(int i=0; i<N; i++)
            x2 = mod_inverse_feima(a, m);

    auto c3 = clock();

    printf("target function: %d * x ≡ 1 (mod %d)\n", a, m);
    printf("x1: %d, x2: %d\n", x1, x2);
//    printf("扩欧算法, x1: %d, 耗时：%.4f ms\n", x1, (double )(c2 - c1) / CLOCKS_PER_SEC * 1000);
//    printf("费马算法. x2: %d, 耗时：%.4f ms\n", x2, (double )(c3 - c2) / CLOCKS_PER_SEC * 1000);
    printf("扩欧算法, 耗时：%.4f ms\n", (double )(c2 - c1) / CLOCKS_PER_SEC * 1000);
    printf("费马算法. 耗时：%.4f ms\n", (double )(c3 - c2) / CLOCKS_PER_SEC * 1000);
    // (8 x 4) % 31 == 1
}