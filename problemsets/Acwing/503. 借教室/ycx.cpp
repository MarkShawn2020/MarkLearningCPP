#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 1000010;

int n, m;
int r[N], d[N], s[N], t[N];
LL b[N];

bool check(int k)                   // k是每次二分的中点订单编号
{
    for (int i = 1; i <= n; i ++ )  // b[i]记录目前的差分值
        b[i] = r[i];

    for (int i = 1; i <= k; i ++ )  // 差分更新（Important！）【把一半的订单都给加上】
        b[s[i]] -= d[i],            // 在申请单起始日，差分值减去申请量
        b[t[i] + 1] += d[i];        // 在申请单末尾日，差分值加上申请量

    LL res = 0;
    for (int i = 1; i <= n; i ++ )  // 差分累和过程中
        if(0 > res += b[i])         // 若为负则说明超过了最大容量
            return true;            // 返真表示二分继续往左半支进行
    return false;                   // 返否表示二分继续往右半支进行
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ )  // r[i] 是每天的库存
        scanf("%d", &r[i]);
    for (int i = n; i; i -- )       // r[i] 变成差分，即每天比昨天多的库存量
        r[i] -= r[i - 1];

    for (int i = 1; i <= m; i ++ )  // d, s, t 分别是数量，起始，结尾
        scanf("%d%d%d", &d[i], &s[i], &t[i]);

    int l = 1, r = m;
    while (l < r)                   // 二分寻找第一份让库存爆掉的单子
    {
        int mid = l + r >> 1;
        check(mid) ? r = mid : l = mid + 1;
    }

    check(r) ? printf("-1\n%d", r) : puts("0");
    return 0;
}

// 作者：yxc
// 链接：https://www.acwing.com/solution/content/3045/
// 来源：AcWing
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。