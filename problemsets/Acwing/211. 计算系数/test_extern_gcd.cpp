//
// Created by 南川 on 2021/2/12.
//
#include "cstdio"

int gcd(int a, int b) {
    while(b ^= a ^= b ^= a %= b);
    return a;
}

void extern_gcd(int a, int b, int &x, int &y)
{
    if(b == 0) {x = 1, y = 0; return;}
    extern_gcd(b, a % b, x, y);
    int tmp = x;
    x = y;                  // y -> x
    y = tmp - (a / b) * y;  // f(x, y) -> y
}


//int main()
//{
//    int a = 4, b = 6, x, y;
//    extern_gcd(a, b, x, y);
//    printf("%dx + %dy = %d 的整数解为(%d, %d)", a, b, gcd(a, b), x, y);
//    // 4x + 6y = 2 的整数解为(-1, 1)
//}