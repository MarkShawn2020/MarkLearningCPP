//
// Created by 南川 on 2021/2/13.
//

#include <iostream>

using namespace std;

const int mod = 10007;

int qmi(int a, int k)
{
    a %= mod;
    int res = 1;
    while (k)
    {
        if (k & 1) res = res * a % mod;
        a = a * a % mod;
        k >>= 1;
    }
    return res;
}

int main()
{
    freopen("/Users/mark/MarkLearningCPP/Acwing/211. 计算系数/case3.txt", "r", stdin);

    int a, b, k, n, m;

    cin >> a >> b >> k >> n >> m;

    int res = qmi(a, n) * qmi(b, m) % mod;
    printf("res: %d\n", res);
    for (int i = 1, j = k; i <= n; i ++, j -- )
    {
        res = res * j % mod;
        res = res * qmi(i, mod - 2) % mod;
        printf("i: %d, res: %d\n", i, res);
    }

    cout << res << endl;

    return 0;
}

//作者：yxc
//        链接：https://www.acwing.com/solution/content/3155/
//来源：AcWing
//        著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。