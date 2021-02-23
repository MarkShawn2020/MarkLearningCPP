//
// Created by 南川 on 2021/2/12.
//

/**
 * 将n看做二进制
 * 从右往左第k位的1表示因子中含有a^{2^k}
 */
int fastPow(int a, int n)
{
    int ans = 1;
    while(n)
    {
        if(n & 1)
            ans *= a;
        a *= a;
        n >>= 1;
    }
    return ans;
}